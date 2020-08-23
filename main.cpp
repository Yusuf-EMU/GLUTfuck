#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#if ( (defined(__MACH__)) && (defined(__APPLE__)) )   
#include <GLUT/glut.h>  
#else 
#include <GL/glut.h>
#endif

std::string commands;

std::string inputFile(const std::string& filename)
{
    std::string commands;
    std::ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Failed to open '" + filename + "'.");

    while (file.good()) {
        commands.push_back(file.get());
    }

    return commands;
}

void interpretCode(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     // Clear Screen and Depth Buffer
	glLoadIdentity();
    std::vector<int> data(1, 0);
    std::vector<int>::iterator dataPtr = data.begin();

    std::string::const_iterator instructionPtr = commands.begin();
    std::stack<std::string::const_iterator> instructionStack;

    while (instructionPtr != commands.end())
    {
        switch (*instructionPtr)
        {
        case '<':
        {
            dataPtr--;
            break;
        }
        case '>':
        {
            dataPtr++;
            if (dataPtr == data.end()) {
                data.push_back(0);
                dataPtr = data.end()-1;
            }
            break;
        }
        case '+':
        {
            (*dataPtr) += 1;
            break;
        }
        case '-':
        {
            (*dataPtr) -= 1;
            break;
        }
        case '.':
        {
            std::cout << char(*dataPtr);
            break;
        }
        case ',':
        {
            char input;
            std::cin >> input;
            *dataPtr = input;
        }
        case '/':
        {
            glBegin(GL_TRIANGLES);	
                if((*dataPtr) == 1) {
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else if((*dataPtr) == 2) {
                    glColor3f(0.0f, 1.0f, 0.0f);
                }		
                else if((*dataPtr) == 3) {
                    glColor3f(0.0f, 0.0f, 1.0f);
                }	
		else if((*dataPtr) == 4) {
                    glColor3f(1.0f, 1.0f, 1.0f);
                }
                //glColor3f((*(dataPtr + 2)),(*(dataPtr + 1)), (*(dataPtr + 3)));			
                glVertex3f( 0.0f, (*dataPtr), 0.0f);				
                glVertex3f(-(*dataPtr),-(*dataPtr), 0.0f);		
                glVertex3f( (*dataPtr), -(*dataPtr), 0.0f);		
            glEnd();
        }
        case '[':
        {
            instructionStack.push(instructionPtr);

            if (*dataPtr == 0)
            {
                auto startInstructionPtr = instructionPtr;
                while (++instructionPtr != commands.end())
                {
                    if (*instructionPtr == '[')
                        instructionStack.push(instructionPtr);
                    else if (*instructionPtr == ']')
                    {
                        if (instructionStack.empty())
                            throw std::runtime_error("Found a ']' that did not have a matching '['!");

                        auto tempInstructionPtr = instructionStack.top();
                        instructionStack.pop();

                        if (startInstructionPtr == tempInstructionPtr)
                            break;
                    }
                }
            }
            break;
        }
        case ']':
        {
            if (instructionStack.empty())
                throw std::runtime_error("Found a ']' that did not have a matching '['!");

            if (*dataPtr != 0)
                instructionPtr = instructionStack.top();
            else
                instructionStack.pop();

            break;
        }
        default:
            break;
        }

        instructionPtr++;
    }

    if (!instructionStack.empty())
        //throw std::runtime_error("Found a '[' that did not have a matching ']'!");
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(900,900);
	glutCreateWindow("GLUTfuck");
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    
    if (argc != 2)
    {
        std::cout << "Usage: ./bf-interpreter input.bf" << std::endl;
        return 1;
    }

    try
    {
        commands = inputFile(argv[1]);
        // register callbacks
	    glutDisplayFunc(interpretCode);
        //interpretCode();
    }
    catch (const std::exception& e)
    {
        std::cout << std::endl << e.what() << std::endl;
    }
    // enter GLUT event processing cycle
	glutMainLoop();

    return 0;
}
