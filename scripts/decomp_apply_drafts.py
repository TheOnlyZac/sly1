#!/usr/bin/env python3
# Apply workflow drafts one-at-a-time (isolated), build the unit object, diff
# against the target asm, and keep only byte-exact matches. Then apply all
# keepers together. Run: python3 /tmp/apply_drafts.py [verify|finalize]
import json, subprocess, os, re, sys

REPO = "/home/johan/git/sly1"
os.chdir(REPO)
DRAFTS = json.load(open("/tmp/drafts.json"))

def sh(cmd):
    return subprocess.run(["bash", "-lc", cmd], capture_output=True, text=True)

def cfile(unit): return f"src/{unit}.c"
def objbase(unit): return os.path.basename(unit)  # P2/crv -> crv

# ---- backup every file we might touch ----
TOUCHED = set(cfile(d["unit"]) for d in DRAFTS) | {"config/symbol_addrs.txt"}
BAK = {f: open(f).read() for f in TOUCHED if os.path.exists(f)}

def restore_all():
    for f, c in BAK.items():
        open(f, "w").write(c)

def apply_one(unit, sym, code, includes, wrap=True):
    f = cfile(unit)
    s = open(f).read()
    line = f'INCLUDE_ASM("asm/nonmatchings/{unit}", {sym});'
    if line not in s:
        return False, "INCLUDE_ASM line not found"
    if wrap:
        # keep INCLUDE_ASM (asm target) + add C under SKIP_ASM (current)
        repl = line + "\n#ifdef SKIP_ASM\n" + code.rstrip() + "\n#endif"
    else:
        repl = code  # finalize: plain C replaces the stub
    s = s.replace(line, repl, 1)
    for inc in includes or []:
        tok = inc.strip()
        if not tok:
            continue
        directive = f"#include {tok}"
        if directive not in s:
            ms = list(re.finditer(r'^#include .*$', s, re.M))
            if ms:
                pos = ms[-1].end()
                s = s[:pos] + "\n" + directive + s[pos:]
            else:
                s = directive + "\n" + s
    open(f, "w").write(s)
    return True, ""

def norm_disasm(obj, sym):
    r = sh(f"mips-linux-gnu-objdump -dr {obj} 2>/dev/null")
    out, p = [], False
    for ln in r.stdout.splitlines():
        if re.search(rf"<{re.escape(sym)}>:", ln):
            p = True; continue
        if p and ln.strip() == "":
            break
        if p:
            ln = re.sub(r'^\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+', '', ln)
            ln = re.sub(r'^\s*[0-9a-f]+: (R_MIPS)', r'\1', ln)
            ln = re.sub(r'[0-9a-f]+ <', '<', ln)
            ln = ln.strip()
            if ln:
                out.append(ln)
    return out

def current_symname(unit, sym):
    if "__" in sym:
        return sym
    obj = f"obj/current/{objbase(unit)}.o"
    r = sh(f"mips-linux-gnu-objdump -t {obj} 2>/dev/null")
    for ln in r.stdout.splitlines():
        m = re.search(rf"\b({re.escape(sym)}__\S+)", ln)
        if m and (" F " in ln or " g " in ln):
            return m.group(1)
    return sym  # maybe extern "C" / unchanged

def has_asm_callers(sym):
    # any other .s referencing this raw symbol?
    r = sh(f"grep -rl '\\b{re.escape(sym)}\\b' asm/nonmatchings/ 2>/dev/null")
    files = [x for x in r.stdout.split() if not x.endswith(f"/{sym}.s")]
    return len(files) > 0

def data_sec_size(obj):
    # total size of allocatable non-.text sections (rodata/data/bss/sdata...)
    r = sh(f"mips-linux-gnu-objdump -h {obj} 2>/dev/null")
    tot = 0
    for ln in r.stdout.splitlines():
        m = re.match(r'\s*\d+\s+(\.\S+)\s+([0-9a-f]{8})', ln)
        if m:
            name, sz = m.group(1), int(m.group(2), 16)
            if name == ".text" or name.startswith((".pdr", ".reginfo", ".comment", ".gnu", ".mdebug", ".debug")):
                continue
            tot += sz
    return tot

def verify():
    sh("source env/bin/activate; python3 configure.py --objects >/dev/null 2>&1")
    # cache clean data-section sizes per unit
    restore_all()
    units = sorted(set(d["unit"] for d in DRAFTS))
    sh("source env/bin/activate; ninja " + " ".join(f"obj/current/{objbase(u)}.o" for u in units) + " 2>&1")
    clean_size = {u: data_sec_size(f"obj/current/{objbase(u)}.o") for u in units}
    results = []
    for d in DRAFTS:
        unit, sym = d["unit"], d["sym"]
        restore_all()
        ok, msg = apply_one(unit, sym, d["code"], d.get("includes"))
        if not ok:
            results.append([unit, sym, "SKIP", msg]); continue
        oc, ot = f"obj/current/{objbase(unit)}.o", f"obj/target/{objbase(unit)}.o"
        b = sh(f"source env/bin/activate; ninja {oc} {ot} 2>&1")
        if b.returncode != 0:
            err = b.stdout.strip().splitlines()[-1] if b.stdout.strip() else "compile failed"
            results.append([unit, sym, "COMPILE_FAIL", err[:160]]); continue
        if data_sec_size(oc) != clean_size[unit]:
            results.append([unit, sym, "DATA_GROWTH", "adds rodata/data -> layout ripple"]); continue
        cs = current_symname(unit, sym)
        dt, dc = norm_disasm(ot, sym), norm_disasm(oc, cs)
        if dt and dt == dc:
            tag = "MATCH" if "__" in sym else ("MATCH_FUN_CALLERS" if has_asm_callers(sym) else "MATCH_FUN")
            results.append([unit, sym, tag, cs])
        else:
            results.append([unit, sym, "DIFFER", f"t={len(dt)} c={len(dc)}"])
    restore_all()
    json.dump(results, open("/tmp/verify_results.json", "w"), indent=0)
    from collections import Counter
    print(Counter(r[2] for r in results))
    for r in results:
        print(r)

def finalize():
    results = json.load(open("/tmp/verify_results.json"))
    keep = {(r[0], r[1]): r for r in results if r[2] in ("MATCH", "MATCH_FUN")}
    restore_all()
    sa = open("config/symbol_addrs.txt").read()
    for d in DRAFTS:
        key = (d["unit"], d["sym"])
        if key not in keep:
            continue
        apply_one(d["unit"], d["sym"], d["code"], d.get("includes"), wrap=False)
        r = keep[key]
        if r[2] == "MATCH_FUN":  # rename raw FUN_ -> mangled in symbol_addrs
            raw, mangled = d["sym"], r[3]
            sa = re.sub(rf'^{re.escape(raw)}(\s)', mangled + r'\1', sa, flags=re.M)
    open("config/symbol_addrs.txt", "w").write(sa)
    print("applied", len(keep), "keepers")

if __name__ == "__main__":
    (verify if len(sys.argv) < 2 or sys.argv[1] == "verify" else finalize)()
