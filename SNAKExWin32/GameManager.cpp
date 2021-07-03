#include "GameManager.h"

GAMEMANAGER::GAMEMANAGER() {
	outputDC = backBuff = 0;
}
GAMEMANAGER::~GAMEMANAGER() {
	ReleaseAllSprites();
	DeleteObject(surface);
	DeleteObject(emptySurface);
	DeleteObject(outputDC);
	DeleteObject(backBuff);
}

GAMEMANAGER* GAMEMANAGER::getInstance() {
	if (!_instance) {
		_instance = new GAMEMANAGER;
	}
	return _instance;
}

void GAMEMANAGER::LoadBackground(HINSTANCE hInstance) {
	background = new SPRITE(hInstance, IDB_BACKGROUND, IDB_BACKGROUND_M);
}
void GAMEMANAGER::LoadTitleSprites(HINSTANCE hInstance) {
	menusheet = new SPRITE(hInstance, IDB_MENU, IDB_MENU_M);
}
void GAMEMANAGER::LoadGameSprites(HINSTANCE hInstance) {

}
void GAMEMANAGER::LoadResultsSprites(HINSTANCE hInstance) {

}
void GAMEMANAGER::ReleaseAllSprites() {
	delete background;
	delete menusheet;
}

void GAMEMANAGER::InitializeScreen(HWND hwnd) {
	backBuff = CreateCompatibleDC(NULL);
	HDC tempDC = GetDC(hwnd);
	outputDC = CreateCompatibleDC(tempDC);
	surface = CreateCompatibleBitmap(tempDC, 720, 804);
	ReleaseDC(hwnd, tempDC);
	emptySurface = (HBITMAP)SelectObject(outputDC, surface);
	HBRUSH bWhite = (HBRUSH)GetStockObject(BLACK_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(outputDC, bWhite);
	Rectangle(outputDC, 0, 0, 720, 804);
	SelectObject(outputDC, oldBrush);
}
void GAMEMANAGER::ChangeState(HINSTANCE hInstance, unsigned short state) {
	this->GameState = state;
	switch (state) {
	case INITIALIZE:
		LoadBackground(hInstance);
		LoadTitleSprites(hInstance);
		this->GameState = TITLE_SCREEN;
		break;
	case TITLE_SCREEN:
		LoadTitleSprites(hInstance);
		break;
	case IN_GAME:
		LoadGameSprites(hInstance);
		break;
	case RESULTS_SCREEN:
		LoadResultsSprites(hInstance);
		break;
	}
}
void GAMEMANAGER::Renderize() {
	background->Draw(outputDC, backBuff, 0, 0);
	switch (GameState) {
	case TITLE_SCREEN:
		menusheet->DrawCut(outputDC, backBuff, 20, 20, 497, 184, 112, 100);
		menusheet->DrawCut(outputDC, backBuff, 20, 205, 471, 44, 125, 450);
		break;
	case MENU_SCREEN:
		menusheet->DrawCut(outputDC, backBuff, 20, 20, 497, 184, 112, 100);
		break;
	case IN_GAME:
		break;
	case RESULTS_SCREEN:
		break;
	}
}
void GAMEMANAGER::Render(HWND hwnd) {
	HDC hWndDC = GetDC(hwnd);
	BitBlt(hWndDC, 0, 0, 720, 804, outputDC, 0, 0, SRCCOPY);
	ReleaseDC(hwnd, hWndDC);
}

unsigned short GAMEMANAGER::GetGameState() {
	return this->GameState;
}