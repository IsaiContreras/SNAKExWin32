#ifndef _GAME
#define _GAME

#include "resource.h"
#include "Sprite.h"
#include "Snake.h"
#include "Fruit.h"
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

	unsigned long score;

	short selectedIndex;

	SPRITE* background = NULL;
	SPRITE* menusheet = NULL;

	SNAKE* player;
	FRUIT* fruit;

	static GAMEMANAGER* _instance;

	GAMEMANAGER();
	
	void LoadBackgroundSprite(HINSTANCE);
	void LoadTitleSprites(HINSTANCE);
	void LoadGameSprites(HINSTANCE);
	void LoadResultsSprites(HINSTANCE);

	void ReleaseBackgroundSprite();
	void ReleaseTitleSprites();
	void ReleaseGameSprites();
	void ReleaseResultsSprites();

	void ExitGame(HWND);

	void ReleaseAllSprites();

public:

	~GAMEMANAGER();

	static GAMEMANAGER* getInstance();

	void InitializeScreen(HWND);
	void SelectOption(HINSTANCE hInst, HWND hwnd);
	
	void ChangeState(HINSTANCE, unsigned short);
	void Algorythm();
	void Renderize();
	void Render(HWND);

	void ChangeSelectedIndex(UINT button);
	void Controler(UINT button);

	unsigned short GetGameState();

};
#endif