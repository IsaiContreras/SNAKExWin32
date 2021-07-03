#include "GamePadRR.h"

GamePadRR::GamePadRR(int jugadorNumero) {
	// establece el numero de jugador
	numeroControlador = jugadorNumero - 1;
}

XINPUT_STATE GamePadRR::GetState() {
	ZeroMemory(&estadoControlador, sizeof(XINPUT_STATE));
	XInputGetState(numeroControlador, &estadoControlador);
	return estadoControlador;
}
XINPUT_BATTERY_INFORMATION GamePadRR::GetBatteryState() {
	ZeroMemory(&batería, sizeof(XINPUT_BATTERY_INFORMATION));
	XInputGetBatteryInformation(numeroControlador, BATTERY_DEVTYPE_GAMEPAD, &batería);
	return batería;
}
XINPUT_CAPABILITIES GamePadRR::GetCapabilities() {
	ZeroMemory(&capacidades, sizeof(XINPUT_CAPABILITIES));
	XInputGetCapabilities(numeroControlador, XINPUT_FLAG_GAMEPAD, &capacidades);
	return capacidades;
}

bool GamePadRR::IsConnected() {
	ZeroMemory(&estadoControlador, sizeof(XINPUT_STATE));
	DWORD Resultado = XInputGetState(numeroControlador, &estadoControlador);
	if (Resultado == ERROR_SUCCESS)
		return true;
	else return false;
}
void GamePadRR::Vibrate(int leftVal = 0, int rightVal = 0) {
	XINPUT_VIBRATION Vibracion;
	ZeroMemory(&Vibracion, sizeof(XINPUT_VIBRATION));
	Vibracion.wLeftMotorSpeed = leftVal;
	Vibracion.wRightMotorSpeed = rightVal;
	XInputSetState(numeroControlador, &Vibracion);
}