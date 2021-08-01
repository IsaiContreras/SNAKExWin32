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
	GAME_OVER,
	RESULTS_SCREEN
};

// GameManager Singleton
class GAMEMANAGER {

	HINSTANCE gameInstance;
	HWND gameWindow;

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
	SPRITE* ingame_cards = NULL;
	SPRITE* numerics = NULL;

	SNAKE* player;
	FRUIT* fruit;

	static GAMEMANAGER* _instance;

	GAMEMANAGER();
	
	void LoadBackgroundSprite();
	void LoadTitleSprites();
	void LoadGameSprites();
	void LoadResultsSprites();

	void ReleaseBackgroundSprite();
	void ReleaseTitleSprites();
	void ReleaseGameSprites();
	void ReleaseResultsSprites();

	void ReleaseAllSprites();

	void ExitGame();

public:

	~GAMEMANAGER();

	static GAMEMANAGER* getInstance();

	void InitializeScreen(HINSTANCE, HWND);
	void SelectOption();
	
	void ChangeState(unsigned short);
	void Algorythm();
	void Renderize();
	void Render();

	void ChangeSelectedIndex(UINT button);
	void Controler(UINT button);
	void TogglePause();
	void Restart();

	unsigned short GetGameState();

};
#endif