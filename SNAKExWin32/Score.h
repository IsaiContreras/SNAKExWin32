#ifndef _SCORE
#define _SCORE

#include "Sprite.h"

class SCORE : private SPRITE {

	unsigned int score = 0;
	char print[6];

	void ScoreToChar();

public:

	SCORE(HINSTANCE instance, UINT imageID, UINT maskID);

	void Score(int sum);

	void Draw(HDC destino, HDC backBuff, unsigned int initPX, unsigned int initPY);

};

#endif