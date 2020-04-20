#ifndef LOADMEDIA_H
#define LOADMEDIA_H

#include<stdbool.h>
#include<string.h>


#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"globals.h"
#include"utils.h"



bool loadMedia();
bool LoadBalls();
bool loadDirections();
bool setIcon();
SDL_Texture* LoadTexture(char* file, int option);

#endif // LOADMEDIA_H