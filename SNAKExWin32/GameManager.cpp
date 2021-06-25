#include "GameManager.h"

void GAMEMANAGER::ChangeState(short state) {
	this->GameState = state;
	switch (state) {
	case MENU_SCREEN:
		InitMenu();
		break;
	case IN_GAME:
		InitGame();
		break;
	case RESULTS_SCREEN:
		InitResults();
		break;
	}
}

void GAMEMANAGER::InitMenu() {

}
void GAMEMANAGER::InitGame() {

}
void GAMEMANAGER::InitResults() {

}