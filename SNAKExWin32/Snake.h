#ifndef _SNAKE_CLASS
#define _SNAKE_CLASS

#include "Sprite.h"
#include "Fruit.h"

enum STATE {
	STAND_BY,
	COOLDOWN,
	PLAYING,
	CRASHED
};

enum FACING {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class SNAKE : private SPRITE {

	friend class GAMEMANAGER;

	int psx, psy;
	int ptx, pty;
	unsigned int ptface;
	unsigned int facing;
	unsigned int facing_sprite;
	unsigned int state = STAND_BY;
	unsigned int speed;
	unsigned int steps = 0;
	unsigned int longtail;

	class TAIL {

		friend class SNAKE;

		TAIL* next;
		TAIL* prev;

		int psx, psy;
		unsigned int facing;

		TAIL(int psx, int psy, unsigned int facing);

	}*aux = NULL, *first = NULL, *last = NULL;
	
	SNAKE(HINSTANCE, UINT, UINT, int initPX, int initPY, int facing, int speed, unsigned int longtail);
	~SNAKE();

	void Eat();

	void MoveSnake();
	void MoveTail(int psx, int psy, int facing);

	void ChangeFacing(unsigned int newfacing);
	bool CheckPositionCollide(int psx, int psy);

	void Draw(HDC, HDC);

};
#endif