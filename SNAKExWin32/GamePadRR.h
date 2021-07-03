#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_

// CÓDIGO DESARROLLADOR POR RAFAEL ALBERTO ROSAS TORRES

//No agrega en la compilada drivers de comunicaciones y otras cosas
#define WIN32_LEAN_AND_MEAN
// Incluimos estas librerias para avanzar
#include <Windows.h>
#include <XInput.h> //libreria del Xbox solo gamepads o joysticks compatibles
// XBOX Controller Class Definition
class GamePadRR {

    XINPUT_STATE estadoControlador;
	XINPUT_BATTERY_INFORMATION batería;
	XINPUT_CAPABILITIES capacidades;
    int numeroControlador;

public:

	GamePadRR(int jugadorNumero);

	XINPUT_STATE GetState();
	XINPUT_BATTERY_INFORMATION GetBatteryState();
	XINPUT_CAPABILITIES GetCapabilities();

	bool IsConnected();
	void Vibrate(int leftVal, int rightVal);

	//estas son las equivalencias a los botonazos mas comunes
	/*XINPUT_GAMEPAD_DPAD_UP          0x00000001
	XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
	XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
	XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
	XINPUT_GAMEPAD_START            0x00000010
	XINPUT_GAMEPAD_BACK             0x00000020
	XINPUT_GAMEPAD_LEFT_THUMB       0x00000040
	XINPUT_GAMEPAD_RIGHT_THUMB      0x00000080
	XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
	XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
	XINPUT_GAMEPAD_A                0x1000
	XINPUT_GAMEPAD_B                0x2000
	XINPUT_GAMEPAD_X                0x4000
	XINPUT_GAMEPAD_Y                0x8000*/
};

#endif