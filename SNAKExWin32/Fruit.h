#ifndef _FRUIT
#define _FRUIT

#include <stdlib.h>
#include <time.h>

#include "Sprite.h"

class FRUIT : private SPRITE {

	int opsx, opsy;
	int ranx, rany;
	int fruittypes;
	int psx, psy;
	unsigned int type;

public:

	FRUIT(HINSTANCE instance, UINT imageID, UINT maskID, int originx, int originy, unsigned int rangex, unsigned int rangey, unsigned int fruittypes);

	void Generate();

	void Draw(HDC destino, HDC backBuff);

	int GetPosX();
	int GetPosY();

	bool CheckPositionColide(int psx, int psy);

};
#endif
