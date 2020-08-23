# GLUTfuck
OpenGL for BrainFuck

The base code is from texus(https://github.com/texus/Brainfuck-interpreter) I just added GLUT functionallity
To run this you need GLUT + Opengl

Compile & Run
-------------

    g++ bf-interpreter.cpp -std=c++11 -o bf-interpreter

    ./bf-interpreter input.bf

I added one extra command with more to come to draw a triange "/" with the current cell being the size (add the next cell being the color value NOTE:ITS BROKEN)
