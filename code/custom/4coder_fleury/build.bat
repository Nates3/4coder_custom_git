@echo off

pushd ..\..\build
call ..\code\custom\bin\buildsuper_x64-win.bat ..\code\custom\4coder_fleury\4coder_fleury.cpp release
REM copy .\custom_4coder.dll ..\custom_4coder.dll
REM copy .\custom_4coder.pdb ..\custom_4coder.pdb
popd

REM call ..\bin\buildsuper_x64-win.bat .\4coder_fleury.cpp debug
REM copy .\custom_4coder.dll ..\..\custom_4coder.dll
REM copy .\custom_4coder.pdb ..\..\custom_4coder.pdb