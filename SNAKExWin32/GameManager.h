#ifndef _GAME
#define _GAME

#include "Sprite.h"
#include "Snake.h"

enum GAMESTATE {
	MENU_SCREEN,
	IN_GAME,
	RESULTS_SCREEN
};

class GAMEMANAGER {

	short GameState;
	bool pause = false;

	SPRITE* selection;
	SPRITE* menuScreen[5];
	SPRITE* resultsScreen[15];

	SNAKE* player;

	static GAMEMANAGER* _INSTANCE;

	GAMEMANAGER(){}

	void InitMenu();
	void InitGame();
	void InitResults();

public:

	static GAMEMANAGER* getInstance() {
		if (!_INSTANCE) {
			_INSTANCE = new GAMEMANAGER();
		}
		return _INSTANCE;
	}

	void ChangeState(short);

};
GAMEMANAGER* GAMEMANAGER::_INSTANCE = NULL;

#endif
