#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAX_SIZE 500

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef int16_t bool;
#define true 1
#define false 0

bool GameOver;
int16_t width = 50, height = 20;
int16_t snakeX, snakeY, fruitX, fruitY, score;
int16_t tailX[100], tailY[100];
int16_t nTail = 0;
enum Direction {STOP = 0, UP, LEFT, DOWN, RIGHT };
Direction direction;

int getRandomNumber(int min , int max) {
	 // Initialize random seed
	 srand(time(NULL));

	 // Generate a random number between min and max
	 int randomNumber = rand() % (max - min + 1) + min;

	 return randomNumber;
}

void sleep(float seconds) {
	 clock_t end_time = (float)clock() + seconds * (float)CLOCKS_PER_SEC;
	 while ((float)clock() < (float)end_time) {
		  // Do nothing, just wait
	 }
}

void setup() {
		GameOver = false;
		snakeX = width / 2;
		snakeY = height / 2;
		fruitX = getRandomNumber(0, width - 1);
		fruitY = getRandomNumber(0, height - 1);
}

void draw() {
		for (int16_t i = 0; i < width; i++){
			printf("_");
		}
		printf("\tSNAKE GAME");
		printf("\n");

		 for (int16_t a = 0; a < height; a++) {
		  for (int16_t j = 0; j < width; j++) {
				if (j == 0 || j == width - 1) {
					 printf("|");
				}
				else if ((int16_t)j == snakeX && (int16_t)a == snakeY) {
					 printf("@");
				}
				else if ((int16_t)j == fruitX && (int16_t)a == fruitY) {
					 printf("*");
				}
				else {
					bool print = false;
					for ( int16_t k = 0; k < nTail; k++) {
						if (tailX[k] == j && tailY[k] == a) {
							printf("0");
							print = true;
						}
					}
					if(!print){
						printf(" ");
						print = false;
					}
				}
		  }
		  if(a == 0) printf("\tCreated By FROST EDSON");
		  if(a == 1) printf("\tScore: %d", score);
		  printf("\n");
	 }

		for (int16_t b = 0; b < width; b++){
			printf("#");
		}
		printf("\n");

}

void input() {
	  if (kbhit()) {
			char ch = getch();

			switch (ch) {
				case 'w':
					if(direction != DOWN)
						direction = UP;
					break;
				case 'W':
					if(direction != DOWN)
						direction = UP;
					break;

				case 's':
					if(direction != UP)
						direction = DOWN;
					break;
				case 'S':
					if(direction != UP)
						direction = DOWN;
					break;

				case 'A':
					if(direction != RIGHT)
						direction = LEFT;
					break;
				case 'a':
					if(direction != RIGHT)
						direction = LEFT;
					break;

				case 'D':
					if(direction != LEFT)
						direction = RIGHT;
					break;
				case 'd':
					if(direction != LEFT)
						direction = RIGHT;
					break;

				default:
					break;
				}


				// Check for ESC key
				if (ch == 27) {
					 GameOver  = true;
				}
		  }
}

void logic() {
	tailX[0] = snakeX;
	tailY[0] = snakeY;
	int16_t prevX = tailX[0];
	int16_t prevY = tailY[0];
	int16_t prev2X, prev2Y;

	for (int16_t i = 0; i < nTail; i++ ){
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (direction) {
		case UP:
			if ( snakeY < 1) snakeY = height;
			snakeY--;
			break;
		case DOWN:
			if ( snakeY > height - 1) snakeY = 0;
			snakeY++;
			break;
		case LEFT:
			if ( snakeX < 1) snakeX = width;
			snakeX--;
			break;
		case RIGHT:
			if ( snakeX > width - 1) snakeX = 0;
			snakeX++;
			break;
		default:
			break;
	}

	if (snakeX == fruitX && snakeY == fruitY){
		 score += 1;
		 nTail += 1;
		 fruitX = getRandomNumber(0, width - 1);
		 fruitX = getRandomNumber(0, width - 1);
		 fruitY = getRandomNumber(0, height - 1);fruitY = getRandomNumber(0, height - 1);
	}
}

void banner() {
	FILE *file;
	 char buffer[MAX_SIZE];

    file = fopen("snake.txt", "r");
    if (file == NULL) {
		  printf("Error opening the Snakefiles.\nCheck if snake.txt is available\n");
    }
    
    // Read the file contents into the buffer
    size_t bytesRead = fread(buffer, sizeof(char), MAX_SIZE, file);
    
    // Print the contents of the file
    printf("%.*s", (int)bytesRead, buffer);
    
    // Close the file
    fclose(file);
    

	for(;;){
		if (kbhit()) {
			char ch = getch();

			if(ch == ' ') break;
		}
	}
}

int main (int argc, char **argv) {
	banner();
	clrscr();
	setup();
	while(!GameOver) {
		clrscr();
		draw();
		input();
		logic();
		sleep(0.1);
	} 

		return 0;
}