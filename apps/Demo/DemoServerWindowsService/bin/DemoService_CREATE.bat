@echo off
cls
echo.
echo *** CREATE ConnectedVisionDemoServer***
echo.
sc create ConnectedVisionDemoServer binPath= "%~dp0DemoServerWindowsService.exe"
echo.
pause
