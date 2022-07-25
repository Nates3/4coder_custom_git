@echo off

@REM [REPLACE THIS FOR YOU]
call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 1>NUL 2>NUL

call ..\misc\api_parser.exe 4ed_api_implementation.cpp
echo ------------------------ building 4coder source -----------------------------
call bin\build.bat 