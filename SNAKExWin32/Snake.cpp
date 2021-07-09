#include "Snake.h"

SNAKE::SNAKE(HINSTANCE hInst, UINT imageID, UINT maskID, int initPX, int initPY, int facing, int speed, unsigned int longtail) : SPRITE(hInst, imageID, maskID) {
	this->psx = initPX;
	this->psy = initPY;
	this->facing = facing;
	this->speed = speed;
	this->longtail = longtail;
	for (unsigned int i = 1; i <= longtail; i++) {
		if (first != NULL) {
			switch (facing) {
			case 0:
				aux->next = new TAIL(initPX, ((initPY) + (32 * i)), facing);
				break;
			case 1:
				aux->next = new TAIL(((initPX) - (32 * i)), initPY, facing);
				break;
			case 2:
				aux->next = new TAIL(initPX, ((initPY) - (32 * i)), facing);
				break;
			case 3:
				aux->next = new TAIL(((initPX) + (32 * i)), initPY, facing);
				break;
			}
			aux->next->prev = aux;
			aux = aux->next;
			aux->next = NULL;
			last = aux;
		}
		else {
			switch (facing) {
			case 0:
				first = new TAIL(initPX, ((initPY) + (32 * i)), facing);
				break;
			case 1:
				first = new TAIL(((initPX) - (32 * i)), initPY, facing);
				break;
			case 2:
				first = new TAIL(initPX, ((initPY) - (32 * i)), facing);
				break;
			case 3:
				first = new TAIL(((initPX) + (32 * i)), initPY, facing);
				break;
			}
			aux = last = first;
		}
	}
	aux = first;
}
SNAKE::~SNAKE() {
	while (aux != NULL) {
		aux = aux->next;
		delete first;
		first = aux;
	}
	first = last = aux = NULL;
}

SNAKE::TAIL::TAIL(int posx, int posy, unsigned int facing) {
	this->psx = posx;
	this->psy = posy;
	this->facing = facing;
	this->next = NULL;
	this->prev = NULL;
}

void SNAKE::DrawSnake(HDC destino, HDC backBuff) {
	DrawCut(destino, backBuff, 20 + (32 * this->facing) , 20, 32, 32, this->psx, this->psy);
	while (aux != NULL) {
		DrawCut(destino, backBuff, 148, 20, 32, 32, aux->psx, aux->psy);
		aux = aux->next;
	}
	aux = first;
}