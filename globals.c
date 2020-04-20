#include "globals.h"

int batterySave = on;
FILE* bestTxt;
Uint16 bestScore;

int const nededBalls = 5;

Uint64 const maxTextLen = 100;
int const screenWidth = 900;
int const screenHeight = 950;

int const cellSize = 100;

const int dims = 9;
int howManyNewBalls = 5;

int points = 0;
int actualBalls = standard;

int** gameArr;
int** directionsArr;

Point* newBallArr;
int* newBallColorArr;
int* nextBallColorArr;

Point** parentsArr;
bool** visitedArr;

int const DESTINATION_CANNOT_BE_REACHED = -1;

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;


SDL_Color textColor = { 0,0,0 };
TTF_Font* font = NULL;

Uint32 startTime = 0;
Uint16 ballsAmount;
Uint16 currBallsAmount;

SDL_Texture* directions[countDirections];
SDL_Texture* balls[countColorBall];
SDL_Texture* cell = NULL;
SDL_Texture* selectedCell = NULL;
SDL_Texture* newCell = NULL;
SDL_Texture* resetButton = NULL;

Point mouse;

