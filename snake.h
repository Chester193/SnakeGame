#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include <time.h>
#include <vector>

#include "screen.h"

class CSnake:public CFramedWindow
{
	vector<CPoint> snake;
	CPoint food;
	CPoint path;
	int score;
	int counter;
	int current;
	int speed;
	int level;
	bool clock;
public:
  CSnake(CRect r, char _c = ' ');
  void drawSnake();
  void FoodSpawn();
  void paint();
  void move();
  void eat();
  void death();
  bool handleEvent(int);
  void crash();
  void printFood();
  void restart();

  
};

#endif
