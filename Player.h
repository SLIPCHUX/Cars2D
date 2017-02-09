#pragma once
#include <iostream>
#include <list>
#include <Windows.h>

#include "Movable.h"
#include "Box.h"
#include "TextSprite.h"
#include "TextWindow.h"

std::string IntToStr(int val);

class Player : public Movable
{
private:
	int speed;
	int health;
	int points;

	bool leftLocked; //Jak jest true to blokuje mo�liwo�� skr�tu w lewo. Nie mo�na skr�ci� w lewo jak koliduje si� z lew� �cian� toru
	bool rightLocked;
	bool upLocked;
	bool downLocked;

	Box body;
	TextSprite bodyTextSprite;

public:
	Player();
	~Player();
	void Move();
	void IsColliding(Track _track);
	void IsColliding(Player _player);
	void IsColliding(Enemy _enemy);
	void IsColliding(Coin _coin);
	void Draw(TextWindow _textWindow);
	void DrawValues(TextWindow _textWindow);
	void SetPosition(int XCoord, int YCoord);
	Box & GetBody();
	bool IsExisting();
	type GetType();
	int GetPoints();
};
