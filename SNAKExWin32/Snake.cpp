#include "Snake.h"

SNAKE::SNAKE(HINSTANCE instance, UINT imageID, UINT maskID, int initPX, int initPY, int facing, unsigned short mode) : SPRITE(instance, imageID, maskID) {
	this->posX = initPX;
	this->posY = initPY;
	this->facing = facing;
	switch (mode) {
	case 0:
		speed = 10;
		speedLimit = 2;
		speedSub = 2;
		eatsToSpeedUp = 4;
		longTail = 5;
		break;
	case 1:
		speed = 9;
		speedLimit = 0;
		speedSub = 3;
		eatsToSpeedUp = 10;
		longTail = 5;
		break;
	case 2:
		speed = 5;
		speedLimit = 1;
		speedSub = 1;
		eatsToSpeedUp = 8;
		longTail = 8;
		break;
	}
	for (unsigned int i = 1; i <= longTail; i++) {
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
	this->posX = posx;
	this->posY = posy;
	this->facing = facing;
	this->next = NULL;
	this->prev = NULL;
}

void SNAKE::Eat() {
	longTail++;
	static unsigned int eats = 0;
	eats++;
	if (eats > eatsToSpeedUp) {
		eats = 0;
		if (speed > speedLimit) speed -= speedSub;
		else speed = speedLimit;
	}
	aux = first;
	while (aux != last) aux = aux->next;
	aux->next = new TAIL(prevTailX, prevTailY, prevTailFacing);
	aux->next->prev = aux;
	aux = aux->next;
	last = aux;
	aux = first;
}

void SNAKE::MoveSnake() {
	if (state == STAND_BY) return;
	if (steps == 0) {
		int prevpsx = posX;
		int prevpsy = posY;
		int prevface = facingChange;
		switch (facingChange) {
		case NORTH:
			posY -= 32;
			break;
		case EAST:
			posX += 32;
			break;
		case SOUTH:
			posY += 32;
			break;
		case WEST:
			posX -= 32;
			break;
		}
		MoveTail(prevpsx, prevpsy, prevface);
		facing = facingChange;
		state = PLAYING;
		steps = speed;
	}
	else steps--;
}
void SNAKE::MoveTail(int psx, int psy, int facing) {
	aux = first;
	int newpsx = psx, newpsy = psy, newface = facing;
	while (aux != NULL) {
		int prevpsx = aux->posX;
		int prevpsy = aux->posY;
		int prevface = aux->facing;
		aux->posX = newpsx;
		aux->posY = newpsy;
		aux->facing = newface;
		newpsx = prevpsx;
		newpsy = prevpsy;
		newface = prevface;
		aux = aux->next;
	}
	prevTailX = newpsx;
	prevTailY = newpsy;
	prevTailFacing = newface;
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
		this->facingChange = newfacing;
		state = COOLDOWN;
	}
}
bool SNAKE::CheckPositionCollide(int psx, int psy) {
	if (this->posX == psx & this->posY == psy) return true;
	aux = first;
	while (aux != NULL) {
		if (aux->posX == psx & aux->posY == psy) return true;
		aux = aux->next;
	}
	aux = first;
	return false;
}
bool SNAKE::CheckTailCollide() {
	aux = first;
	while (aux != NULL) {
		if (this->posX == aux->posX & this->posY == aux->posY) return true;
		aux = aux->next;
	}
	aux = first;
	return false;
}
bool SNAKE::CheckWallsCollide(int left, int right, int top, int bottom) {
	if (this->posX < left) return true;
	if (this->posX > right) return true;
	if (this->posY < top) return true;
	if (this->posY > bottom) return true;
	return false;
}

void SNAKE::Draw(HDC destino, HDC backBuff) {
	aux = first;
	DrawCut(destino, backBuff, 20 + (32 * this->facing) , 20, 32, 32, this->posX, this->posY);
	while (aux != last) {
		if (aux->facing != aux->next->facing) {
			switch (aux->facing) {
			case NORTH:
				switch (aux->next->facing) {
				case WEST:
					DrawCut(destino, backBuff, 20, 86, 32, 32, aux->posX, aux->posY);
					break;
				case EAST:
					DrawCut(destino, backBuff, 116, 86, 32, 32, aux->posX, aux->posY);
					break;
				}
				break;
			case EAST:
				switch (aux->next->facing) {
				case NORTH:
					DrawCut(destino, backBuff, 52, 86, 32, 32, aux->posX, aux->posY);
					break;
				case SOUTH:
					DrawCut(destino, backBuff, 20, 86, 32, 32, aux->posX, aux->posY);
					break;
				}
				break;
			case SOUTH:
				switch (aux->next->facing) {
				case EAST:
					DrawCut(destino, backBuff, 84, 86, 32, 32, aux->posX, aux->posY);
					break;
				case WEST:
					DrawCut(destino, backBuff, 52, 86, 32, 32, aux->posX, aux->posY);
					break;
				}
				break;
			case WEST:
				switch (aux->next->facing) {
				case SOUTH:
					DrawCut(destino, backBuff, 116, 86, 32, 32, aux->posX, aux->posY);
					break;
				case NORTH:
					DrawCut(destino, backBuff, 84, 86, 32, 32, aux->posX, aux->posY);
					break;
				}
				break;
			}
		}
		else {
			DrawCut(destino, backBuff, 20 + (32 * (aux->facing % 2)), 53, 32, 32, aux->posX, aux->posY);
		}
		aux = aux->next;
	}
	DrawCut(destino, backBuff, 20 + (32 * last->facing), 119, 32, 32, last->posX, last->posY);
	aux = first;
}