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


REM download_and_check: URL
REM downloads files and uses certutil to verify integrity
:download_and_check
echo Downloading %~1 and certutil hashes...
curl -sS %~1 -o %TEMP%\%~nx1
curl -sS %~1.b2 -o %TEMP%\%~nx1.b2

REM download files to %TEMP% and verify hashes
pushd %TEMP% >nul
certutil -hashfile %~nx1 SHA256 | findstr /i /c:"%~nx1.b2" >nul || (
    if errorlevel 1 (
        call :die "certutil hashes failed to verify when downloading %~1"
    )
)
popd >nul

echo certutil hashes verified, moving files from %TEMP% to %CD%
del %TEMP%\%~nx1.b2
move %TEMP%\%~nx1 %CD%
goto :eof


REM start
REM main entrypoint
:start
REM download required files (registry + SDK package)
call :download_and_check "https://computernewb.com/~lily/sly1/prodg_env.reg"
call :download_and_check "https://computernewb.com/~lily/sly1/prodg_sce%SDK_VER%.7z"

REM apply environment variables from the registry file
echo Applying environment variables, please accept the UAC prompt
regedit %TEMP%\prodg_env.reg

REM Extract the SDK into the C: drive
echo Extracting SDK to C:\...
7z x -y prodg_sce%SDK_VER%.7z -oC:\ -bso0 -bse2 -bsp0

::echo Removing temporary files
echo Removing temporary files...
del prodg_sce%SDK_VER%.7z
del prodg_env.reg

echo Setup complete!
endlocal
