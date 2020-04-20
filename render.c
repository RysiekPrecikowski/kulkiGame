#include"render.h"

void renderAllText(char* actualPointsString, char* bestScoreString, char* text, SDL_Rect* textRectangle)
{
	//snprintf(actualTimeString, 20, "%u", Time()/1000);
	//strcpy_s(text, maxTextLen, "Actual time: ");
	//strcat_s(text, maxTextLen, actualTimeString);
	//render_text(5, 10, text, textRectangle, 1);

	snprintf(actualPointsString, 20, "%d", points);
	strcpy_s(text, maxTextLen, "Your points: ");
	strcat_s(text, maxTextLen, actualPointsString);
	renderText(4, 4, text, textRectangle, 1.5);

	snprintf(bestScoreString, 20, "%i", bestScore);
	strcpy_s(text, maxTextLen, "Best: ");
	strcat_s(text, maxTextLen, bestScoreString);
	renderText(textRectangle->w + 30, 4, text, textRectangle, 1.5);
}

void renderText(int x, int y, char* text, SDL_Rect* rect, float size_multiplikator) {
	SDL_Surface* surface;
	SDL_Texture* texture;

	surface = TTF_RenderText_Solid(font, text, textColor);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect->x = x;
	rect->y = y;
	rect->w = (int)(surface->w * size_multiplikator);
	rect->h = (int)(surface->h * size_multiplikator);

	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, rect);
	SDL_DestroyTexture(texture);
}

void renderBalls(SDL_Rect* ballRectangle, bool isBallSelected, Point cords)
{
	bool changeColor = false;

	for (int i = 0; i < dims; i++) {

		for (int j = 0; j < dims; j++)
		{
			ballRectangle->x = i * cellSize;
			ballRectangle->y = j * cellSize;

			SDL_RenderCopy(renderer, cell, NULL, ballRectangle);
			for (int k = 0; k < howManyNewBalls; k++)
				if (newBallArr[k].x == i && newBallArr[k].y == j && gameArr[i][j] != notBall) {
					//k++;
					SDL_RenderCopy(renderer, newCell, NULL, ballRectangle);
				}

			if (isBallSelected && cords.x == i && cords.y == j) {
				changeColor = true;
				SDL_RenderCopy(renderer, selectedCell, NULL, ballRectangle);
			}

			if (gameArr[i][j] != notBall) {
				SDL_RenderCopy(renderer, balls[gameArr[i][j]], NULL, ballRectangle);
			}
		}
	}
}

void renderDirections(SDL_Rect* directionRectangle)
{
	for (int i = 0; i < dims; i++) {

		for (int j = 0; j < dims; j++)
		{
			if (directionsArr[i][j] != notDirection) {
				directionRectangle->x = i * cellSize;
				directionRectangle->y = j * cellSize;
				SDL_RenderCopy(renderer, directions[directionsArr[i][j]], NULL, directionRectangle);
			}
		}
	}
}

void renderNextBalls() {
	SDL_Rect nextBallRect = { screenWidth / 2, 2, 50, 50 };
	for (int i = 0; i < 3; i++) {
		nextBallRect.x += 40;
		SDL_RenderCopy(renderer, balls[nextBallColorArr[i]], NULL, &nextBallRect);
	}
}