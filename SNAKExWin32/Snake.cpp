#include "Snake.h"

SNAKE::SNAKE(HINSTANCE hInst, UINT imageID, UINT maskID, int initPX, int initPY, int facing, int speed, unsigned int longtail) : SPRITE(hInst, imageID, maskID) {
	this->psx = initPX;
	this->psy = initPY;
	this->facing_sprite = facing;
	this->speed = speed;
	this->longtail = longtail;
	for (unsigned int i = 1; i <= longtail; i++) {
		if (first != NULL) {
			switch (facing) {
			case NORTH:
				aux->next = new TAIL(initPX, ((initPY) + (32 * i)), facing);
				break;
			case EAST:
				aux->next = new TAIL(((initPX) - (32 * i)), initPY, facing);
				break;
			case SOUTH:
				aux->next = new TAIL(initPX, ((initPY) - (32 * i)), facing);
				break;
			case WEST:
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
			case NORTH:
				first = new TAIL(initPX, ((initPY) + (32 * i)), facing);
				break;
			case EAST:
				first = new TAIL(((initPX) - (32 * i)), initPY, facing);
				break;
			case SOUTH:
				first = new TAIL(initPX, ((initPY) - (32 * i)), facing);
				break;
			case WEST:
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

void SNAKE::MoveSnake() {
	if (state == STAND_BY) return;
	if (steps == 0) {
		int prevpsx = psx;
		int prevpsy = psy;
		switch (facing) {
		case NORTH:
			psy -= 32;
			break;
		case EAST:
			psx += 32;
			break;
		case SOUTH:
			psy += 32;
			break;
		case WEST:
			psx -= 32;
			break;
		}
		MoveTail(prevpsx, prevpsy);
		facing_sprite = facing;
		state = PLAYING;
		steps = speed;
	}
	else steps--;
}
void SNAKE::MoveTail(int psx, int psy) {
	aux = first;
	int newpsx = psx, newpsy = psy;
	while (aux != NULL) {
		int prevpsx = aux->psx;
		int prevpsy = aux->psy;
		aux->psx = newpsx;
		aux->psy = newpsy;
		newpsx = prevpsx;
		newpsy = prevpsy;
		aux = aux->next;
	}
	aux = first;
}

void SNAKE::ChangeFacing(unsigned int newfacing) {
	if (state == STAND_BY) state = PLAYING;
	if (facing == NORTH && newfacing == SOUTH) return;
	if (facing == EAST && newfacing == WEST) return;
	if (facing == SOUTH && newfacing == NORTH) return;
	if (facing == WEST && newfacing == EAST) return;
	if (state == COOLDOWN) return;
	if (state == PLAYING){
		this->facing = newfacing;
		state = COOLDOWN;
	}
}

void SNAKE::DrawSnake(HDC destino, HDC backBuff) {
	DrawCut(destino, backBuff, 20 + (32 * this->facing_sprite) , 20, 32, 32, this->psx, this->psy);
	while (aux != NULL) {
		DrawCut(destino, backBuff, 148, 20, 32, 32, aux->psx, aux->psy);
		aux = aux->next;
	}
	aux = first;
}