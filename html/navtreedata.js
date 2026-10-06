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
"bif_8h.html#a2028d2cb968824c1d06bbcd80231c131",
"bif_8h.html#aeb8756f210900f8a151c0fecec21931aa8f15ebed37bf0c077e6bc83363085406",
"break_8h.html#a43a9809dd0d3fc849b7fcc3c4c943fc3a1ed5b934a14917f16f1b2be644dcdf4a",
"cd_8h.html#ae6b10fba6838f4797d7d575b4759d138a70573d6c3bc06655976c7f5a8daee3a9",
"classCBinaryInputStream.html#a0f265ff3c59c91bfaef207c59ee372c2",
"classCSidebag.html#a3c8b3734e773440dbce86af38331ce28",
"cm_8c.html#a55f47d31653867b2ecdcc8bf23062941",
"cplcy_8c.html#ada9063bd19403ea33f5e29e00d457230",
"deprecated.html",
"emitter_8c.html#a57c7c75c7cb0d5fab9f4c7d00a1c1b46",
"flash_8h.html#acd9816efa0004dc04512bb1fb62ab39a",
"functions_vars_n.html",
"glob_8c.html#a02f818d846da50b76e2b5c65f10827d0",
"ik_8c.html",
"jsg_8c.html#a762d531765abe3731846e00c55361bec",
"jump_8h.html#a6b91e0250f60cf3cdc2b6cf61186574e",
"lo_8c.html#a36efcb86ae6fd0b9f8fbc57d3ab1c410",
"mat_8h.html#ac58259518b324f7fc0a47c9bae0d276b",
"missile_8c.html#a35fed250718d16af428d552bb89572fb",
"pnt_8c.html#a21c56a9828f586ad7a02c8a2940a7624",
"pzo_8c.html#a13666bdd5f19ade00bf0077cef9a7467",
"ref_8h.html#a4e55c80470e633730d036482bd72bd52af03e3f108857e1255b5f86c89356d2ce",
"rip_8h.html#a9f750804cff29b19a97cefda01be856ea4a92911a4fbe5af73ebc5457133f560b",
"rog_8h.html#ab62973a2c7ee5f7ecf7992e18e97b1a8",
"screen_8c.html#abcb7a0283ae4f3f30e42bda5d8354ebe",
"sensor_8h.html#ae91767c7e5a00bdf872ebaa12c95a453",
"sidebag_8cpp.html",
"so_8h.html#a348162739dfc6455b73b853a0ffc3915af0569d7a4aaea820e492f7a8dbc0a26c",
"sound_8h.html#a34e9cff1b7a75a2c6744fadf0d600dbaa671fdfed3c6b49de58a3bda14e59e66d",
"step_8h.html#ab1dcb3526417b0503ed8a975432adc57",
"stepguard_8h.html#afdfda899ec2daf1f65f90ca19bf5e3c7",
"structACTLA.html#ac4889d7c589aece1043ba3b1e4fb2cb3",
"structBLOT.html#aa58e02d001d9e52f9bece7cd717afe97",
"structCOIN.html#a91b7f1073a54cb8bee954be8e80cf706",
"structDZ.html#a8ba799d536098b74690cfc4a527db0e7",
"structHND.html#a00832607c5c14d8f0c25abb027fc35c9",
"structLevelLoadData.html#a93d8240b9c9936e7fe65712c53790636",
"structRO.html#a90091f5042eab94f12f2afa48ed9b69a",
"structSTEP.html#a32743e5f31059cdbebf6edc73f551f4b",
"structUI.html#a22f59851a41a46dd7c3e3b517ad74e5e",
"structVTLASEN.html#a4021816b736834e744365abdbf07e018",
"structVTSENSOR.html#ab3d6683744a981a19d6aa40af29b2197",
"structWS.html#a64419610f0849af9f11ef542b27b358a",
"sw_8c.html#ad8701c1747ab97da675bc74d0793901b",
"tn_8c.html#af12fa8e77c5073285f46be0f383c78f2",
"unionTAG.html#a49cc48ac76183caaec40da76bb88a650",
"water_8c.html#ac12b0a856e7fe345b95dc466699f1525",
"xform_8h.html#a15165447365bf8df2c31f941ae051379"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';