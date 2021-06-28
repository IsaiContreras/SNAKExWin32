#ifndef _GAME
#define _GAME

#include "resource.h"
#include "Sprite.h"
#include "Snake.h"

// Estado del juego
enum GAMESTATE {
	MENU_SCREEN,
	IN_GAME,
	RESULTS_SCREEN
};

// GameManager Singleton
class GAMEMANAGER {

	HDC myDC;
	HDC backBuff;
	HBITMAP surface;
	HBITMAP emptySurface;

	short GameState;
	bool pause = false;

	SPRITE* spritesheet;

	static GAMEMANAGER* _instance;

	GAMEMANAGER();

	void InitMenu(HINSTANCE);
	void InitGame(HINSTANCE);
	void InitResults(HINSTANCE);

public:

	static GAMEMANAGER* getInstance();

	void InitializeScreen(HWND);

	void ChangeState(HINSTANCE, short);
	void Renderize();
	void Render(HWND);
};
#endif
