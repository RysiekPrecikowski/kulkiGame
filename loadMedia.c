#include"loadMedia.h"

bool loadMedia()
{
	if (!LoadBalls()) {
		fprintf(stderr, "Failed to load balls\n");
		return false;
	}

	if (!loadDirections()) {
		fprintf(stderr, "failed to load directions\n");
		return false;
	}

	cell = LoadTexture("images/cell.png", dontDeleteBackground);
	if (cell == NULL)
	{
		fprintf(stderr, "Failed to load the image \n");
		return false;
	}
	selectedCell = LoadTexture("images/selectedCell.png", dontDeleteBackground);
	if (selectedCell == NULL)
	{
		fprintf(stderr, "Failed to load the image \n");
		return false;
	}
	newCell = LoadTexture("images/newCell.png", dontDeleteBackground);
	if (newCell == NULL)
	{
		fprintf(stderr, "Failed to load the image \n");
		return false;
	}
	resetButton = LoadTexture("images/resetButton.png", deleteWhiteBackground);
	if (resetButton == NULL)
	{
		fprintf(stderr, "Failed to load the image \n");
		return false;
	}
	return true;
}

bool LoadBalls() {
	balls[redBall] = LoadTexture("images/redBall.png", deleteWhiteBackground);
	balls[blueBall] = LoadTexture("images/blueBall.png", deleteWhiteBackground);
	balls[cyanBall] = LoadTexture("images/cyanBall.png", deleteWhiteBackground);
	balls[yellowBall] = LoadTexture("images/yellowBall.png", deleteWhiteBackground);
	balls[greyBall] = LoadTexture("images/greyBall.png", deleteWhiteBackground);
	balls[purpleBall] = LoadTexture("images/purpleBall.png", deleteWhiteBackground);
	balls[greenBall] = LoadTexture("images/greenBall.png", deleteWhiteBackground);

	for (Uint32 i = 0; i < countColorBall; i++) {
		if (balls[i] == NULL) {
			fprintf(stderr, "Failed to load %d ball!\n", i);
			return false;
		}
	}
	return true;
}

bool loadDirections() {
	directions[weirdot] = LoadTexture("images/weirdot.png", deleteWhiteBackground);

	for (Uint32 i = 0; i < countDirections; i++) {
		if (directions[i] == NULL) {
			fprintf(stderr, "Failed to load %d direction!\n", i);
			return false;
		}
	}
	return true;
}

bool setIcon()
{
	int option = deleteWhiteBackground;
	SDL_Surface* loadedSurface = IMG_Load("images/icon.png");

	if (loadedSurface == NULL) {
		fprintf(stderr, "Unable to load the icon ! SDL_image Error: %s\n", (char*)IMG_GetError);
		return false;
	}
	else {
		if (option == deleteWhiteBackground)
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
		SDL_SetWindowIcon(window, loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}

	return true;
}

SDL_Texture* LoadTexture(char* file, int option)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(file);

	if (loadedSurface == NULL) {
		fprintf(stderr, "Unable to load the image %s! SDL_image Error: %s\n", file, (char*)IMG_GetError);
	}
	else {
		if (option == deleteWhiteBackground)
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL)
			fprintf(stderr, "Unable to create the texture form %s! SDL_error: %s\n", file, SDL_GetError());

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}