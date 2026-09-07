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
"crv_8h.html#ae0ebbe595526f52311cffea13556b883",
"dmas_8h.html#a8ee4409bb43ebb43e92fb7001014a8b3",
"eval_8h.html#ae6cb8f147011061b6f0659c4ec968f6b",
"frm_8c.html#ac9159d95f6c68be29c93901e5fccfed0",
"game_8h.html#a84d86025c83f3d5df6e1ed220c174b59",
"gs_8h.html#a0d576f975dedbfed1400a5b25a13e2bc",
"joy_8h.html#a36a5e3ae90f39dc35fcc17465ad1c8f6aa5961ed03437ff7948a554332376c465",
"jt_8h.html#a70bb70478ddea29d37942e7173d5cf0c",
"light_8c.html#a39a2502b86559c8cfd98d3f3cfd703b2",
"mark_8h.html#ae9fa1214e7e33c5bf23e5e41ae1fa1c9a2b40aa853e2af3d2db4f7c57489088d9",
"memcard_8c.html#aede9e8eb0771abe34dc4b9699eb68ae2",
"oid_8h.html#a09ed43a0c8361f9f5a9428ae38d34b26af2cc295e76aada312ebb224d813d2e1b",
"prompt_8h.html#aeb0746a396bac9c423378f0ad165ae0daf51828b9f315055194e0fc3269f25994",
"rchm_8c.html#a5eecc739a31550dbe4e510eb90bf4b1c",
"rip_8c_source.html",
"rog_8h.html#a3d94197c1035abc37601ea505a8d0498a76fa5b98067bc8bad14de02b0c221f94",
"screen_8c.html#a2cb78dc9d6871bd1a27c60e2fbca5878",
"sensor_8h.html#a29737ed6568e42c6a2655dd4648e7c44",
"shdanim_8c.html#a9d9a46a3f3ea2cf50c01bda298c0bb17",
"so_8c.html#a90a0f62a323c87890a4c76c2b8c1ed38",
"sound_8c.html#ac9aff12bb2a06547647456d076e4c2f5",
"sqtr_8c.html#a04aaac63c61fd89ddef2bf270d13605b",
"stepguard_8h.html#a34c75c18dea99cc504577b438996f8ab",
"structACR.html",
"structBLOT.html#af2a182b75b363c63e7ec7be9851c3cef",
"structCPASEG.html",
"structDZG.html#a84015932158b4fb7ad8d591f2e715078",
"structHP.html#a33cae8ec4a4a6a93511ef43577d0feb2",
"structMVG.html#a2bedbb0194d53c82c66da872cb868828",
"structRWAC.html",
"structSURF.html#ae9c91d14997f43caa8ce78c0a701449c",
"structVTALO.html#a1ce6504746efe46ccaf9f6aede039443",
"structVTTOTALS.html#acb7ee9a8227f812b0d68a129ff1c203a",
"structtD__CHCR.html#ab0c7fa6a0dbc9f13c81a9ecc00129fa5",
"target_8h.html#a42a1daaed818afbc30034369f206bb66",
"tv_8h.html#ae8c0b6116e14047997f631c023940952ae124c1abe81074324526b7b55b47afdc",
"vecmat_8cpp.html#a581acb3acb7bcda07c157928d5368362",
"wm_8h.html#ad638bf699a5a16c65055160a4d2fca64aca72dfaf16b53b136645c0dfdc63cc58"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';