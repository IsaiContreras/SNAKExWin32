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

	HDC outputDC;
	HDC backBuff;
	HBITMAP surface;
	HBITMAP emptySurface;

	short GameState;
	bool pause = false;

	SPRITE* background;
	SPRITE* menusheet;

	static GAMEMANAGER* _instance;

	GAMEMANAGER();
	~GAMEMANAGER();

	void InitMenu(HINSTANCE);
	void InitGame(HINSTANCE);
	void InitResults(HINSTANCE);

	void ReleaseAllSprites();

public:

	static GAMEMANAGER* getInstance();

	void InitializeScreen(HWND);

	void ChangeState(HINSTANCE, short);
	void Renderize();
	void Render(HWND);

};
#endif
