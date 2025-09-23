REM backup registry to C:\usr\local\sce\regbackup.reg
echo Backing up registry, please accept the UAC prompt
regedit /E C:\usr\local\sce\regbackup.reg "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment"
