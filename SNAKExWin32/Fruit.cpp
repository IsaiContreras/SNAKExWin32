#include "Fruit.h"

FRUIT::FRUIT(HINSTANCE instance, UINT imageID, UINT maskID, int originx, int originy, unsigned int rangex, unsigned int rangey, unsigned int fruittypes) : SPRITE(instance, imageID, maskID) {
	srand(time(NULL));
	this->opsx = originx;
	this->opsy = originy;
	this->ranx = rangex;
	this->rany = rangey;
	this->fruittypes = fruittypes;
	Generate();
}

void FRUIT::Generate() {
	psx = opsx + ((rand() % ranx) * 32);
	psy = opsy + ((rand() % rany) * 32);
	type = rand() % fruittypes;
}

void FRUIT::Draw(HDC destino, HDC backBuff) {
	DrawCut(destino, backBuff, 20 + (type * 32), 20, 32, 32, this->psx, this->psy);
}

int FRUIT::GetPosX() {
	return psx;
}
int FRUIT::GetPosY() {
	return psy;
}

bool FRUIT::CheckPositionColide(int psx, int psy) {
	if (this->psx == psx & this->psy == psy) return true;
	else return false;
}