#include <Windows.h>
#include <strsafe.h>
#include "resource.h"

#include "GameManager.h"

#define TM_TIMER_FRAME 2000

HINSTANCE instGlobal;
HWND hWindow;

HDC myHDC;
HDC hdcBackBuffer = 0;
HBITMAP myHSurface;
HBITMAP myHoldSurface;

GAMEMANAGER* GAMEMANAGER::_instance = NULL;

SNAKE player;

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
		                   CW_USEDEFAULT, CW_USEDEFAULT, 368, 426,
		                   NULL, NULL, hInstance, NULL);

	if (!hWindow) {
		MessageBox(NULL, L"Error al crear ventana.\nEl programa se cerrará.", L"ERROR", MB_ICONERROR);
		return 1;
	}

	ShowWindow(hWindow, cShow);
	UpdateWindow(hWindow);

	SetTimer(hWindow, TM_TIMER_FRAME, 1000/30, NULL);

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
		manager->ChangeState(instGlobal, MENU_SCREEN);
		manager->InitializeScreen(hwnd);
		break;
	}
	case WM_PAINT: {
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_KEYDOWN: {
		break;
	}
	case WM_TIMER: {
		switch (LOWORD(wparam)) {
		case TM_TIMER_FRAME:
			GAMEMANAGER* manager = GAMEMANAGER::getInstance();
			manager->Renderize();
			manager->Render(hwnd);
			break;
		}
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
		break;
	}
	return 0;
}