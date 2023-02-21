__Code Matching Guide for Sly1 Decompilation Project__

Works only on Windows for now.

**1. Clone the Sly1 Git repo.**

`git clone https://github.com/TheOnlyZac/sly1.git`

**2. Download and extract the PS2 compiler collection (25MB in size).**

`https://archive.org/download/SNSystemsProDGPs2/ProDGPs2usrLocalSceFiles.zip`

Extract it to your `C:\` drive.
Once extracted, the path structure should look like: `C:\usr\local\sce\...`

If you are wondering why this step is needed, it will be useful for compiling our code (from the repo).
CodeMatcher will be able to match it against Sly1's original code.

**3. Get the Sly1 Prototype ELF.**

Find the Sly1 May Prototype ISO online, download it and extract the ELF inside it to the `tools` folder, alongside `match_all.cmd`. We will need it for code matching. Name it `sly_proto.elf`.
We cannot provide this file via the GitHub repo for copyright reasons.

**4. Match your code.**

Run `match_all.cmd` from the tools folder in the repo to compile the source tree and perform a function match.
A summary of the process will be displayed, including functions that do match and which do not.

Good luck, and have fun!