@echo off

[PATCH vcvarsall.bat] here!

echo ---
echo --- building 4coder source ---
echo ---

pushd code\
call bin\build.bat
popd

echo ---
echo --- building ryan's custom layer ---
echo ---

pushd build\custom\
call 4coder_fleury\build.bat
popd