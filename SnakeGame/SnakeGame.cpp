#include <iostream>
#include <conio.h>
#include <Windows.h>

bool game; 
//Map size 
const int width = 25;
const int height = 25;
//User
int x, y;
int speed = 1;
int tailX[100], tailY[100], tail_Lenght;
int first_PosX, first_PosY, second_PosX, second_PosY;
//Apple
int appleX, appleY;
//Game
int score;
enum directions {STOP = 0, UP, DOWN, LEFT, RIGHT};
directions dir;

void game_Setup() {
	game = true;
	dir = STOP;
	score = 0;
	//Snake will spawn in random place but not in the border
	x = rand() % width; 
	y = rand() % height;
	//Apple will spawn in random place but not in the border
	appleX = rand() % width;
	appleY = rand() % height;
	//Error when apple and player are on top
	while (x == appleX && y == appleY) {
		x = rand() % width;
		y = rand() % height;
		appleX = rand() % width;
		appleY = rand() % height;
	}
	while (first_PosX == appleX && first_PosY == appleY) {
		appleX = rand() % width;
		appleY = rand() % height;
	}
}

void game_Map() {
	system("cls");
	//Top
	for (int i = 0; i < width; i++) {
		std::cout << "#";
	}
	std::cout << std::endl;

	//Body
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				std::cout << "#";
			}
			else if (i == y && j == x) {
				std::cout << "S";
			}
			else if (i == appleY && j == appleX) {
				std::cout << "a";
			}
			else {
				bool tail = false;
				for (int k = 0; k < tail_Lenght; k++) {
					if (j == tailX[k] && i == tailY[k]) {
						std::cout << "s";
						tail = true;
					}
				}
				if (!tail) {
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl;
	}

	//Bottom
	for (int i = 0; i < width; i++) {
		std::cout << "#";
	}
	std::cout << std::endl;
	std::cout << "Score:" << score;
}
//Key input
void game_Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			if (dir != RIGHT) {
				dir = LEFT;
			}
			break;
		case 'd':
			if (dir != LEFT) {
				dir = RIGHT;
			}
			break;
		case 'w':
			if (dir != DOWN) {
				dir = UP;
			}
			break;
		case 's':
			if (dir != UP) {
				dir = DOWN;
			}
			break;
		}
	}
}

void game_code() {
	//Tail
	//Has to be top code else tail will spawn after you eat second apple
	first_PosX = tailX[0];
	first_PosY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tail_Lenght; i++) {
		second_PosX = tailX[i];
		second_PosY = tailY[i];
		tailX[i] = first_PosX;
		tailY[i] = first_PosY;
		first_PosX = second_PosX;
		first_PosY = second_PosY;
	}

	//(0;0) Top left
	switch (dir) {
	case LEFT:
		x -= speed;
		break;
	case RIGHT:
		x += speed;
		break;
	case UP:
		y -= speed;
		break;
	case DOWN:
		y += speed;
		break;
	}

	//Wall hit 
	if (x <= 0 || x >= width - 1 || y < 0 || y > height - 1) {
		game = false;
	}
	for (int i = 0; i < tail_Lenght; i++) {
		if (x == tailX[i] && y == tailY[i]) {
			game = false;
		}
	}


	//Apple and scroe
	if (x == appleX && y == appleY) {
		appleX = rand() % width;
		appleY = rand() % height;
		score +=10;
		tail_Lenght ++;
	}
}

int main() {
	game_Setup();
	while (game == true) {
		game_Map();
		game_Input();
		game_code();
		Sleep(100);
	}
}

