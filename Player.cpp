//#include "stdafx.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "Track.h"

std::string IntToStr(int val) //To nie jest metoda klasy tylko zwyk�a funkcja. NIEOBIEKTOWY fragment kodu.
{
	std::string retval = "";
	char character = ' ';
	const char FirstASCIINumber = 48;

	while (val > 0)
	{
		character = (val % 10) + FirstASCIINumber;
		val = val / 10;
		retval = character + retval;
	}

	return retval;
}

Player::Player()
{
	speed = 2;
	health = 100;
	points = 0;

	bodyTextSprite.Add("0-^-0");
	bodyTextSprite.Add("|,_,|");
	bodyTextSprite.Add("|[_]|");
	bodyTextSprite.Add("0---0");

	bodyTextSprite.SetPosition(3, 30);

	body.SetLeft(bodyTextSprite.GetPosition().X);
	body.SetTop(bodyTextSprite.GetPosition().Y);
	body.SetHeight(bodyTextSprite.GetHeight());
	body.SetWidth(bodyTextSprite.GetWidth());
}

Player::~Player()
{
}

void Player::Move()
{
	points++;

	int x = body.GetLeft();
	int y = body.GetTop();

	if (GetAsyncKeyState(VK_LEFT) && !leftLocked)	//GetAsyncKeyState zwraca warto�� niezerow� je�li przycisk jest wci�ni�ty
	{												//Ka�da niezerowa warto�� jest traktowana jak logiczne true
		x -= speed;
	}
	if (GetAsyncKeyState(VK_RIGHT) && !rightLocked)
	{
		x += speed;
	}
	if (GetAsyncKeyState(VK_UP) && !upLocked)
	{
		y -= speed / 2;
	}
	if (GetAsyncKeyState(VK_DOWN) && !downLocked)
	{
		y += speed;
	}

	body.SetLeft(x);
	body.SetTop(y);
	bodyTextSprite.SetPosition(x, y);
}

void Player::IsColliding(Track _track)
{
	leftLocked = (body.CheckIfCollides(_track.GetLeftBorder())); //inaczej if ((body.CheckIfCollides(_track.GetLeftBorder()) == true)) leftLocked = true; else LeftLocked = false;
	rightLocked = (body.CheckIfCollides(_track.GetRightBorder())); //je�li koliduj� z praw� �ciank� to wyra�enie w nawiasie jest true a je�li nie to false
	upLocked = (body.GetTop() <= _track.GetLeftBorder().GetTop()); //tu tak samo
	downLocked = (body.GetBottom() >= _track.GetLeftBorder().GetBottom()); //rightBorder ma tak� sam� wysoko�� i szeroko�� co leftBorder
}

void Player::IsColliding(Player _player)
{
	//Do nothing
}

void Player::IsColliding(Enemy _enemy)
{
	if (body.CheckIfCollides(_enemy.GetBody()) == true) //Napisa�em klas� Box a dla niej metod� wykrywaj�c� kolizje
	{													//Gdy chc� sprawdzi� kolizje mi�dzy jakimi� elementami to
		health -= 10;									//tak naprawd� sprawdzam kolizj� mi�dzy ich Boxami
	}
}

void Player::IsColliding(Coin _coin)
{
	if (body.CheckIfCollides(_coin.GetBody()) == true)
	{
		points += 30;
	}
}

void Player::Draw(TextWindow _textWindow)
{
	_textWindow.Draw(bodyTextSprite);

	DrawValues(_textWindow);
}

void Player::DrawValues(TextWindow _textWindow)
{
	TextSprite valuesTextSprite;
	valuesTextSprite.SetPosition(50, 3);

	std::string pointBar = "POINTS: " + IntToStr(points);
	std::string healthBar = "HEALTH: " + IntToStr(health);

	valuesTextSprite.Add(pointBar);
	valuesTextSprite.Add(healthBar);

	_textWindow.Draw(valuesTextSprite);
}

void Player::SetPosition(int XCoord, int YCoord)
{
	body.SetLeft(XCoord);
	body.SetTop(YCoord);
}

Box & Player::GetBody()
{
	return body;
}

bool Player::IsExisting()
{
	return (health > 0); //Taka sztuczka. Zwracana jest warto�� wyra�enia w nawiasie. Jak zdrowie wi�ksze od zera to true jak nie to false;
}

Movable::type Player::GetType()
{
	return PLAYER;
}

int Player::GetPoints()
{
	return points;
}

