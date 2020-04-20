#include"gameFunctions.h"
#include"findingPath.h"


void handleLeftClics(bool* isBallSelected, Point* selectedBall, Point* selectedPos, bool* haveToAddBalls, Uint32* timeAfterMove)
{
	if (!(*isBallSelected)) {
		*selectedBall = getPosInArr();
		if (gameArr[selectedBall->x][selectedBall->y] == notBall) {
			printf("selected wrong ball!\n");
		}
		else {
			*isBallSelected = true;
			printf("selected ball %d %d\n", selectedBall->x, selectedBall->y);
			fillArr(directionsArr, notDirection);
		}
	}
	else {
		*selectedPos = getPosInArr();
		printf("2selected ball %d %d\n", selectedBall->x, selectedBall->y);
		printf("2selected dest %d %d\n", selectedPos->x, selectedPos->y);
		if (selectedBall->x == selectedPos->x && selectedBall->y == selectedPos->y) {
			printf("unselected\n");
			*isBallSelected = false;
		}
		else if (gameArr[selectedPos->x][selectedPos->y] != notBall) {
			printf("selected pos with ball!\n");
			*selectedBall = *selectedPos;
		}
		else {
			if (getDirections(*selectedBall, *selectedPos) == DESTINATION_CANNOT_BE_REACHED) {
				printf("wrong\n");
			}
			else {
				directionsArr[selectedBall->x][selectedBall->y] = weirdot;
				gameArr[selectedPos->x][selectedPos->y] = gameArr[selectedBall->x][selectedBall->y];
				gameArr[selectedBall->x][selectedBall->y] = notBall;
				*timeAfterMove = gameTime();

				printf("colors:  ");
				generateColorsForBalls(3);
				for (int k = 0; k < 3; k++) {
					printf("%d ", newBallColorArr[k]);
				}
				printf("\n");
				*haveToAddBalls = true;
				*isBallSelected = false;
			}
		}

	}

}

bool addBalls(int n)
{
	int* colors = malloc(sizeof(int) * n);
	int i, j;

	for (int k = 0; k < n; k++) {
		currBallsAmount++;
		//if we have more balls than we can fit
		if (currBallsAmount > ballsAmount)
			return false;
		howManyNewBalls = k + 1;

		do {
			i = rand() % dims;
			j = rand() % dims;
		} while (gameArr[i][j] != notBall);
		gameArr[i][j] = newBallColorArr[k];
		newBallArr[k].x = i;
		newBallArr[k].y = j;
	}
	free(colors);
	return true;
}

void generateColorsForBalls(int n) {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++) {
		newBallColorArr[i] = nextBallColorArr[i];
		nextBallColorArr[i] = rand() % countColorBall;
	}
}

int getDirections(Point from, Point to) {
	fillArr(directionsArr, notDirection);
	int moves = BFS(from, to);
	Point cords = to;
	for (int i = 0; i < moves; i++) {
		directionsArr[cords.x][cords.y] = weirdot;
		cords = parentsArr[cords.x][cords.y];
	}

	return moves;
}

