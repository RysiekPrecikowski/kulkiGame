#ifndef GLOBALS_H
#define GLOBALS_H

#include<stdio.h>
#include<stdbool.h>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>


#define ERROR_INIT -1
#define ERROR_LOAD -2

enum directions {
	weirdot,
	countDirections,
	notDirection
};

enum balls {
	redBall,
	blueBall,
	cyanBall,
	yellowBall,
	greyBall,
	greenBall,
	purpleBall,
	countColorBall,
	notBall
};

enum backgroundOptions {
	dontDeleteBackground,
	deleteWhiteBackground
};

enum findingScore {
	vertical,
	horizontal,
	slantLeft,
	slantRight,
	notScore
};

enum actualBalls {
	standard,
};

enum battery {
	off,
	on,
	ultra,
	ultraX2,
	numberOfBatteryMode
};

typedef struct Point{
	int x;
	int y;
}Point;

typedef struct data {
	Point pt;
	int distanceFromStart;
}data;



extern int batterySave;
extern FILE* bestTxt;
extern Uint16 bestScore;


extern const int nededBalls;

extern const Uint64 maxTextLen;
extern const int screenWidth ;
extern const int screenHeight;

extern const int cellSize;

extern const int dims;
extern int howManyNewBalls;

extern int points;
extern int actualBalls;

extern int** gameArr;
extern int** directionsArr;

extern Point* newBallArr;
extern int* newBallColorArr;
extern int* nextBallColorArr;

extern Point** parentsArr;
extern bool** visitedArr;

extern int const DESTINATION_CANNOT_BE_REACHED;

extern SDL_Window* window;

extern SDL_Renderer* renderer;
extern SDL_Texture* texture;

extern SDL_Color textColor;
extern TTF_Font* font;

extern Uint32 startTime;
extern Uint16 ballsAmount;
extern Uint16 currBallsAmount;

extern SDL_Texture* directions[countDirections];
extern SDL_Texture* balls[countColorBall];
extern SDL_Texture* cell;
extern SDL_Texture* selectedCell;
extern SDL_Texture* newCell;
extern SDL_Texture* resetButton;

extern Point mouse;




#endif //GLOBALS_H
