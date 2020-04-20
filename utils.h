#ifndef UTILS_H
#define UTILS_H

#include<stdbool.h>
#include<string.h>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"globals.h"

bool checkIfClickInRectangle(SDL_Rect Rectangle);
Point getPosInArr();
Uint32 gameTime();
void printArr(int** arr);
void fillArr(int** arr, int code);

void freeArr(void** arr);

#endif // UTILS_H