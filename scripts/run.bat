@echo off

REM ##############################################################################
REM Set these paths to point to your PCSX2 1.7 executable and your copy of the game
set PCSX2_PATH="C:\path\to\pcsx2.exe"
set ISO_PATH=""
REM ##############################################################################

goto :start

REM die: MESSAGE
REM perl-style `die` expressions.
:die
echo run.bat: error: %*
exit /b 1

REM start
REM main entrypoint
:start
if not defined PCSX2_PATH (
    call :die "PCSX2 path is empty, please edit the paths in 'run.bat'"
)
if not defined ISO_PATH (
    echo Warning: ISO path is empty, please edit the paths in 'run.bat'
)
if not exist "!ISO_PATH!" (
    call :die "Game ISO not found at '!ISO_PATH!'"
)
if not exist "!PCSX2_PATH!" (
    call :die "PCSX2 executable not found at '!PCSX2_PATH!'"
)
if not "!PCSX2_PATH:~-4!"==".exe" (
    call :die "PCSX2 exe is not executable"
)

REM Switch to the project root directory
pushd "%~dp0..\.." > nul

REM Build the game
echo Compiling ELF...
::make clean > nul
make > nul

REM Run the game
echo Booting ELF in PCSX2...
"%PCSX2_PATH%" -nogui -console -elf ".\bin\debug\SCUS_971.98" "%ISO_PATH%"

REM Switch back to the original directory
popd > nul
echo Done.
