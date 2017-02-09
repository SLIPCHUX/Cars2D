//#include "stdafx.h"
#include "TextWindow.h"

//Generalnie to co tu si� dzieje jest trudne i zostaw to sobie na koniec.
//Korzystam tutaj z Windows API. Da�o si� to zrobi� pro�ciej efekt by� by gorszy a po za tym chcia�em pobawi� si� tymi funkcjami.
//windowsowe API (Application Programing Interface) jest napisane w j�zyku C czyli strukturalnie.
//Poni�szy kod to implementacja klasy TextWindow (kod obiektowy) w oparciu o bibliotek� z j�zyka C (kod strukturalny).

TextWindow::TextWindow()
{
	switcher = false;
	windowBufferOne = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	windowBufferTwo = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	activeWindowBuffer = &windowBufferOne;
	backgroundWindowBuffer = &windowBufferTwo;
	//Tworz� dwa bufory dla ekranu konsoli. Wszystko co pisz� wewn�trz bufora jest niewidoczne na ekranie konsoli dop�ki
	//nie ustawi� danego bufora jako aktywny. Chodzi o to �e operacja uaktywniania bufora jest du�o szybsza ni� pisanie
	//bezpo�rednio na oknie konsoli. Gdybym pisa� bezpo�rednio na oknie konsoli by�oby wida� nieprzyjemne migotanie.
	//Jak nie wierzysz spr�buj w niesko�czonej p�tli zape�ni� ekran 10000 liter a nast�pnie to czy�ci� i tak w k�ko.
	//Mo�na by�o zminimalizowa� miganie w mniej zaawansowany i mniej efektywny spos�b ale chcia�em si� przy okazji czego� nauczy�.
	//Poczytaj sobie czym w og�le jest podw�jne buforowanie.
}

TextWindow::TextWindow(unsigned int Width, unsigned int Height)
{
	switcher = false;
	windowBufferOne = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	windowBufferTwo = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	activeWindowBuffer = &windowBufferOne;
	backgroundWindowBuffer = &windowBufferTwo;
	
	SMALL_RECT rect = { 0 ,0, Width, Height };

	SetConsoleWindowInfo(windowBufferOne, 1, &rect); //ta funkcja jest do�� uparta i jak nie spodobaj� si� jej dane to je ignoruje
	SetConsoleWindowInfo(windowBufferTwo, 1, &rect); //mo�na zrobi� walidacj� danych i jak b�d� za du�e to wstawi� maksymalne mo�liwe
}

TextWindow::~TextWindow()
{
}

void TextWindow::Clear()
{
	COORD topLeft = { 0 , 0 };
	CONSOLE_SCREEN_BUFFER_INFO bufferWindowInfo;
	DWORD written;

	GetConsoleScreenBufferInfo(*backgroundWindowBuffer, &bufferWindowInfo); //To ca�e info wykokrzystuj� �eby wiedzie� iloma spacjami wyczy�ci� ekran
	FillConsoleOutputCharacterA(*backgroundWindowBuffer, ' ', bufferWindowInfo.dwSize.X * bufferWindowInfo.dwSize.Y, topLeft, &written);
	SetConsoleCursorPosition(*backgroundWindowBuffer, topLeft);
}

void TextWindow::Draw(TextSprite sprite)
{
	COORD cord;
	DWORD written;
	cord = sprite.GetPosition();

	//for each (std::string line in sprite.GetSprite())
	for( std::list<std::string>::iterator line = sprite.GetSprite().begin();
        line != sprite.GetSprite().end();
        ++line)
	{
		//for each (char ch in line)
		for( std::string::iterator ch = (*line).begin();
        	ch != (*line).end();
        	++ch)
		{
			SetConsoleCursorPosition(*backgroundWindowBuffer, cord); //w oknie b�d�cym w tle ustawiam kursor na odpowiednich wsp�rz�dnych
			FillConsoleOutputCharacterA(*backgroundWindowBuffer, *ch, 1, cord, &written);
			cord.X++;
		}
		cord.X = sprite.GetPosition().X;
		cord.Y++;
	}
}

void TextWindow::Display()
{
	CONSOLE_SCREEN_BUFFER_INFO windowInfo;
	GetConsoleScreenBufferInfo(&activeWindowBuffer, &windowInfo);
	SetConsoleScreenBufferSize(&backgroundWindowBuffer, windowInfo.dwSize);

	switcher = !switcher; //zmiana stanu prze��cznika
	activeWindowBuffer = (switcher == false) ? &windowBufferOne : &windowBufferTwo; //skr�cony if
	//Je�li prze��cznik wy��czony to aktywne jest okno jeden, jak w��czony to aktywne jest okno dwa
	backgroundWindowBuffer = (switcher == false) ? &windowBufferTwo : &windowBufferOne;
	
	SetConsoleActiveScreenBuffer(*activeWindowBuffer);
}
