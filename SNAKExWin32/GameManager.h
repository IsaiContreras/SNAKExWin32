#ifndef _GAME
#define _GAME

#include "resource.h"
#include "Sprite.h"
#include "Snake.h"

// Estado del juego
enum GAMESTATE {
	INITIALIZE,
	TITLE_SCREEN,
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

	unsigned short GameState;
	bool pause = false;

	SPRITE* background;
	SPRITE* menusheet;

	static GAMEMANAGER* _instance;

	GAMEMANAGER();
	~GAMEMANAGER();

	void LoadBackground(HINSTANCE);
	void LoadTitleSprites(HINSTANCE);
	void LoadGameSprites(HINSTANCE);
	void LoadResultsSprites(HINSTANCE);

	void ReleaseAllSprites();

public:

	static GAMEMANAGER* getInstance();

	void InitializeScreen(HWND);

	void ChangeState(HINSTANCE, unsigned short);
	void Renderize();
	void Render(HWND);

	unsigned short GetGameState();

};
#endif