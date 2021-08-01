#include "Score.h"

#pragma warning (disable:4996)

SCORE::SCORE(HINSTANCE instance, UINT imageID, UINT maskID) : SPRITE(instance, imageID, maskID) {
	strcpy(print, "000000");
}

void SCORE::ScoreToChar() {
	char buff[6];
	itoa(score, buff, 10);
	unsigned int size = strlen(buff);
	size = strlen(print) - size;
	strcpy(&print[size], buff);
}

void SCORE::Score(int sum) {
	score += sum;
}

void SCORE::Draw(HDC destino, HDC backBuff, unsigned int initPX, unsigned int initPY) {
	ScoreToChar();
	for (unsigned int i = 0; i < 6; i++) {
		DrawCut(destino, backBuff, 20 + (37 * ((int)print[i] - 48)), 20, 36, 44, initPX + (37 * i), initPY);
	}
}