/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "Sly Cooper Decompilation", "index.html", [
    [ "🦝 Sly Cooper and the Thievius Raccoonus", "index.html", "index" ],
    [ "Source Files", "md_src_2readme.html", null ],
    [ "Beginner's Guide", "md_docs_2BEGINNERSGUIDE.html", null ],
    [ "Contributing Guide", "md_docs_2CONTRIBUTING.html", [
      [ "So you want to decompile Sly 1...", "md_docs_2CONTRIBUTING.html#autotoc_md3", null ],
      [ "Contents", "md_docs_2CONTRIBUTING.html#autotoc_md4", null ],
      [ "Getting started", "md_docs_2CONTRIBUTING.html#autotoc_md5", null ],
      [ "Find a function to match", "md_docs_2CONTRIBUTING.html#autotoc_md6", null ],
      [ "Match the function", "md_docs_2CONTRIBUTING.html#autotoc_md7", [
        [ "Objdiff", "md_docs_2CONTRIBUTING.html#autotoc_md8", null ],
        [ "Decomp.me", "md_docs_2CONTRIBUTING.html#autotoc_md9", null ]
      ] ],
      [ "Integrate the matched code", "md_docs_2CONTRIBUTING.html#autotoc_md10", null ],
      [ "Make a pull request", "md_docs_2CONTRIBUTING.html#autotoc_md11", null ],
      [ "Conclusion", "md_docs_2CONTRIBUTING.html#autotoc_md12", null ]
    ] ],
    [ "Using Distrobox for Non-Debian Distributions", "md_docs_2DISTROBOX.html", [
      [ "What is Distrobox?", "md_docs_2DISTROBOX.html#autotoc_md14", null ],
      [ "Installing Distrobox", "md_docs_2DISTROBOX.html#autotoc_md15", [
        [ "Fedora:", "md_docs_2DISTROBOX.html#autotoc_md16", null ],
        [ "Arch Linux:", "md_docs_2DISTROBOX.html#autotoc_md17", null ],
        [ "openSUSE:", "md_docs_2DISTROBOX.html#autotoc_md18", null ]
      ] ],
      [ "Setting up the Debian Container", "md_docs_2DISTROBOX.html#autotoc_md19", [
        [ "1. Create the container", "md_docs_2DISTROBOX.html#autotoc_md20", null ],
        [ "2. Enter the container", "md_docs_2DISTROBOX.html#autotoc_md21", null ],
        [ "3. Verify you're in the container", "md_docs_2DISTROBOX.html#autotoc_md22", null ]
      ] ],
      [ "Following the Setup Instructions", "md_docs_2DISTROBOX.html#autotoc_md23", null ],
      [ "Exiting the Container", "md_docs_2DISTROBOX.html#autotoc_md24", null ],
      [ "Working with the Container", "md_docs_2DISTROBOX.html#autotoc_md25", [
        [ "Re-entering the container", "md_docs_2DISTROBOX.html#autotoc_md26", null ],
        [ "Running commands from outside", "md_docs_2DISTROBOX.html#autotoc_md27", null ],
        [ "Stopping the container", "md_docs_2DISTROBOX.html#autotoc_md28", null ],
        [ "Removing the container", "md_docs_2DISTROBOX.html#autotoc_md29", null ]
      ] ],
      [ "Troubleshooting", "md_docs_2DISTROBOX.html#autotoc_md30", [
        [ "Run.sh is not finding PCSX2", "md_docs_2DISTROBOX.html#autotoc_md31", null ]
      ] ]
    ] ],
    [ "Decompilation Cheatsheet", "md_docs_2mips__ps2__cheatsheet.html", [
      [ "</blockquote>", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md33", null ],
      [ "0 · Types, Sizes & Quick Hex Reference", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md34", [
        [ "A · Fundamental Types — size, alignment, MIPS instruction", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md35", null ],
        [ "B · Hex → Decimal — common offsets & sizes", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md36", null ],
        [ "C · Struct alignment rules & padding", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md37", null ],
        [ "D · Bits → bytes → hex — quick reference", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md38", null ]
      ] ],
      [ "1 · Integer Registers ($0 – $31)", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md40", null ],
      [ "2 · Float Registers ($f0 – $f31) — Coprocessor 1 (FPU)", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md42", null ],
      [ "</blockquote>", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md43", null ],
      [ "3 · Float Arithmetic Instructions (FPU)", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md44", null ],
      [ "4 · Memory Instructions (load / store)", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md46", null ],
      [ "5 · Jumps, Branches & Integer Arithmetic", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md48", null ],
      [ "</blockquote>", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md49", null ],
      [ "6 · C++ Demangling — Reading Mangled Names", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md50", null ],
      [ "</blockquote>", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md51", null ],
      [ "7 · Reading a Struct from ASM — Finding Offsets", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md52", null ],
      [ "8 · Recurring Patterns in Sly 1", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md54", null ],
      [ "9 · Annotated Example — EvaluateAcpb (ASM → full C)", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md56", null ],
      [ "10 · Ghidra — Practical Tips for Sly 1", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md58", null ],
      [ "11 · Common Errors & Troubleshooting", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md60", null ],
      [ "12 · Full Workflow — From Zero to PR", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md62", null ],
      [ "13 · PS2 EE Calling Convention — How Args Are Passed", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md64", null ],
      [ "14 · Special Registers HI / LO — mult, div & accumulator", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md66", null ],
      [ "</blockquote>", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md67", null ],
      [ "15 · VU0 / VU1 & PS2 SIMD Instructions (128-bit vectors)", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md68", null ],
      [ "</blockquote>", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md69", null ],
      [ "16 · Engine Lexicon — All Modules & Types in Sly Cooper", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md70", [
        [ "Math, Geometry & Base Types", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md71", null ],
        [ "World Object System (LO / ALO / SO / SW)", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md72", null ],
        [ "Animation System (AC* / ASEG / ACT / BLEND)", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md73", null ],
        [ "Physics, Gameplay & Sly Movement (JT / XP / DZG)", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md74", null ],
        [ "Graphics Rendering (GLOB / GIFS / VIFS / SHD / RPL)", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md75", null ],
        [ "Engine Systems (BRX / CLOCK / SPLICE)", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md76", null ],
        [ "Splice — Scheme-like Scripting Engine (P2/splice/)", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md77", null ],
        [ "Enemies, Gameplay & Interactive Objects", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md78", null ]
      ] ],
      [ "</blockquote>", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md79", null ],
      [ "17 · decomp.me — Tips for Getting the Most Out of It", "md_docs_2mips__ps2__cheatsheet.html#autotoc_md80", null ]
    ] ],
    [ "Style Guide", "md_docs_2STYLEGUIDE.html", [
      [ "Contents", "md_docs_2STYLEGUIDE.html#autotoc_md83", null ],
      [ "General Rules", "md_docs_2STYLEGUIDE.html#autotoc_md84", null ],
      [ "Symbol Names", "md_docs_2STYLEGUIDE.html#autotoc_md85", [
        [ "Capitalization", "md_docs_2STYLEGUIDE.html#autotoc_md86", null ]
      ] ],
      [ "Documentation", "md_docs_2STYLEGUIDE.html#autotoc_md87", [
        [ "File Comments", "md_docs_2STYLEGUIDE.html#autotoc_md88", null ],
        [ "Function Comments", "md_docs_2STYLEGUIDE.html#autotoc_md89", [
          [ "Class Comments", "md_docs_2STYLEGUIDE.html#autotoc_md90", null ]
        ] ],
        [ "Todo and Notes", "md_docs_2STYLEGUIDE.html#autotoc_md91", null ]
      ] ],
      [ "Example Code", "md_docs_2STYLEGUIDE.html#autotoc_md92", null ]
    ] ],
    [ "Todo List", "todo.html", null ],
    [ "Deprecated List", "deprecated.html", null ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", "functions_vars" ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", "globals_func" ],
        [ "Variables", "globals_vars.html", "globals_vars" ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Enumerator", "globals_eval.html", "globals_eval" ],
        [ "Macros", "globals_defs.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"989snd_8c.html",
"ac_8h.html#a9eb508a72b70ba9fafcade2c20c0649c",
"alo_8c.html#a5dccdcbf02cd26c5efe76456487ea21c",
"alo_8h.html#a6cf29b34cbc93abf861b02f9d87062d0",
"barrier_8h.html#ae64a4551dcede0f1c7a9599454ac764e",
"bif_8h.html#a4eceef13fad5fb64e08b448b5cfab173",
"blip_8h.html#a35f1d658f1ea64fdf2594c0cff56e9f6",
"button_8h.html#a24b0555c197f1347b4b276bbfccb5b94",
"cid_8h.html#a5a95f696191e6e81c14198ad0c7792f4aafd508f711e5b9ae3d14d8574448e25d",
"classCMpeg.html#a2e5213e17d42e3b170cb761c4d0b0f0b",
"clip_8c.html#a3ad3649b3dc8d4ddc8b47ce50286d84f",
"coin_8c.html#a59b2fa49b130d9f62da22e1920498fcc",
"crv_8h.html#adc4f700a9890a5faa28e9ae491ab4fc3",
"dmas_8h.html#a174ee89df422e24309d395206458daa7",
"eval_8h.html#acd896768088f2cdcf8f9170a6456ea8e",
"frm_8c.html#ab9d3e8e54f657f2226bf35fe1481358b",
"game_8h.html#a7ea6a30556e6c301a85803b8f767ef5e",
"gs_8h.html",
"joy_8h.html#a36a5e3ae90f39dc35fcc17465ad1c8f6a9d7aeb25c9d0f72cff55f867503d4f69",
"jt_8h.html#a68314d7340e742bcdb56d3f5afe1d02eae03722bb1a63eff16cfa82a6186d13cb",
"light_8c.html#a2f92da3a3f93e1e2130ad8acdd1641fb",
"mark_8h.html#ae9fa1214e7e33c5bf23e5e41ae1fa1c9a13d05c2393599101ee9c90aa9978429a",
"memcard_8c.html#adf221d7f57cc30ec6f0f777112e644d7",
"oid_8h.html#a09ed43a0c8361f9f5a9428ae38d34b26adedc54e9f395ec2961e66afaff4917bc",
"prompt_8h.html#aeb0746a396bac9c423378f0ad165ae0daeb21d4e5b6f9c10d19ae911f180d1b78",
"rchm_8c.html#a2d3a04aefe232e00e77359b984985ff3",
"rip_8c.html#afdf515a68cb6afdb69acc7b69058209f",
"rog_8h.html#a3d94197c1035abc37601ea505a8d0498a46bfdb0dba9a0ecf68090fabea9dae72",
"screen_8c.html#a255995ff4aa2398fe2284130ed77ecd0",
"sensor_8h.html#a028944a31cd11ad38999910637a0a75b",
"shdanim_8c.html#a8e950097410e056bbeb2872e003e57ff",
"so_8c.html#a8d1b7276341ddb135bb41601e8636fc4",
"sound_8c.html#ac351533374e36eb3fb26bcb1fccd50ff",
"sprbuf_8h_source.html",
"stepguard_8h.html#a344180f4f59a4a7dacb5fab3c2216a50a7e95b555e790e7e5da2cfeba53b9ca7d",
"structACPBL.html",
"structBLOT.html#ae8a199476e0f3715203f2d6b1076c690",
"structCPALIGN.html#ab70b17c9482007d4febed846e9e540d7",
"structDZG.html#a12767d05003c6bc22b87fe554fa1937c",
"structHP.html",
"structMVG.html",
"structRUMPAT.html#a14f65bb19249149ffc5de84477f73827",
"structSURF.html#a8e5983b4418e1f66f031dc810c48a988",
"structVTALO.html#a183b4dfbffdc8d1131ce2efaadee2090",
"structVTTOTALS.html#ac2036f4da957866f6300b704fe841fce",
"structtD__CHCR.html#a783e9298084ebcbcd8a07e891653c8df",
"target_8h.html",
"tv_8h.html#ae8c0b6116e14047997f631c023940952a18308aa903cf1cdbc57118ea1d723708",
"vecmat_8cpp.html#a46b0a8799a94e8a889ddd1288413cfd9",
"wm_8h.html#ad638bf699a5a16c65055160a4d2fca64aa6ed722289eb9c5ec511711f19b02666"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';