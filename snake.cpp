#include "snake.h"
#include"screen.h"

CSnake::CSnake(CRect r, char _c) :
	CFramedWindow(r, _c)
{
	restart();
}


void CSnake::drawSnake() {
	for (unsigned i = 0; i < snake.size(); i++) {
		gotoyx(geom.topleft.y + snake[i].y, geom.topleft.x + snake[i].x);
		printc('+');
	}
	gotoyx(geom.topleft.y + snake[0].y, geom.topleft.x + snake[0].x);
	printc('*');
}
void CSnake::printFood() {
	gotoyx(food.y + geom.topleft.y, food.x + geom.topleft.x);
	printc('O');
}

void CSnake::FoodSpawn() {
	srand(time(NULL));
	int flag = 1;
	while(flag){
		flag=0;
		food.x = rand() % (geom.size.x - 3) + 1;
		food.y = rand() % (geom.size.y - 3) + 1;
		for (unsigned i = 0; i < snake.size(); i++) {
			if ((snake[i].x == food.x) && (snake[i].y == food.y))
				flag = 1;
		}
	}
}
void CSnake::paint() {
	gotoyx(geom.topleft.y - 1, geom.topleft.x);
	printl("level: %i", level+1);
	CFramedWindow::paint();
	switch (current) {
	case(0): //menu
		gotoyx(geom.topleft.y + 3, geom.topleft.x + 1);
		printl("h - toogle help");
		gotoyx(geom.topleft.y + 4, geom.topleft.x + 1);
		printl("p - toogle pause/play mode");
		gotoyx(geom.topleft.y + 5, geom.topleft.x + 1);
		printl("r - restart game");
		break;
	case(1): //game
		drawSnake();
		printFood();
		if(clock){
			move();
			eat();
		}
		break;
	case(2): //pause
		drawSnake();
		printFood();
		gotoyx(geom.topleft.y + 3, geom.topleft.x + 1);
		printl("pause");
		break;
	case(3): //help
		gotoyx(geom.topleft.y + 3, geom.topleft.x + 1);
		printl("move with wsad || catch all the apples");
		break;
	case(4): //over
		gotoyx(geom.topleft.y + 5, geom.topleft.x + 1);
		printl("GAME OVER");
		gotoyx(geom.topleft.y + 3, geom.topleft.x + 1);
		printl("r to restart");
		break;

	}
}

bool CSnake::handleEvent(int key) {
	if (current != 1 && CFramedWindow::handleEvent(key)) return true;
	else {
		switch (key) {
		case('w'):
			if (path.y == 1);
			path.x = 0;
			path.y = -1;
			clock = true;
			return true;
		case('s'):
			if (path.y == -1) break;
			path.x = 0;
			path.y = 1;
			clock = true;
			return true;
		case('a'):
			if (path.x == 1) break;
			path.x = -1;
			path.y = 0;
			clock = true;
			return true;
		case('d'):
			if (path.x == -1) break;
			path.x = 1;
			path.y = 0;
			clock = true;
			return true;
		case('p'):
			if(current==0) current=1;
			else if(current == 2) current = 1;
			else if(current == 1) current = 2;
			return true;
		case('r'):
			restart();
			return true;
		case('h'):
			if (current == 3) {
				current = 0; 
				return true;
			}
			if (current == 1 || current == 2) return true;
			current = 3;
			return true;
		case ERR:
			if(current==1){
				counter++;
				!(counter%speed) ? clock = true, counter = 0 : clock = false;
			}
			return true;
		}
	}
	return false;
}
void CSnake::move() {
	for (int i = snake.size() - 1; i > 0; i--)
		snake[i] = snake[i - 1];
	snake[0] += path;
	crash();
	death();
}
void CSnake::death() {
	for (unsigned i = 2; i < snake.size(); i++)
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) current = 4;
}
void CSnake::eat() {
	if ((snake[0].x == food.x) && (snake[0].y == food.y)) {
		snake.push_back(CPoint(snake[snake.size() - 1]));
		score++;	
		if(!(score%3)){
			level++;
			speed-=2;
			if(speed==2) speed=4;
		}
		FoodSpawn();
	}
}
void CSnake::crash() {
	if (snake[0].x >= geom.size.x - 1)
		snake[0].x = 1;
	if (snake[0].y >= geom.size.y - 1)
		snake[0].y = 1;
	if (snake[0].x < 1)
		snake[0].x = geom.size.x - 2;
	if (snake[0].y < 1)
		snake[0].y = geom.size.y - 2;
}
void CSnake::restart() {
	vector<CPoint> ekans;
	ekans.push_back(CPoint(4, 7));
	ekans.push_back(CPoint(4, 6));
	ekans.push_back(CPoint(4, 5));
	snake = ekans;
	current = 0;
	speed = 16;
	level = 0;
	counter = 0;
	score = 0;
	path.x = 0;
	path.y = 1;
	FoodSpawn();
}
