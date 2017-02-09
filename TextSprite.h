#pragma once
#include <iostream>
#include <windows.h>
#include <list>

class TextSprite
{
private:
	std::list<std::string> sprite; //lista to taka struktura danych kt�ra dopasowuje swoj� wielko�� do ilo�ci element�w. Obs�uguje si� podobnie ale dzia�a na ciut innej zasadzie
	COORD position; //COORD to struktura przyjmuj�ca wsp�rz�dne x i y. Jest to cz�� biblioteki windows.h i u�ywa si� tego do rysowania na ekranie w okre�lonym punkcie

public:
	TextSprite();
	~TextSprite();
	void Add(std::string line);
	void SetPosition(int XCord, int YCord);
	COORD GetPosition();
	std::list<std::string> & GetSprite(); //zwracam referencj� (&) do listy
	int GetWidth();
	int GetHeight();
};
