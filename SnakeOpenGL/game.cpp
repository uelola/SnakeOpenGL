//
// Created by Lola Ueda on 07.11.21.
//

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <ctime>
#include <cstdlib>
#include "game.h"

int gridX, gridY;
//initial length of the snake is 5
int snake_length = 9;

bool treat = true;
// position of the treat
int treatX, treatY;
// initial direction
short sDirection = RIGHT;
extern bool gameOver;
extern int score;

//initial position of the snake head
//int posX = 32, posY = 24;

// at the beginning initialize starting position of the full snake body
int posX [60] = {32, 32, 32, 32, 32, 32, 32, 32, 32}, posY [60] = {24, 23, 22, 21, 20, 19, 18, 17, 16};

// draw grid on the screen, function is called to initialize the dimensions of the grid
void initGrid(int x, int y) {
    gridX = x;
    gridY = y;
}
void unit(int, int);

// function to draw grid
void drawGrid() {
    // test is 1 square is displayed         unit(32, 24);

    for(int x = 0; x < gridX; x++){
        for(int y = 0; y < gridY; y++){
            unit(x, y);
        }
    }

}


void unit(int x, int y) {
    // function to draw a single grid unit
    // set color & thickness of the line (by default the thickness is 1.0 and color is white)
    //glLineWidth(1.0);
    //glColor3f(1.0, 1.0, 1.0);

    // if the box is at the edge ( x == gridX  is the most right side, similar with y   y == gridY - 1 )
    if(x == 0 | y == 0 | x == gridX - 1 | y == gridY - 1){
        glLineWidth(5.0);
        glColor3f(0.4, 0.3, 0.05);
    } else {
        glLineWidth(1.0);
        glColor3f(0.0 , 0.5, 0.0);
    }

    // specify drawing mode of geometric primitives like line...
    // 1st & last specified vertex are connected, closed figure is formed
    glBegin(GL_LINE_LOOP);

    // drawing in between glBegin and glEnd
    glVertex2f(x,y);
    glVertex2f(x+1, y);
    glVertex2f(x+1,y+1);
    glVertex2f(x,y+1);

    // end drawing
    glEnd();
}

void drawTreat() {
    // treat position needs to be reset
    if(treat)
        random(treatX, treatY);
    treat = false;
    glColor3f(1.0, 0.0, 0.0);
    glRectf(treatX, treatY, treatX+1, treatY+1 );

}

void drawSnake() {

    // position of the last block will change to position of the previous block (when snake is moving)
    // position 0 will be assigned with a new position, therefore 0 is excluded
    for(int i = snake_length-1; i > 0; i--) {
        posX[i] = posX[i-1];
        posY[i] = posY[i-1];

    }

    if(sDirection == UP)
        posY[0]++;
    else if(sDirection == DOWN)
        posY[0]--;
    else if(sDirection == RIGHT)
        posX[0]++;
    else if(sDirection == LEFT)
        posX[0]--;

    // draw the snake body
    for(int i = 0; i < snake_length; i++) {
        if(i == 0)
            // head color
            glColor3f(0.498039, 1.0, 0.0);

        else

            //body color
            glColor3f(0.196078, 0.8, 0.196078);
        glRectd(posX[i], posY[i], posX[i]+1, posY[i]+1);
    }

    // collision detection only for the head element
    if(posX[0] == 0 | posX[0] == gridX-1 | posY[0] == 0 | posY[0] == gridY-1)
        gameOver = true;
    // collision with the treat and snake head
    if(posX[0] == treatX && posY[0] == treatY) {

        // each time snake eats a treat, the score is increased
        score++;

        // snake length will increase
        snake_length++;

        if(snake_length > MAX)
            // if snake length reaches 60, it will stop growing
            snake_length = MAX;
        // then draw treat will be called
        treat = true;
    }

}

// create random values for treat generation
void random(int &x, int &y) {
    // avoids generation of the same number
    int _maxX = gridX - 2; // 64-2
    int _maxY = gridY - 2;
    int _min = 1;
    srand(time(NULL));
    // rand returns high num, use algorithm to convert to a range number => (min + rand % (max - min))
    x = _min + rand() % (_maxX - _min);
    y = _min + rand() % (_maxY - _min);


}