int checkVertical(int color, Point* bestStartingPos) {
	Point bestEndingPos = { -1,-1 };
	int length;
	int maxlenght = 0;
	for (int i = 0; i < dims; i++) {
		length = 0;
		for (int j = 0; j < dims; j++) {
			if (gameArr[i][j] == color) {
				length++;
				if (length > maxlenght) {
					maxlenght = length;
					bestEndingPos.x = i;
					bestEndingPos.y = j;
				}
			}
			else {
				length = 0;
			}
		}
	}

	if (maxlenght >= nededBalls) {
		bestStartingPos->x = bestEndingPos.x;
		bestStartingPos->y = bestEndingPos.y;
		return maxlenght;
	}
	return 0;
}
int checkHorizontal(int color, Point* bestStartingPos) {
	Point bestEndingPos = { -1,-1 };
	int length;
	int maxlenght = 0;
	for (int i = 0; i < dims; i++) {
		length = 0;
		for (int j = 0; j < dims; j++) {
			if (gameArr[j][i] == color) {
				length++;
				if (length > maxlenght) {
					maxlenght = length;
					bestEndingPos.x = j;
					bestEndingPos.y = i;
				}
			}
			else {
				length = 0;
			}
		}
	}

	if (maxlenght >= nededBalls) {
		bestStartingPos->x = bestEndingPos.x;
		bestStartingPos->y = bestEndingPos.y;
		return maxlenght;
	}
	return 0;
}
int checkSlantLeft(int color, Point* bestStartingPos) {
	Point bestEndingPos = { -1,-1 };
	int length;
	int maxlenght = 0;
	int i, k;

	for (i = 0; i < dims; i++) {
		length = 0;
		for (k = 0; k < dims - i; k++) {
			if (gameArr[k][i + k] == color) {
				length++;
				if (length > maxlenght) {
					maxlenght = length;
					bestEndingPos.x = k;
					bestEndingPos.y = i + k;
				}
			}
			else {
				length = 0;
			}
		}
	}
	for (i = 0; i < dims; i++) {
		length = 0;
		for (k = 0; k < dims - i; k++) {
			if (gameArr[i + k][k] == color) {
				length++;
				if (length > maxlenght) {
					maxlenght = length;
					bestEndingPos.x = i + k;
					bestEndingPos.y = k;
				}
			}
			else {
				length = 0;
			}
		}
	}
	if (maxlenght >= nededBalls) {
		bestStartingPos->x = bestEndingPos.x;
		bestStartingPos->y = bestEndingPos.y;
		return maxlenght;
	}
	return 0;
}
int checkSlantRight(int color, Point* bestStartingPos) {
	Point bestEndingPos = { -1,-1 };
	int length;
	int maxlenght = 0;
	int i, k;

	for (i = 0; i < dims; i++) {
		length = 0;
		for (k = 0; k < dims - i; k++) {
			if (gameArr[dims - 1 - k][i + k] == color) {
				length++;
				if (length > maxlenght) {
					maxlenght = length;
					bestEndingPos.x = dims - 1 - k;
					bestEndingPos.y = i + k;
				}
			}
			else {
				length = 0;
			}
		}
	}
	for (i = 0; i < dims; i++) {
		length = 0;
		for (k = 0; k < dims - i; k++) {
			if (gameArr[dims - 1 - (i + k)][k] == color) {
				length++;
				if (length > maxlenght) {
					maxlenght = length;
					bestEndingPos.x = dims - 1 - (i + k);
					bestEndingPos.y = k;
				}
			}
			else {
				length = 0;
			}
		}
	}

	if (maxlenght >= nededBalls) {
		bestStartingPos->x = bestEndingPos.x;
		bestStartingPos->y = bestEndingPos.y;
		return maxlenght;
	}
	return 0;
}

int checkPoints()
{
	int res = 0;
	int tmpVertical, tmpHorizontal, tmpSlantLeft, tmpSlantRight;
	Point bestStartingPosVertical, bestStartingPosHorizontal, bestStartingPosSlantLeft, bestStartingSlantRight;
	for (int color = 0; color < countColorBall; color++) {
		//printf("best for %d is %d\n",color, checkVertical(color, &bestStartingPos));
		//printf("best for %d is %d\n", color, checkHorizontal(color, &bestStartingPos));
		tmpVertical = checkVertical(color, &bestStartingPosVertical);

		tmpHorizontal = checkHorizontal(color, &bestStartingPosHorizontal);

		tmpSlantLeft = checkSlantLeft(color, &bestStartingPosSlantLeft);

		tmpSlantRight = checkSlantRight(color, &bestStartingSlantRight);

		if (tmpVertical >= nededBalls)
		{
			res += tmpVertical;
			for (int i = 0; i < tmpVertical; i++) {
				gameArr[bestStartingPosVertical.x][bestStartingPosVertical.y - i] = notBall;
			}
		}

		if (tmpHorizontal >= nededBalls)
		{
			res += tmpHorizontal;
			for (int i = 0; i < tmpHorizontal; i++) {
				gameArr[bestStartingPosHorizontal.x - i][bestStartingPosHorizontal.y] = notBall;
			}
		}

		if (tmpSlantLeft >= nededBalls)
		{
			res += tmpSlantLeft;
			for (int i = 0; i < tmpSlantLeft; i++) {
				gameArr[bestStartingPosSlantLeft.x - i][bestStartingPosSlantLeft.y - i] = notBall;
			}
		}

		if (tmpSlantRight >= nededBalls)
		{
			res += tmpSlantRight;
			for (int i = 0; i < tmpSlantRight; i++) {
				gameArr[bestStartingSlantRight.x + i][bestStartingSlantRight.y - i] = notBall;
			}
		}

	}
	currBallsAmount -= res;
	return res;
}

void handlePointsAndNewBalls(bool* haveToAddBalls, bool* lost)
{
	fillArr(directionsArr, notDirection);
	int gainedPoints = checkPoints();

	//adding balls if not gained points
	if (gainedPoints == 0) {
		if (!addBalls(3))
		{
			*lost = true;
		}
		// check if gained points from new balls
		points += checkPoints();
	}
	printf("colors:  ");
	for (int k = 0; k < 3; k++) {
		printf("%d ", newBallColorArr[k]);
	}
	printf("\n");
	*haveToAddBalls = false;
	points += gainedPoints;
}