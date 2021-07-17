#include "Fruit.h"

FRUIT::FRUIT(HINSTANCE instance, UINT imageID, UINT maskID, int originx, int originy, unsigned int rangex, unsigned int rangey, unsigned int fruittypes) : SPRITE(instance, imageID, maskID) {
	srand(time(NULL));
	this->originX = originx;
	this->originY = originy;
	this->rangeX = rangex;
	this->rangeY = rangey;
	this->fruitTypes = fruittypes;
	Generate();
}

void FRUIT::Generate() {
	posX = originX + ((rand() % rangeX) * 32);
	posY = originY + ((rand() % rangeY) * 32);
	type = rand() % fruitTypes;
}

void FRUIT::Draw(HDC destino, HDC backBuff) {
	DrawCut(destino, backBuff, 20 + (type * 32), 20, 32, 32, this->posX, this->posY);
}

int FRUIT::GetPosX() {
	return posX;
}
int FRUIT::GetPosY() {
	return posY;
}

bool FRUIT::CheckPositionColide(int psx, int psy) {
	if (this->posX == psx & this->posY == psy) return true;
	else return false;
}