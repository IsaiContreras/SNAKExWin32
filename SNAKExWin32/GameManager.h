#ifndef _GAME
#define _GAME

#include "resource.h"
#include "Sprite.h"
#include "Snake.h"
#include "GamePadRR.h"

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

	short selectedIndex;

	SPRITE* background = NULL;
	SPRITE* menusheet = NULL;

	static GAMEMANAGER* _instance;

	GAMEMANAGER();
	
	void LoadBackground(HINSTANCE);
	void LoadTitleSprites(HINSTANCE);
	void LoadGameSprites(HINSTANCE);
	void LoadResultsSprites(HINSTANCE);

	void ExitGame(HWND);

	void ReleaseAllSprites();

public:

	~GAMEMANAGER();

	static GAMEMANAGER* getInstance();

	void InitializeScreen(HWND);
	void SelectOption(HWND hwnd);
	
	void ChangeState(HINSTANCE, unsigned short);
	void Renderize();
	void Render(HWND);

	void ChangeSelectedIndex(UINT button);

	unsigned short GetGameState();

};
#endif