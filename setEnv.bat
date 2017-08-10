@echo off

set dirPath=%~dp0
if %dirPath:~-1%==\ set dirPath=%dirPath:~0,-1%

echo setting environment variable "ConnectedVision" to:
echo %dirPath%
echo.

setx -m ConnectedVision "%dirPath%"
echo.

pause