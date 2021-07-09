#include <Windows.h>
#include <strsafe.h>
#include "resource.h"

#include "GameManager.h"
#include "GamePadRR.h"

#define TM_TIMER_FRAME 2000
#define TM_TIMER_GAMEPAD 2001

HINSTANCE instGlobal;
HWND hWindow;

GamePadRR jugador(1);
XINPUT_GAMEPAD prevState;

HDC myHDC;
HDC hdcBackBuffer = 0;
HBITMAP myHSurface;
HBITMAP myHoldSurface;

GAMEMANAGER* GAMEMANAGER::_instance = NULL;

LRESULT CALLBACK winProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cShow) {
	instGlobal = hInstance;

	myHDC = hdcBackBuffer;

	WNDCLASSEX snCEx;
	ZeroMemory(&snCEx, sizeof(WNDCLASSEX));

	snCEx.cbSize = sizeof(WNDCLASSEX);
	snCEx.style = CS_HREDRAW | CS_VREDRAW;
	snCEx.lpfnWndProc = winProc;
	snCEx.cbClsExtra = 0;
	snCEx.cbWndExtra = 0;
	snCEx.hInstance = hInstance;
	snCEx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	snCEx.hCursor = LoadCursor(NULL, IDC_CROSS);
	snCEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	snCEx.lpszMenuName = NULL;
	snCEx.lpszClassName = L"SNKWINDOW";
	snCEx.hIconSm = LoadIcon(snCEx.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if(!RegisterClassEx(&snCEx)){
		MessageBox(NULL, L"Error al registrar ventana.\nEl programa se cerrará.", L"ERROR", MB_ICONERROR);
		return 1;
	}

	hWindow = CreateWindow(L"SNKWINDOW", L"SNAKExWin32", WS_OVERLAPPEDWINDOW,
		                   CW_USEDEFAULT, CW_USEDEFAULT, 720, 804,
		                   NULL, NULL, hInstance, NULL);

	if (!hWindow) {
		MessageBox(NULL, L"Error al crear ventana.\nEl programa se cerrará.", L"ERROR", MB_ICONERROR);
		return 1;
	}

	ShowWindow(hWindow, cShow);
	UpdateWindow(hWindow);

	SetTimer(hWindow, TM_TIMER_FRAME, 1000/30, NULL);
	SetTimer(hWindow, TM_TIMER_GAMEPAD, 10, NULL);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	KillTimer(hWindow, TM_TIMER_FRAME);
	return 0;

}

LRESULT CALLBACK winProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	PAINTSTRUCT ps;
	switch (msg) {
	case WM_CREATE: {
		//Load Sprites
		GAMEMANAGER* manager = GAMEMANAGER::getInstance();
		manager->ChangeState(instGlobal, INITIALIZE);
		manager->InitializeScreen(hwnd);
		break;
	}
	case WM_PAINT: {
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_KEYDOWN: {
		GAMEMANAGER* manager = GAMEMANAGER::getInstance();
		switch (LOWORD(wparam)) {
		case VK_UP:
			switch (manager->GetGameState()) {
			case MENU_SCREEN:
				manager->ChangeSelectedIndex(XINPUT_GAMEPAD_DPAD_UP);
				break;
			}
			break;
		case VK_DOWN:
			switch (manager->GetGameState()) {
			case MENU_SCREEN:
				manager->ChangeSelectedIndex(XINPUT_GAMEPAD_DPAD_DOWN);
				break;
			}
			break;
		case VK_LEFT:
			switch (manager->GetGameState()) {

			}
			break;
		case VK_RIGHT:
			switch (manager->GetGameState()) {

			}
			break;
		case VK_RETURN:
			switch (manager->GetGameState()) {
			case TITLE_SCREEN:
				manager->ChangeState(instGlobal, MENU_SCREEN);
				break;
			}
			break;
		case VK_SPACE:
			switch (manager->GetGameState()) {
			case MENU_SCREEN:
				manager->SelectOption(instGlobal, hwnd);
				break;
			}
			break;
		}
		break;
	}
	case WM_TIMER: {
		switch (LOWORD(wparam)) {
		case TM_TIMER_GAMEPAD: {
			if (!jugador.IsConnected()) break;
			GAMEMANAGER* manager = GAMEMANAGER::getInstance();
			XINPUT_GAMEPAD currState = jugador.GetState().Gamepad;
			switch (currState.wButtons) {
			case XINPUT_GAMEPAD_DPAD_UP:
				if (prevState.wButtons & currState.wButtons) break;
				switch (manager->GetGameState()) {
				case MENU_SCREEN:
					manager->ChangeSelectedIndex(XINPUT_GAMEPAD_DPAD_UP);
					break;
				}
				break;
			case XINPUT_GAMEPAD_DPAD_DOWN:
				if (prevState.wButtons & currState.wButtons) break;
				switch (manager->GetGameState()) {
				case MENU_SCREEN:
					manager->ChangeSelectedIndex(XINPUT_GAMEPAD_DPAD_DOWN);
					break;
				}
				break;
			case XINPUT_GAMEPAD_DPAD_LEFT:
				if (prevState.wButtons & currState.wButtons) break;
				break;
			case XINPUT_GAMEPAD_DPAD_RIGHT:
				if (prevState.wButtons & currState.wButtons) break;
				break;
			case XINPUT_GAMEPAD_START:
				if (prevState.wButtons & currState.wButtons) break;
				switch (manager->GetGameState()) {
				case TITLE_SCREEN:
					manager->ChangeState(instGlobal, MENU_SCREEN);
					break;
				}
				break;
			case XINPUT_GAMEPAD_A:
				if (prevState.wButtons & currState.wButtons) break;
				switch (manager->GetGameState()) {
				case MENU_SCREEN:
					manager->SelectOption(instGlobal, hwnd);
					break;
				}
				break;
			}
			prevState = currState;
			break;
		}
		case TM_TIMER_FRAME: {
			GAMEMANAGER* manager = GAMEMANAGER::getInstance();
			manager->Renderize();
			manager->Render(hwnd);
			break;
		}
		}
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY: {
		GAMEMANAGER* manager = GAMEMANAGER::getInstance();
		delete manager;
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
		break;
	}
	return 0;
}