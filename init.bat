
pushd %~dp0
setlocal enabledelayedexpansion

rem ファイルパスを設定
set folderName=%1

set sourceName=template\main.cpp
set fileNames[0]=A.cpp
set fileNames[1]=B.cpp
set fileNames[2]=C.cpp
set fileNames[3]=D.cpp

rem ターゲットとなるフォルダを作成
mkdir %folderName%

rem 各種ファイルをコピー
set cnt_copyied=0
:FOREACH_COPYFILE
set cur=!fileNames[%cnt_copyied%]!
if defined cur (
    copy "%sourceName%" "%folderName%\%cur%"
    set /a cnt_copyied+=1
    goto :FOREACH_COPYFILE
)

@echo on
popd
