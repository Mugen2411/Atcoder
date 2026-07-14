echo off
pushd %~dp0
setlocal enabledelayedexpansion

chcp 65001
set MODULE_DIR=module
set TARGET_NAME=%1

if exist %TARGET_NAME% del %TARGET_NAME%

if not exist %~dp1 mkdir %~dp1

copy "template\main.cpp" %TARGET_NAME%

endlocal
popd