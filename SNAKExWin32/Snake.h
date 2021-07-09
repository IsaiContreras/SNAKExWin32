#ifndef _SNAKE_CLASS
#define _SNAKE_CLASS

#include "Sprite.h"

enum STATE {
	STAND_BY,
	PLAYING,
	CRASHED
};

class SNAKE : private SPRITE {

	friend class GAMEMANAGER;

	int psx, psy;
	unsigned int facing;
	unsigned int state = STAND_BY;
	unsigned int speed;
	unsigned int longtail;

	class TAIL {

		friend class SNAKE;

		TAIL* next;
		TAIL* prev;

		int psx, psy;
		unsigned int facing;
		unsigned int sprite;

		TAIL(int, int, unsigned int);

	}*aux = NULL, *first = NULL, *last = NULL;
	
	SNAKE(HINSTANCE, UINT, UINT, int initPX, int initPY, int facing, int speed, unsigned int longtail);
	~SNAKE();

	void DrawSnake(HDC, HDC);

};
#endif
