@echo off
setlocal

REM The SDK (Runtime Library) version to install.
set SDK_VER=242

echo Starting ProDG setup script...
goto :start


REM die: MESSAGE
REM perl-style `die` expressions.
:die
echo Error: %*
exit /b 1


REM download_file: URL
REM downloads file using curl
:download_file
echo Downloading %~1...
set output_file=%TEMP%\progd.zip
curl -L %~1 -o %output_file%
if exist "%output_file%" (
    echo File downloaded to %output_file%
) else (
    call :die Failed to download file
)
goto :eof


REM start
REM main entrypoint
:start
echo NOTE This script is untested with the new build system and may not work as expected!
echo Please report any issues on github or discord.
echo

REM download required files (registry + SDK package)
call :download_file "https://github.com/TheOnlyZac/compilers/releases/download/ee-gcc2.95.2-SN-v2.73a/ee-gcc2.95.2-SN-v2.73a.zip"

::REM apply environment variables from the registry file
::echo Applying environment variables, please accept the UAC prompt
::regedit %TEMP%\prodg_env.reg

REM Extract the compiler to the project/tools directory
echo Extracting compiler to tools directory...
7z x -y %TEMP%\progd.zip -otools

::echo Removing temporary files
echo Removing temporary files...
::del %TEMP%\ee-gcc2.95.2-SN-v2.73a.zip

echo Setup complete!
endlocal
