echo off
pushd %~dp0
setlocal enabledelayedexpansion

chcp 65001
set MODULE_DIR=module
set TARGET_NAME=%1

if exist %TARGET_NAME% del %TARGET_NAME%

for %%F in ("%MODULE_DIR%\*.cpp") do (
    echo "%%F"
    cmd /u /c type "%%F" > $$$
    cmd /c type $$$ >> "%1"
    del $$$
    echo; >> "%1"
)

cmd /u /c type "template\main.cpp" > $$$
cmd /c type $$$ >> %1
del $$$

endlocal
popd