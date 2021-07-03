#include "GameManager.h"

GAMEMANAGER::GAMEMANAGER() {
	outputDC = backBuff = 0;
}

void GAMEMANAGER::LoadBackground(HINSTANCE hInstance) {
	if (!background)
		background = new SPRITE(hInstance, IDB_BACKGROUND, IDB_BACKGROUND_M);
}
void GAMEMANAGER::LoadTitleSprites(HINSTANCE hInstance) {
	if (!menusheet)
		menusheet = new SPRITE(hInstance, IDB_MENU, IDB_MENU_M);
}
void GAMEMANAGER::LoadGameSprites(HINSTANCE hInstance) {

}
void GAMEMANAGER::LoadResultsSprites(HINSTANCE hInstance) {

}

void GAMEMANAGER::ExitGame(HWND hwnd) {
	DestroyWindow(hwnd);
}

void GAMEMANAGER::ReleaseAllSprites() {
	delete background;
	delete menusheet;
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
void GAMEMANAGER::SelectOption(HWND hwnd) {
	switch (selectedIndex) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		ExitGame(hwnd);
		break;
	}
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
	case MENU_SCREEN:
		selectedIndex = 0;
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
		menusheet->DrawCut(outputDC, backBuff, 20, 250, 418, 44, 151, 300);
		menusheet->DrawCut(outputDC, backBuff, 20, 295, 111, 44, 200, 354);
		menusheet->DrawCut(outputDC, backBuff, 20, 340, 190, 44, 200, 408);
		menusheet->DrawCut(outputDC, backBuff, 20, 385, 127, 44, 200, 462);
		menusheet->DrawCut(outputDC, backBuff, 20, 430, 274, 44, 223, 600);
		if (selectedIndex != 3)
			menusheet->DrawCut(outputDC, backBuff, 518, 20, 46, 30, 154, 361 + (54 * selectedIndex));
		else menusheet->DrawCut(outputDC, backBuff, 518, 20, 46, 30, 177, 607 + (54 * (selectedIndex - 3)));
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

void GAMEMANAGER::ChangeSelectedIndex(UINT button) {
	if (GameState == MENU_SCREEN) {
		if (button == XINPUT_GAMEPAD_DPAD_DOWN)
			selectedIndex < 3 ? selectedIndex++ : selectedIndex = 3;
		if (button == XINPUT_GAMEPAD_DPAD_UP)
			selectedIndex > 0 ? selectedIndex-- : selectedIndex = 0;
	}
}

unsigned short GAMEMANAGER::GetGameState() {
	return this->GameState;
}