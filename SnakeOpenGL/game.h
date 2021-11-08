//
// Created by Lola Ueda on 07.11.21.
//

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
//define direction constants, need to be unique
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#define MAX 60


void initGrid(int, int);
void drawGrid();
void drawSnake();
void drawTreat();
void random(int &, int &);

#endif
