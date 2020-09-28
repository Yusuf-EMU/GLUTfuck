# GLUTfuck
OpenGL for BrainFuck

The base code is from texus(https://github.com/texus/Brainfuck-interpreter) I just added GLUT functionallity
To run this you need GLUT + Opengl

Compile & Run
-------------

    g++ main.cpp -std=c++11 -framework GLUT -framework OpenGL  -obf-interpreter -O1

    ./bf-interpreter input.bf

Use ',' to draw a triange with the current cell being the size (add the next cell being the color value NOTE:ITS BROKEN)
Use '.' to draw a cube with the current cell being the size.
