
Step1 git clone wherever
Step2 patch vcvarsall.bat in "dual_build.bat" file
Step3 git clone "4coder non-source" into the cloned repository
-> https://github.com/Dion-Systems/4coder-non-source.git

You can split the builds apart in dual build if you would like, but if you want a complete build,
you will have to build the source *then* build the custom layer. 

to learn how to make custom commands you can look at code\custom\4coder_examples.cpp
and for user defined "custom_layer_init" function stuff you follow 
https://4coder.handmade.network/forums/articles/t/7319-customization_layer_-_getting_started__4coder_4.1_


Copyright (c) 2022 Allen Webster

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

