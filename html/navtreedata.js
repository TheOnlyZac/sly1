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
"ac_8h.html#a636c14e0f5e43fac083bf9b29619fe2b",
"alo_8c.html#a3cb5b167affa09376803406f37ec3a44",
"alo_8h.html#a57782ef08b1b5e9831ffcbb4615c2b85",
"asega_8c.html#aee751e72022ba31bde95ecb084a754d1",
"bif_8cpp.html#af6ba791cb4b3f764839631a86e8745d2",
"bif_8h.html#acc7f2cc3bcc369e94ad25b1e32d5071c",
"break_8c.html#a6c35318ac30a511482ffb7c67043dab7",
"cd_8c.html",
"classCBinaryAsyncStream.html#a052611951d67b5560489f4ba7d84ea86",
"classCProg.html#a76885d900fb7ecaac744dc01e95af183",
"clip_8c.html#a3bb17e1a1851663a18fea177dbecc758",
"coin_8h.html#a278f27aa0df68ffcb451a8de1766e0a5a49a37dbac635011a5ef84e90b60e84b6",
"crv_8h.html#a62667ba24cb9b05e105d769139008ee5a26cca9369299002a481535a6d38c7208",
"dl_8h.html#a9a51742381a1ad6110e71ef01c3f43b4",
"eval_8cpp.html#a7770e481a1d742c80859b8449722d71c",
"freeze_8h.html#ace3ab351d84913e4634137197a4c4fc2",
"game_8h.html#a73a5f862a351662bf22487f62e26cb5eac121f4d6ee069b10a5185c8f778aa2b0",
"gomer_8h.html#ab5eb07af5f8b27b5e6dfb75bb08b0041a20159642c3559d40c55cabb784a31255",
"joy_8c.html#a8346488b34dd9b9bbdff75c95744f534",
"jt_8c.html#adda9368c3004a2607d0bdfccf7466c51",
"libdma_8h.html",
"lookat_8h_source.html",
"md_docs_2mips__ps2__cheatsheet.html#autotoc_md44",
"mpeg_8h_source.html",
"po_8h.html#a9abacc433defe714d4f95acfe9418414a3da8d30a2026ea03257ed068a3dc0255",
"pzo_8h.html#a6a170e17b67e5e15c46bf964bd40ec75",
"render_8h.html#a5c3c59dc9181cd0234cd60fe7c7b4fca",
"rip_8h.html#afd3174b00666ea8ffe9d6558b4808041ad1131ba90e054f9ae76adc0d62ab25e5",
"rumble_8h.html",
"screen_8h.html#a6c9aeebc87b228a4a4ea0d0e018c10caa323f85d53955a19f16f3fb7231a7af20",
"shape_8c.html#ab0c857a46e5d075c7e91d51b6cc14aa2",
"sm_8c.html#a6bf783ede7664630c106b424dfd8fbc9",
"so_8h.html#ad401e0b460a8ee5eecff0c70e4e36caf",
"sound_8h.html#a615a90ab3a1f58d2ceee86ad3bc85ee7",
"stepguard_8c.html#a1fd5dc98e9e4d5308e580d77ba623711",
"stephide_8c.html#ad36eb337d7094958738f2ebcbe154953",
"structALO.html#a234580c9d6a2b5a2e5b6c0c11089b84e",
"structBRP.html",
"structCPTN.html#aacfda61ac99de9ef8958357e6ac8baf7",
"structEXIT.html#a4d89faced4962c3211b51f1e6fbdf4df",
"structJOY.html#a3f8575a8fa15b7bdb1ad2d924e05897e",
"structMEMCARD.html#a76c9612cec885a36f749026f8d56e61d",
"structRPL.html#a4d95a12a6d72c37439b4ce5a3d87f901",
"structSPLOPT.html#a003afa669a5dbcdf28ace4db806613f7",
"structTRANS.html#a8b8e840ec3ce25d4c55855c5f49705ad",
"structVTCAMSEN.html#aa0ff09b18ea26675adabd41afd959b3b",
"structVTPRSEN.html#abe37aab27d4a5e13ca0a33bc6f428c9c",
"structWARP.html#a7cfcaec8df2a0d7ddc3cef602e77d41d",
"suv_8c.html#a28aa1cca79a30ca23ae78e377ccbf352",
"text_8c.html",
"types_8h.html#a27c902d5ca78afa82d5ed75554d5cedc",
"vb_8c.html#aa55ec47d3e0b63a5afc19a60abb265bf",
"waypoint_8h.html#a5accaa7e9dff79fbe9397a572c538e66a7235b65b71036a6235df7d40c927af88",
"zap_8c.html#a9487f02fdb3d5816db12d97291d9467c"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';