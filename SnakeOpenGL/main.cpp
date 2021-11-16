#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include "game.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

#include <cstdlib>
#include <charconv>

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
void welcome_display();
void game_over_display();
void reshape_callback(int, int);
void keyboard_callback(int, int, int);
void keys (unsigned char, int, int );

GLvoid* font_style = GLUT_BITMAP_TIMES_ROMAN_24;
int score_color = 1;

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
    init();
    // to initialize the display, needs display_callback
    glutDisplayFunc(welcome_display); //glutDisplayFunc(display_callback);
    // called when the window is created, minimized, maximised or extended to any direction(size changed)
    glutReshapeFunc(reshape_callback);
    // should be called before main loop
    glutTimerFunc(0, timer_callback, 0);
    // accepting user input
    glutSpecialFunc(keyboard_callback);
    glutKeyboardFunc(keys);

    glutMainLoop();
    return 0;
}

void keys (unsigned char key, int x, int y){
    if (key == 's') {
        glutDisplayFunc(display_callback);
    }
    // control back to display
    glutPostRedisplay();
}


void display_callback() {

//     const int buffer = 100;
//     char msg[buffer + 1];
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
        glutDisplayFunc(game_over_display);
        glutPostRedisplay();
        //exit(0);
    }

}

void welcome_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.498039, 1.0, 0.0);

    glRasterPos3f(26,30,0);
    char msg [] = "SNAKE GAME";
    for(int i=0; i< strlen(msg); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg[i] );
    }
    glRasterPos3f(24,26,0);
    char msg1 [] = "Press S to start the game";
    for(int i=0; i< strlen(msg1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg1[i] );
    }
    glutSwapBuffers();
}

void game_over_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.498039, 1.0, 0.0);

    glRasterPos3f(26,30,0);
    char msg2 [] = "GAME OVER";
    for(int i=0; i< strlen(msg2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg2[i] );
    }
    glRasterPos3f(24,26,0);
    char msg3 [] = "Your score: " ;
    for(int i=0; i< strlen(msg3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);
    }
    glRasterPos3f(34,26,0);


//    char msg4 [] = to_chars(score);
//    for(int i=0; i< strlen(msg4); i++) {
//        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);
//    }

    glutSwapBuffers();
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
