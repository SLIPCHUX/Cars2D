#pragma once
#include <list>

#include "Movable.h"

class TextWindow;

class Program
{
private:
	std::list<Movable*> movable;
	Track track;
	Player* player;	//Obiekt klasy player stnieje zar�wno w li�cie jak i tutaj. To ten sam obiekt. Mo�e istnie� w dw�ch miejscach
					//jednocze�nie dzi�ki zastosowaniu wska�nik�w. Dok�adniej to jest w jednym miejscu a w wielu sa jego referencje
	int callsToCreate; //Liczba wywo�a� metody GenerateObjects do stworzenia wroga
	bool isPlayerAlive;
	int points;

public:
	Program();
	~Program();
	void GenerateObjects();
	void RemoveObjects();
	void CheckCollisions();
	void MoveObjects();
	void DrawObjects(TextWindow _textWindow);
	void DrawGameOver(TextWindow _textWindow);
	void GetDataFromPlayer(); //tu u�ywam wska�nika na playera �eby nie iterowa� po ca�ej li�cie i go nie szuka�
	void Delay();
	bool GetIsPlayerAlive();
	
	//static int _Main();
};
