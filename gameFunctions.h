#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"globals.h"
#include"utils.h"


void handleLeftClics(bool* isBallSelected, Point* selectedBall, Point* selectedPos, bool* haveToAddBalls, Uint32* timeAfterMove);
bool addBalls(int n);
void generateColorsForBalls(int n);
int getDirections(Point from, Point to);
void handlePointsAndNewBalls(bool* haveToAddBalls, bool* lost);
int checkPoints();

#endif // GAMEFUNCTIONS_H