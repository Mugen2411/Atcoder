pushd %~dp0
setlocal enabledelayedexpansion

chcp 65001
set MODULE_DIR=module

for %%F in ("%MODULE_DIR%/*.cpp") do (
    for /f "delims=" %%S in (%MODULE_DIR%/%%F) do (
        echo %%S
    )
    echo;
)
for /f "delims=" %%S in (template/main.cpp) do (
        echo %%S
    )

popd