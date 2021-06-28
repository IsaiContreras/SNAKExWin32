#include "GameManager.h"

GAMEMANAGER::GAMEMANAGER() {
	myDC = backBuff = 0;
}

GAMEMANAGER* GAMEMANAGER::getInstance() {
	if (!_instance) {
		_instance = new GAMEMANAGER;
	}
	return _instance;
}

void GAMEMANAGER::InitMenu(HINSTANCE hInstance) {
	spritesheet = new SPRITE();
	spritesheet->LoadSprite(hInstance, IDB_SPRITESHEET, NO_MASK);
}
void GAMEMANAGER::InitGame(HINSTANCE hInstance) {

}
void GAMEMANAGER::InitResults(HINSTANCE hInstance) {

}

void GAMEMANAGER::InitializeScreen(HWND hwnd) {
	backBuff = CreateCompatibleDC(NULL);
	HDC tempDC = GetDC(hwnd);
	myDC = CreateCompatibleDC(tempDC);
	surface = CreateCompatibleBitmap(tempDC, spritesheet->GetWidth(), spritesheet->GetHeight());
	ReleaseDC(hwnd, tempDC);
	emptySurface = (HBITMAP)SelectObject(myDC, surface);
	HBRUSH bWhite = (HBRUSH)GetStockObject(BLACK_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(myDC, bWhite);
	Rectangle(myDC, 0, 0, spritesheet->GetWidth(), spritesheet->GetHeight());
	SelectObject(myDC, oldBrush);
}
void GAMEMANAGER::ChangeState(HINSTANCE hInstance, short state) {
	this->GameState = state;
	switch (state) {
	case MENU_SCREEN:
		InitMenu(hInstance);
		break;
	case IN_GAME:
		InitGame(hInstance);
		break;
	case RESULTS_SCREEN:
		InitResults(hInstance);
		break;
	}
}
void GAMEMANAGER::Renderize() {
	switch (GameState) {
	case MENU_SCREEN:
		spritesheet->DrawTransparent(myDC, backBuff, RECT{ 0, 0, 352, 352 }, RECT{0, 17, 352, 352});
		spritesheet->DrawTransparent(myDC, backBuff, RECT{ 43, 30, 266, 230 }, RECT{ 568, 0, 266, 230 });
		break;
	case IN_GAME:
		break;
	case RESULTS_SCREEN:
		break;
	}
}
void GAMEMANAGER::Render(HWND hwnd) {
	HDC hWndDC = GetDC(hwnd);
	BitBlt(hWndDC, 0, 0, 368, 426, myDC, 0, 0, SRCCOPY);
	ReleaseDC(hwnd, hWndDC);
}