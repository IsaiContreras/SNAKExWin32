#include "Sprite.h"

SPRITE::SPRITE(HINSTANCE hInstance, UINT imageID, UINT maskID) {
	LoadSprite(hInstance, imageID, maskID);
}
SPRITE::~SPRITE() {
	DeleteObject(hMask);
	DeleteObject(hImage);
}

void SPRITE::LoadSprite(HINSTANCE hInstance, UINT imageID, UINT maskID) {
	hImage = LoadBitmap(hInstance, MAKEINTRESOURCE(imageID));
	GetObject(hImage, sizeof(BITMAP), &bmpImage);
	if (maskID != NO_MASK) {
		hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(maskID));
		GetObject(hMask, sizeof(BITMAP), &bmpMask);
	}
	width = bmpImage.bmWidth;
	height = bmpImage.bmHeight;
}

void SPRITE::Draw(HDC destino, HDC backBuff, int px, int py) {
	HGDIOBJ oldObj = SelectObject(backBuff, hMask);
	BitBlt(destino, px, py, width, height, backBuff, 0, 0, SRCAND);
	SelectObject(backBuff, hImage);
	BitBlt(destino, px, py, width, height, backBuff, 0, 0, SRCPAINT);
	SelectObject(backBuff, oldObj);
}
void SPRITE::DrawCut(HDC destino, HDC backBuff, int fromx, int fromy, int width, int height, int px, int py) {
	if (width > this->width)
		width = this->width;
	if (height > this->height)
		height = this->height;
	HGDIOBJ oldObj = SelectObject(backBuff, hMask);
	BitBlt(destino, px, py, width, height, backBuff, fromx, fromy, SRCAND);
	SelectObject(backBuff, hImage);
	BitBlt(destino, px, py, width, height, backBuff, fromx, fromy, SRCPAINT);
	SelectObject(backBuff, oldObj);
}
void SPRITE::DrawTransparent(HDC destino, HDC backBuff, RECT dR, RECT sR) {
	COLORREF transparent_color = RGB(0, 255, 0);
	SelectObject(backBuff, hImage);
	TransparentBlt(destino, dR.left, dR.top, dR.right, dR.bottom, backBuff, sR.left, sR.top, sR.right, sR.bottom, transparent_color);
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