#pragma once
#include <iostream>
#include <windows.h>

#include "TextSprite.h"

class TextWindow //Implementuj� tutaj konsolowe podw�jne buforowanie. Poczytaj co to a implementacj� tej klasy ogarnij na ko�cu
{
private:
	bool switcher; //okre�la kt�ry buffer jest aktywny a kt�ry nie
	HANDLE windowBufferOne; //pierwszy bufor okna - szczeg�y w konstruktorze
	HANDLE windowBufferTwo; //drugi
	HANDLE* activeWindowBuffer; //tym wybieram kt�ry bufor aktualnie jest aktywny czyli widoczny
	HANDLE* backgroundWindowBuffer; //tym wybieram kt�ry bufor s�u�y do malowania w nim

public:
	TextWindow();
	TextWindow(unsigned int Width, unsigned int Height);
	~TextWindow();
	void Clear(); //metoda czyszcz�ca bufer
	void Draw(TextSprite sprite); //metoda rysuj�ca w tym oknie buforowym
	void Display(); //wy�wietla obraz - zawarto�� bufferWindow idzie do consoleWindow
};
