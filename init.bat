
pushd %~dp0
setlocal enabledelayedexpansion

rem ファイルパスを設定
set folderName=%1
set generateName="gen_main.cpp"

rem ブランチ切ってチェックアウト
git checkout master
git pull origin master
git branch %folderName%
git checkout %folderName%

rem テンプレートファイルを生成
call GenerateTemplate.bat %generateName%

rem 作成するファイル名たちを指定
set fileNames[0]=A.cpp
set fileNames[1]=B.cpp
set fileNames[2]=C.cpp
set fileNames[3]=D.cpp
set fileNames[4]=E.cpp

rem ターゲットとなるフォルダを作成
mkdir %folderName%

rem 各種ファイルをコピー
set cnt_copyied=0
:FOREACH_COPYFILE
set cur=!fileNames[%cnt_copyied%]!
if defined cur (
    copy "%generateName%" "%folderName%\%cur%"
    set /a cnt_copyied+=1
    goto :FOREACH_COPYFILE
)

rem 後始末
del %generateName%

@echo on
popd
