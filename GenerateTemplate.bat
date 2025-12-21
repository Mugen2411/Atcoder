echo off
pushd %~dp0
setlocal enabledelayedexpansion

chcp 65001
set MODULE_DIR=module
set TARGET_NAME=%1

if exist %TARGET_NAME% del %TARGET_NAME%

if not exist %~dp1 mkdir %~dp1

for %%F in ("%MODULE_DIR%\*.cpp") do (
    echo "%%F"
    rem 一旦BOMを消すためにANSIを通す
    cmd /u /c type "%%F" > $$$
    cmd /c type $$$ >> "%1"
    del $$$
    echo; >> "%1"
)

rem 一旦BOMを消すためにANSIを通す
cmd /u /c type "template\main.cpp" > $$$
cmd /c type $$$ >> %1
del $$$

endlocal
popd