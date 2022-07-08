# Build Instructions

## Step1 
HTTPS: `git clone --recursive https://github.com/Nates3/4coder_custom_git.git`  
SSH: `git clone --recursive git@github.com:Nates3/4coder_custom_git.git`

## Step2 
Navigate to `{rootDir}/code` (IMPORTANT!)  
Insert call to `vcvarsall.bat` in `{rootDir}\code\full_build.bat` file

## Step3 
call `full_build.bat`

## Info
To learn how to make custom commands you can look at code\custom\4coder_examples.cpp
and for user defined "custom_layer_init" function stuff you follow 
[Customisation Layer 4coder](https://4coder.handmade.network/forums/articles/t/7319-customization_layer_-_getting_started__4coder_4.1_)
the function should be in `code\custom\4coder_default_bindings.cpp`

# State of the Project
https://github.com/Nates3/4coder_custom_git/projects/1

## License
Copyright (c) 2022 Allen Webster

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

