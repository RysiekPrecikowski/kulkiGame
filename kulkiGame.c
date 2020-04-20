#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"findingPath.h"
#include"globals.h"
#include"render.h"
#include"utils.h"
#include"loadMedia.h"
#include"gameFunctions.h"

bool initialize();
void close();
void reset(bool* lost, bool* isBallSelected);


int main(int argc, char* argv[]) {
	if (!initialize()) {
		fprintf(stderr, "Could not initialize\n");
		return ERROR_INIT;
	}

	if (!loadMedia()) {
		fprintf(stderr, "Could not load media!\n");
		return ERROR_LOAD;
	}

	Point selectedBall = { 0,0 };
	Point selectedPos = { 0,0 };
	bool isBallSelected = false;


	Uint32 timeAfterMove = 0;
	bool haveToAddBalls = false;

	bool exit = false;
	bool lost = false;
	bool leftClick = false;
	SDL_Event e;

	SDL_Rect topViewport = { 0, 0, screenWidth, screenHeight - 900 };
	SDL_Rect mainViewport = { 0, screenHeight - 900 , screenWidth, 900 };

	SDL_Rect textRectangle = { 0,0,0,0 };
	SDL_Rect ballRectangle = { 0, 0, cellSize, cellSize };
	SDL_Rect screenRectangle = { 0, 0, screenWidth, screenHeight };
	SDL_Rect resetButtonRectangle = { screenWidth - 150, 2, 100, 50 };

	char* text = (char*)malloc(sizeof(char) * (maxTextLen + 1));
	char* actualPointsString = (char*)malloc(sizeof(char) * (maxTextLen + 1));
	char* bestScoreString = (char*)malloc(sizeof(char) * (maxTextLen + 1));


	while (!exit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				exit = true;
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					exit = true;
					break;
				case SDLK_UP:
					if (batterySave < numberOfBatteryMode - 1)
						batterySave++;
					break;
				case SDLK_DOWN:
					if (batterySave > 0)
						batterySave--;
					break;
				default:
					break;
				}
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					mouse.x = e.motion.x;
					mouse.y = e.motion.y;
					if (checkIfClickInRectangle(resetButtonRectangle))
						reset(&lost, &isBallSelected);
					else
						if (checkIfClickInRectangle(mainViewport))
							handleLeftClics(&isBallSelected, &selectedBall, &selectedPos, &haveToAddBalls, &timeAfterMove);
					break;

				default:
					break;
				}
			}
		}


		// 200 ms delay after move
		if (gameTime() - timeAfterMove >= 200 && haveToAddBalls)
			handlePointsAndNewBalls(&haveToAddBalls, &lost);


		SDL_RenderClear(renderer);


		SDL_RenderSetViewport(renderer, &topViewport);

		renderAllText(actualPointsString, bestScoreString, text, &textRectangle);
		renderNextBalls();
		SDL_RenderCopy(renderer, resetButton, NULL, &resetButtonRectangle);


		SDL_RenderSetViewport(renderer, &mainViewport);

		renderBalls(&ballRectangle, isBallSelected, selectedBall);
		renderDirections(&ballRectangle);


		if (currBallsAmount >= ballsAmount)
			lost = true;

		if (points > bestScore) {
			errno_t err;
			if ((err = fopen_s(&bestTxt, "best.txt", "w")) != 0)
				fprintf(stderr, "cannot open txt file! \n");
			bestScore = points;
			fprintf_s(bestTxt, "%i", bestScore);
			fclose(bestTxt);
		}


		if (lost) {
			SDL_RenderSetViewport(renderer, &mainViewport);

			renderText(50, 50, "u lost", &textRectangle, 3.0);
			renderText(40, 100, "Reset in 10 seconds", &textRectangle, 4.0);


			if (gameTime() - timeAfterMove >= 10000)
				reset(&lost, &isBallSelected);
		}

		SDL_RenderPresent(renderer);

		if (batterySave != off)
			SDL_Delay(batterySave * 50);
	}


	free(text);
	close();
	return 0;
}


bool initialize() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL could not be initialized! SDL_ERROR: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("KulkiGame",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		fprintf(stderr, "Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		fprintf(stderr, "Renderer could not be created! SDL_ERROR: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 255, 251, 100, 255);
	int imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags) & imgFlags)) {
		fprintf(stderr, "SDL_image could not be initialized! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		fprintf(stderr,"SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	font = TTF_OpenFont("fonts/arial_narrow.ttf", 24);
	if (font == NULL)
	{
		fprintf(stderr, "Font not found! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	if (!setIcon())
		fprintf(stderr, "Unable to load icon");

	startTime = SDL_GetTicks();

	gameArr = (int**)malloc(dims * sizeof(int*));
	directionsArr = (int**)malloc(dims * sizeof(int*));
	parentsArr = (Point**)malloc(dims * sizeof(Point*));
	visitedArr = (bool**)malloc(dims * sizeof(bool*));
	for (int i = 0; i < dims; i++) {
		gameArr[i] = (int*)malloc(dims * sizeof(int));
		directionsArr[i] = (int*)malloc(dims * sizeof(int));
		parentsArr[i] = (Point*)malloc(dims * sizeof(Point));
		visitedArr[i] = (bool*)malloc(dims * sizeof(bool));
		for (int j = 0; j < dims; j++) {
			gameArr[i][j] = notBall;
			directionsArr[i][j] = notDirection;

		}
	}
	newBallArr = (Point*)malloc(5 * sizeof(Point));
	newBallColorArr = (int*)malloc(5 * sizeof(int));
	nextBallColorArr = (int*)malloc(5 * sizeof(int));

	currBallsAmount = 0;
	ballsAmount = dims * dims;
	mouse.x = mouse.y = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 5; i++) {
		newBallColorArr[i] = rand() % countColorBall;
		nextBallColorArr[i] = rand() % countColorBall;
	}
	addBalls(5);

	errno_t err;

	if ((err = fopen_s(&bestTxt, "best.txt", "r")) != 0)
		fprintf(stderr, "cannot open txt file! \n");
	fscanf_s(bestTxt, "%hu", &bestScore);
	fclose(bestTxt);

	return true;
}

void close() {
	SDL_DestroyWindow(window);
	window = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	
	freeArr(gameArr);
	freeArr(directionsArr);
	freeArr(parentsArr);
	freeArr(visitedArr);

	free(newBallArr);
	free(newBallColorArr);
	free(nextBallColorArr);
}

void reset(bool* lost, bool* isBallSelected)
{
	fillArr(gameArr, notBall);
	fillArr(directionsArr, notDirection);
	currBallsAmount = 0;
	startTime = SDL_GetTicks();

	points = 0;
	*lost = false;
	*isBallSelected = false;

	LoadBalls();

	srand((unsigned int)time(NULL));
	for (int i = 0; i < 5; i++) {
		newBallColorArr[i] = rand() % countColorBall;
		nextBallColorArr[i] = rand() % countColorBall;
	}
	addBalls(5);
}

