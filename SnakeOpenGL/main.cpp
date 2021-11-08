#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include "game.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

#define COLUMNS 64
#define ROWS 48
//frames per second
#define FPS 5

extern short sDirection;
bool gameOver = false;

int score = 0;

void timer_callback(int);
void display_callback();
void reshape_callback(int, int);
void keyboard_callback(int, int, int);

void init(){
    // change default black background to pleasant green background
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // grid is initialized
    initGrid(COLUMNS, ROWS);
}

int main(int argc, char**argv) {
    glutInit(&argc,argv);
    // double buffer window with RGB mode
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800,600);
    glutCreateWindow("Snake");
    // to initialize the display, needs display_callback
    glutDisplayFunc(display_callback);
    // called when the window is created, minimized, maximised or extended to any direction(size changed)
    glutReshapeFunc(reshape_callback);
    // should be called before main loop
    glutTimerFunc(0, timer_callback, 0);
    // accepting user input
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop();
    return 0;
}


void display_callback() {
    // clears the buffer specified by the argument
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    // grid is drawn every time a new frame is displayed
    drawGrid();
    drawSnake();
    drawTreat();
    /* after display_callback draws the screen need to sweep the buffer (not swept automatically)
       important to know that some delay is introduced by swap buffers,
       means that FPS is not exactly 10
       gives higher FPS if delay in not introduced */
    glutSwapBuffers();
    if(gameOver) {
        exit(0);
    }
}



// takes 2 arguments width and height after it is resized
// width and height of the window is passed by glut to reshape fallback function
void reshape_callback(int w, int h) {
    // initialize Viewport
    // need to cast to GL size (GLsizei) as w, h are integers
    glViewport(0, 0, (GLsizei) w,(GLsizei) h );

    // switch to projection matrix need to pass below enumeration GL projection to the function
    glMatrixMode(GL_PROJECTION);
    // make sure that no changes yet are made to the matrix, default 'no changes' at the beginning
    glLoadIdentity();
    // set up the projection, 2 choices available: perspective(3D) and orthographic(2D is ok) projection
    // initialize system coordinates, x, y, z coordinates (z nearest -1.0 is closest and 1.0 is the furthermost)
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
    // switch back to a model view matrix as the rest of the activities take part in the model view matrix
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int) {
    glutPostRedisplay();
    // unregistered after the 1st call from main, need to bee registered again
    // manually setting the value of FPS so the snake does not move too fast
    glutTimerFunc(1000/FPS, timer_callback, 0);
}

// snake is not able to move 180 degrees!
void keyboard_callback(int key, int, int) {
    switch(key){
        case GLUT_KEY_UP:
            if(sDirection != DOWN)
                sDirection = UP;
            break;
        case GLUT_KEY_DOWN:
            if(sDirection != UP)
                sDirection = DOWN;
            break;
        case GLUT_KEY_RIGHT:
            if(sDirection != LEFT)
                sDirection = RIGHT;
            break;
        case GLUT_KEY_LEFT:
            if(sDirection != RIGHT)
                sDirection = LEFT;
            break;
    }
}
