#ifndef RENDER_H
#define RENDER_H

#include<stdbool.h>
#include<string.h>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"globals.h"

void renderAllText(char* actualPointsString, char* bestScoreString, char* text, SDL_Rect* textRectangle);
void renderText(int x, int y, char* text, SDL_Rect* rect, float size_multiplikator);
void renderBalls(SDL_Rect* ballRectangle, bool isBallSelected, Point cords);
void renderDirections(SDL_Rect* directionRectangle);
void renderNextBalls();

#endif // RENDER_H