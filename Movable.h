#pragma once

class Track;
class Player;
class Enemy;
class Coin;
class Box;
class TextWindow;

//To tylko deklaracje klas (brak cia�a). Jak widzisz nie ma tu �adnego nag��wka kt�ry m�wi�by o ich istnieniu.
//Klasa ta nabiorze sensu dopiero w klasach, kt�re dziedzicz� po Movable. Te klasy zawieraj�
//w plikach nag��wkowych includy do prawdziwych TextSprite i TextWindow gdzie s� one ju� zdefiniowane

//Lubi� u�ywa� dziedziczenia w taki spos�b jak interfejs�w w innych j�zykach czyli bez �adnych p�l i bez
//cia� metod (metody czysto wirtualne). W ten spos�b tylko okre�lam co dana klasa dziedzicz�ca musi potrafi� no i
//mog� traktowa� je w zbiorczy spos�b. Mog� zrobi� tabel� typu Movable a w �rodku b�dzie jaki� Coin, Player itp.
//Logiki nie dziedzicz� tylko pakuj� do takich jakby komponent�w. Przyk�adem takiego komponentu jest klasa Box

class Movable
{
public:
	Movable();
	~Movable();
	virtual void Move() = 0; // = 0 oznacza metod� czysto wirtualn�
	virtual void IsColliding(Track _track) = 0;
	virtual void IsColliding(Player _player) = 0;
	virtual void IsColliding(Enemy _enemy) = 0;
	virtual void IsColliding(Coin _coin) = 0;
	virtual void SetPosition(int XCoord, int YCoord) = 0;
	virtual Box & GetBody() = 0;
	virtual bool IsExisting() = 0;
	virtual void Draw(TextWindow _textWindow) = 0;

	enum type
	{
		COIN,
		ENEMY,
		PLAYER,
		TRACK,
	};

	virtual type GetType() = 0;
};
