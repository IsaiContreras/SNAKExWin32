#ifndef _SPRITE_CLASS
#define _SPRITE_CLASS

#include <Windows.h>

class SPRITE {
	HBITMAP hImage;
	HBITMAP hMask;
	BITMAP bmpImage;
	BITMAP bmpMask;
	int width;
	int height;
public:
	// Cargar sprite.
	void LoadSprite(HINSTANCE, UINT, UINT);
	// Dibujar el sprite.
	void Draw(HDC, HDC, int posx, int poxy);

	// Asignar objeto hImage.
	void SetHBMImage(HBITMAP);
	// Asignar objeto hMask.
	void SetHBMMask(HBITMAP);
	// Obtener objeto hImage.
	HBITMAP GetHBMImage();
	// Obtener objeto hMask.
	HBITMAP GetHBMMask();
	
	// Asignar objeto bmpImage.
	void SetBMImage(BITMAP);
	// Asignar objeto bmpMask.
	void SetBMMask(BITMAP);
	// Obtener objeto bmpImage.
	BITMAP GetBMImage();
	// Obtener objeto bmpMask.
	BITMAP GetBMMask();

	// Asignar valor de ancho.
	void SetWidth(int);
	// Asignar valor de altura.
	void SetHeight(int);
	// Obtener valor de ancho.
	int GetWidth();
	// Obtener valor de altura.
	int GetHeight();

};

#endif