# Build Instructions

## Step1 
HTTPS: `git clone --depth 1 https://github.com/Nates3/4coder_custom_git.git`  
SSH: `git clone --depth 1 git@github.com:Nates3/4coder_custom_git.git`

## Step2 
Navigate to `{RootDir}/code` (IMPORTANT!)  
Insert call to `vcvarsall.bat` in `{RootDir}/code/full_build.bat` file

## Step3 
call `full_build.bat`

## Bulid Settings
To change between debug or release -> {RootDir}/code/custom/bin/buildsuper_os.bat 
and change "mode" variable to "debug" or "release"

## Code
Most of the custom code is in `{RootDir}/code/custom/q7/` folder  
There is some custom code that is written in the backend half of the api implementation  
so not all of it is in the `{RootDir}/code/custom/` folder


## Info
To learn how to make custom commands you can look at code\custom\4coder_examples.cpp
and for user defined "custom_layer_init" function stuff you follow 
[Customisation Layer 4coder](https://4coder.handmade.network/forums/articles/t/7319-customization_layer_-_getting_started__4coder_4.1_)
                             the function should be in `code\custom\4coder_default_bindings.cpp`
                             
# 4coder Source
                             https://github.com/Dion-Systems/4coder
                             
                             ## License
                             Copyright (c) 2022 Allen Webster
                             
                             Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
                             The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
                             THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
                             
                             