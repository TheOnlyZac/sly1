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
"break_8c.html#ab3e942db7f8dad4042b357237293cbb1",
"cd_8c.html#ac47d6b5f363b360d598f06fd3d3c3a3e",
"classCBinaryAsyncStream.html#a587367762fa14ad65e9279f964d9fd11",
"classCRichText.html#a1f995261e3cd76a8c8b9220c576893e0",
"cm_8c.html#a1a55bd3feeefa6f0e574ce74f444ad47",
"common_8h.html#a572ae999f74b9e5b7ec2f936d3036f15",
"dartgun_8c.html#af81eba10990fc8ad37f21a495798de30",
"emitter_8c.html#a0c47c6f30929f29fae52a45c35ffb7c4",
"find_8h.html#a3f150d8fe7ba2fae45d4f09c24cb60f0",
"functions_q.html",
"glbs_8c.html#a5552113fb6c376d7e65aff77829cb282",
"hide_8h.html#a35a18eb1be3ab44fa00041434617e679a0628660adfac2a04d488acd61820ed4a",
"joy_8h.html#ac987ccc8ebf81c9ab5b574f4ded366c9",
"jt_8h.html#aeec8cd48f7842e2652f6eff1e3476315ae0db6b0e505fe26cb7cce230a9775bbe",
"light_8h.html#a6ec7102d9cb863b1f2388251a80703e6",
"mat_8c.html#adaeaac62e19955f567310b896bade7e4",
"memory_8c.html#ad2af9373fb312125f9b22b9267e109a5",
"phasemem_8c.html#a2ef647a0ddd9076a74b6060a83c747b4",
"puffer_8c.html#abf9e80726d90de70ddd62539982c2fb8",
"ref_8h.html#a4e55c80470e633730d036482bd72bd52",
"rip_8h.html#a34f1ddfa7da41f2830885b533a215dcaa214556ef436047310356290498b2befb",
"rog_8h.html#a820f5c361f53e15f86474a2d60a875d1",
"screen_8c.html#a75882ae226c4a62eade2e135032df1d9",
"sensor_8h.html#a5dcd55e97d43491d17306b50be122458aa1bdd52d36802e205127a11bef375012",
"shdanim_8c_source.html",
"so_8c.html#addfb9c9dd6514aa279aa0c3a6cd323d5",
"sound_8h.html#a34e9cff1b7a75a2c6744fadf0d600dbaa0352cf78dd44faa3bb8ab201419d20fe",
"step_8c.html#a9f2924761d09c018dde6f82df1901858",
"stepguard_8h.html#aba35f227c19848f951158675645f6233",
"structACRC.html",
"structBLIP.html#a4b86c9e97dafce4f7108656a9c8b376c",
"structCM.html#abc1a64842207d0e80287e99b74efe808",
"structDPRIZE.html#a25dad13c12498436212c2e44e789fe9d",
"structGLBS.html#a319e78d8c956e5d30e5e0dcb33cf68f4",
"structLO.html#ab9db8626b158470ff34f2831563fb6de",
"structRAIL.html",
"structSHADOW.html#a3be2c1604248130ff2332df5274ed8da",
"structSndSystemStatus.html",
"structVTBINOC.html#ae6e19bdbd0f9045e06ea65ae61fcdbac",
"structVTPRSEN.html#a27733a615397ebfa30ac9ace531ac192",
"structVTTOTALS.html#a55ae2a1042c564566d05ea1600978b5e",
"structsceDmaChan.html#ae610b1a3becfe081d4c7e9c719cfbb04",
"tank_8h.html#aeeaa214fa74ab67aa4be284801c57a8ba454dae78171ad15c5be6aa21e10deeba",
"tv_8h.html#aa6011b1023060c5a67ce3ebaf0268f8a",
"vb_8c.html#a5a12944311383a259d5d7d191830d1a1",
"waypoint_8c.html#a2e9388a107b5bbe8af8e060a3a9c626f",
"xform_8h.html#a8ba07e7dbf196364d740679cc15b4ed3"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';