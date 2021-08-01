#ifndef _SNAKE_CLASS
#define _SNAKE_CLASS

#include "Sprite.h"
#include "Fruit.h"

enum STATE {
	STAND_BY,
	COOLDOWN,
	PLAYING,
	GAMEOVER
};

enum FACING {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class SNAKE : private SPRITE {

	friend class GAMEMANAGER;

	int posX, posY;
	int prevTailX, prevTailY;
	unsigned int prevTailFacing;
	unsigned int facingChange;
	unsigned int facing;
	unsigned int state = STAND_BY;
	unsigned int steps = 0;
	unsigned int speed;
	unsigned int speedLimit;
	unsigned int speedSub;
	unsigned short eatsToSpeedUp;
	unsigned int longTail;

	class TAIL {

		friend class SNAKE;

		TAIL* next;
		TAIL* prev;

		int posX, posY;
		unsigned int facing;

		TAIL(int psx, int psy, unsigned int facing);

	}*aux = NULL, *first = NULL, *last = NULL;
	
	SNAKE(HINSTANCE, UINT, UINT, int initPX, int initPY, int facing, unsigned short mode);
	~SNAKE();

	void Eat();

	void MoveSnake();
	void MoveTail(int psx, int psy, int facing);

	void ChangeFacing(unsigned int newfacing);
	bool CheckPositionCollide(int psx, int psy);
	bool CheckTailCollide();
	bool CheckWallsCollide(int left, int right, int top, int bottom);

	void Draw(HDC, HDC);

};
#endif