#include "GameManager.h"

GAMEMANAGER::GAMEMANAGER() {
	outputDC = backBuff = NULL;
}

void GAMEMANAGER::LoadBackgroundSprite() {
	if (!background)
		background = new SPRITE(gameInstance, IDB_BACKGROUND, IDB_BACKGROUND_M);
}
void GAMEMANAGER::LoadTitleSprites() {
	if (!menusheet)
		menusheet = new SPRITE(gameInstance, IDB_MENU, IDB_MENU_M);
}
void GAMEMANAGER::LoadGameSprites() {
	if (!player)
		player = new SNAKE(gameInstance, IDB_SNAKE, IDB_SNAKE_M, 352, 352, WEST, selectedIndex);
	if (!fruit) {
		fruit = new FRUIT(gameInstance, IDB_FRUIT, IDB_FRUIT_M, 32, 32, 20, 20, 5);
		while (player->CheckPositionCollide(fruit->GetPosX(), fruit->GetPosY()))
			fruit->Generate();
	}
	if (!ingame_cards)
		ingame_cards = new SPRITE(gameInstance, IDB_INGAMECARDS, IDB_INGAMECARDS_M);
}
void GAMEMANAGER::LoadResultsSprites() {

}

void GAMEMANAGER::ReleaseBackgroundSprite() {
	if (background) {
		delete background;
		background = NULL;
	}
}
void GAMEMANAGER::ReleaseTitleSprites() {
	if (menusheet) {
		delete menusheet;
		menusheet = NULL;
	}
}
void GAMEMANAGER::ReleaseGameSprites() {
	if (player) {
		delete player;
		player = NULL;
	}
	if (fruit) {
		delete fruit;
		fruit = NULL;
	}
	if (ingame_cards) {
		delete ingame_cards;
		ingame_cards = NULL;
	}
}
void GAMEMANAGER::ReleaseResultsSprites() {
	
}

void GAMEMANAGER::ReleaseAllSprites() {
	ReleaseBackgroundSprite();
	ReleaseTitleSprites();
	ReleaseGameSprites();
	ReleaseResultsSprites();
}

void GAMEMANAGER::TogglePause() {
	pause ? pause = false : pause = true;
}

void GAMEMANAGER::ExitGame() {
	DestroyWindow(gameWindow);
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

void GAMEMANAGER::InitializeScreen(HINSTANCE instance, HWND hwnd) {
	this->gameInstance = instance;
	this->gameWindow = hwnd;
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
void GAMEMANAGER::SelectOption() {
	switch (selectedIndex) {
	case 0:
		ReleaseTitleSprites();
		ChangeState(IN_GAME);
		break;
	case 1:
		ReleaseTitleSprites();
		ChangeState(IN_GAME);
		break;
	case 2:
		ReleaseTitleSprites();
		ChangeState(IN_GAME);
		break;
	case 3:
		ExitGame();
		break;
	}
}

void GAMEMANAGER::ChangeState(unsigned short state) {
	this->GameState = state;
	switch (state) {
	case INITIALIZE:
		LoadBackgroundSprite();
		LoadTitleSprites();
		this->GameState = TITLE_SCREEN;
		break;
	case TITLE_SCREEN:
		LoadTitleSprites();
		break;
	case MENU_SCREEN:
		LoadTitleSprites();
		selectedIndex = 0;
		break;
	case IN_GAME:
		score = 0;
		LoadGameSprites();
		break;
	case RESULTS_SCREEN:
		LoadResultsSprites();
		break;
	}
}
void GAMEMANAGER::Algorythm() {
	if (GameState != IN_GAME) return;
	if (pause) return;
	player->MoveSnake();
	if (fruit->CheckPositionColide(player->posX, player->posY)) {
		player->Eat();
		while (player->CheckPositionCollide(fruit->GetPosX(), fruit->GetPosY()))
			fruit->Generate();
	}
	else if (player->CheckTailCollide()) {
		ChangeState(GAME_OVER);
	}
	else if (player->CheckWallsCollide(32, 640, 32, 640)) {
		ChangeState(GAME_OVER);
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
		player->Draw(outputDC, backBuff);
		fruit->Draw(outputDC, backBuff);
		if (pause) ingame_cards->DrawCut(outputDC, backBuff, 20, 114, 146, 37, 279, 333);
		break;
	case GAME_OVER:
		ingame_cards->DrawCut(outputDC, backBuff, 20, 20, 157, 73, 273, 315);
		player->Draw(outputDC, backBuff);
		fruit->Draw(outputDC, backBuff);
	case RESULTS_SCREEN:
		break;
	}
}
void GAMEMANAGER::Render() {
	HDC hWndDC = GetDC(gameWindow);
	BitBlt(hWndDC, 0, 0, 720, 804, outputDC, 0, 0, SRCCOPY);
	ReleaseDC(gameWindow, hWndDC);
}
void GAMEMANAGER::Restart() {
	ReleaseGameSprites();
	ChangeState(MENU_SCREEN);
}

void GAMEMANAGER::ChangeSelectedIndex(UINT button) {
	if (GameState == MENU_SCREEN) {
		if (button == XINPUT_GAMEPAD_DPAD_DOWN)
			selectedIndex < 3 ? selectedIndex++ : selectedIndex = 3;
		if (button == XINPUT_GAMEPAD_DPAD_UP)
			selectedIndex > 0 ? selectedIndex-- : selectedIndex = 0;
	}
}
void GAMEMANAGER::Controler(UINT button) {
	switch (button) {
	case XINPUT_GAMEPAD_DPAD_UP:
		player->ChangeFacing(NORTH);
		break;
	case XINPUT_GAMEPAD_DPAD_RIGHT:
		player->ChangeFacing(EAST);
		break;
	case XINPUT_GAMEPAD_DPAD_DOWN:
		player->ChangeFacing(SOUTH);
		break;
	case XINPUT_GAMEPAD_DPAD_LEFT:
		player->ChangeFacing(WEST);
		break;
	}
}

unsigned short GAMEMANAGER::GetGameState() {
	return this->GameState;
}