#include "Sprite.h"

void SPRITE::LoadSprite(HINSTANCE hInstance, UINT imageID, UINT maskID) {
	hImage = LoadBitmap(hInstance, MAKEINTRESOURCE(imageID));
	hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(maskID));
	GetObject(hImage, sizeof(BITMAP), &bmpImage);
	GetObject(hMask, sizeof(BITMAP), &bmpMask);
	width = bmpImage.bmWidth;
	height = bmpMask.bmHeight;
}
void SPRITE::Draw(HDC destino, HDC backBuff, int px, int py) {
	HGDIOBJ oldObj = SelectObject(backBuff, hMask);
	BitBlt(destino, px, py, width, height, backBuff, 0, 0, SRCAND);
	SelectObject(backBuff, hImage);
	BitBlt(destino, px, py, width, height, backBuff, 0, 0, SRCPAINT);
	SelectObject(backBuff, oldObj);
}

void SPRITE::SetHBMImage(HBITMAP param) {
	this->hImage = param;
}
void SPRITE::SetHBMMask(HBITMAP param) {
	this->hMask = param;
}
HBITMAP SPRITE::GetHBMImage() {
	return this->hImage;
}
HBITMAP SPRITE::GetHBMMask() {
	return this->hMask;
}

void SPRITE::SetBMImage(BITMAP param) {
	this->bmpImage = param;
}
void SPRITE::SetBMMask(BITMAP param) {
	this->bmpMask = param;
}
BITMAP SPRITE::GetBMImage() {
	return this->bmpImage;
}
BITMAP SPRITE::GetBMMask() {
	return this->bmpMask;
}

void SPRITE::SetWidth(int param) {
	this->width = param;
}
void SPRITE::SetHeight(int param) {
	this->height = param;
}
int SPRITE::GetWidth() {
	return this->width;
}
int SPRITE::GetHeight() {
	return this->height;
}