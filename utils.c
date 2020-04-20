#include "utils.h"

bool checkIfClickInRectangle(SDL_Rect Rectangle){
	return (mouse.x > Rectangle.x &&
		mouse.x < Rectangle.x + Rectangle.w &&
		mouse.y > Rectangle.y &&
		mouse.y < Rectangle.y + Rectangle.h);
}

Point getPosInArr(){
	Point ballPos;
	ballPos.x = mouse.x / cellSize;
	ballPos.y = (mouse.y - (screenHeight - 900)) / cellSize;

	return ballPos;
}

Uint32 gameTime() {
	return SDL_GetTicks() - startTime;
}

void printArr(int** arr) {
	for (int i = 0; i < dims; i++) {
		for (int j = 0; j < dims; j++) {
			printf("%i ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void fillArr(int** arr, int code){
	for (int i = 0; i < dims; i++)
		for (int j = 0; j < dims; j++)
			arr[i][j] = code;
}

void freeArr(void** arr) {

	for (int i = 0; i < dims; i++) 
		free(arr[i]);
	
	free(arr);
}