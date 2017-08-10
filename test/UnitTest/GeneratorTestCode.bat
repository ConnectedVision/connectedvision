@ECHO off
setlocal

SET CV_CPP_PATH=%ConnectedVision%

REM remove trailing backslash
IF %CV_CPP_PATH:~-1%==\ SET CV_CPP_PATH=%CV_CPP_PATH:~0,-1%

SET TOOLS_PATH=%CV_CPP_PATH%\tools
SET TARGET_PATH=%CV_CPP_PATH%\test\UnitTest
SET SCHEMA_FILE=%TARGET_PATH%\GeneratorTestCode.schema
SET FOLDER_STRUCTURE=%TARGET_PATH%\GeneratorTestCodeStructure.json

SET PARAMS=-f %1 %2 %3 %4 %5

ECHO %SCHEMA_FILE%
ECHO -----------------

ECHO CreateItemsForSchema.js
CALL node.exe %TOOLS_PATH%\CodeFromTemplate\CreateItemForSchema.js %TARGET_PATH% %CV_CPP_PATH% %SCHEMA_FILE% %FOLDER_STRUCTURE% -id UnitTest %PARAMS%

if %errorlevel% neq 0 exit /b %errorlevel%

ECHO CodeFromTemplate.js - DATA items
CALL node.exe %TOOLS_PATH%\CodeFromTemplate\CodeFromTemplate.js %TARGET_PATH%\global.json %TARGET_PATH%\items.json %PARAMS%

if %errorlevel% neq 0 exit /b %errorlevel%

ECHO Clean Up
DEL %TARGET_PATH%\global.json >NUL 2>&1
DEL %TARGET_PATH%\items.json >NUL 2>&1
DEL %TARGET_PATH%\artefacts.json >NUL 2>&1

ECHO.

ECHO OK

:END