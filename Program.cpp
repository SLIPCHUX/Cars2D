// Cars.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <ctime> //
#include <conio.h> //_kbhit()
#include <algorithm>

#include "TextSprite.h"
#include "TextWindow.h"
#include "Coin.h"
#include "Enemy.h"
#include "Player.h"
#include "Track.h"
#include "Program.h"

Program::Program()
{
	isPlayerAlive = true;
	Player* p = new Player();
	player = p;
	callsToCreate = 17;
	
	movable.push_back(p);
}

Program::~Program()
{
}

void Program::GenerateObjects()
{
	static int i = 0; //static raz si� stworzy i z kolejnym wywo�aniem tej metody pracujemy na tej samej zmiennej
	i++;
	
	if (i == callsToCreate)
	{
		i = 0;
		Enemy* e = new Enemy();
		movable.push_back(e);

		if (points < 500)
		{
			callsToCreate = 17;
		}
		else if (points < 1000)
		{
			callsToCreate = 15;
		}
		else if (points < 1500)
		{
			callsToCreate = 13;
		}
		else if (points < 2000)
		{
			callsToCreate = 11;
		}
		else
		{
			callsToCreate = 9;
		}
	}
	if (i % 8 == 0)
	{
		Coin* c = new Coin();

		movable.push_back(c);
	}
}

void Program::RemoveObjects()
{
	//for each (Movable* var in movable)
	for( std::list<Movable*>::iterator var = movable.begin();
         var != movable.end();
         ++var)
	{
		if ((*var)->IsExisting() == false)
		{
			delete (*var);
			movable.remove(*var);

			break;
		}
	}
}

void Program::CheckCollisions()
{
	int i = 0;
	int j = 0;

	//for each (Movable* var in movable)
	for( std::list<Movable*>::iterator var = movable.begin();
         var != movable.end();
         ++var)
	{
		i++;
		(*var)->IsColliding(track);

		//for each (Movable* collider in movable)
		for( std::list<Movable*>::iterator collider = movable.begin();
        	collider != movable.end();
        	++collider)
		{
			j++;
			
			if (i != j) //nie sprawdzam kolizji dla siebie samego
			{
				switch ((*collider)->GetType())
				{
				case Movable::COIN:
					(*var)->IsColliding(*(Coin*)(*collider)); //Nie istnieje co� takiego jak obiekt klasy movable bo to klasa abstrakcyjna
					break;								//mo�na zrobi� za to wska�nik na movable pod kt�rym kryje si� konkretny
				case Movable::ENEMY:					//typ klasy pochodnej. Sprawdzam ten typ i dobieram odpowiedniego case.
					(*var)->IsColliding(*(Enemy*)(*collider));//W case w parametrze metody rzutuj� wska�nik na movable na wska�nik
					break;								//okre�lonego typu i nast�pnie wy�uskuj� obiekt bo metoda przyjmuje
				case Movable::PLAYER:					//obiekt a nie wska�nik na niego
					//std::cin.get();
					(*var)->IsColliding(*(Player*)(*collider)); 
					//std::cin.get();
					break;
				default:
					break;
				}
			}
		}

		j = 0;
	}
}

void Program::MoveObjects()
{
	//for each (Movable* var in movable)
	for( std::list<Movable*>::iterator var = movable.begin();
        var != movable.end();
        ++var)
	{
		(*var)->Move();
	}
}

void Program::DrawObjects(TextWindow _textWindow)
{
	track.Draw(_textWindow);

	//for each (Movable* var in movable)
	for( std::list<Movable*>::iterator var = movable.begin();
        var != movable.end();
        ++var)
	{
		(*var)->Draw(_textWindow);
	}
}

void Program::DrawGameOver(TextWindow _textWindow)
{
	std::string tekst;
	TextSprite GameOverSprite;

	tekst = "***GAME OVER***";
	GameOverSprite.Add(tekst);
	tekst = "";
	GameOverSprite.Add(tekst);
	tekst = "Your score is: " + IntToStr(points);
	GameOverSprite.Add(tekst);
	GameOverSprite.SetPosition(20, 20);

	_textWindow.Draw(GameOverSprite);
}

void Program::GetDataFromPlayer()
{
	 isPlayerAlive = player->IsExisting();
	 points = player->GetPoints();
}

void Program::Delay()
{
	if (isPlayerAlive)
	{
		Sleep(30);	//Jak b�dzie ci zapierdala� to zmie� na wi�ksze. Mo�esz te� zrobi� �eby liczy�o ile czasu min�o
					//od poprzedniego wywo�ania i dopasowa� sleep �eby na ka�dym kompie by�o tak samo pobieraj�c i wyliczaj�c op�nienie.
	}
	else
	{
		Sleep(3000);
	}
}

bool Program::GetIsPlayerAlive()
{
	return isPlayerAlive;
}

//int Program::_Main()
int main()
{
	srand(time(NULL));
	TextWindow textWindow(65, 50);
	Program program; //wszystko si� dzieje w obiekcie klasy Program

	while (program.GetIsPlayerAlive())
	{	
		program.GenerateObjects(); //dok�ada obiekt co jaki� czas
		program.CheckCollisions(); //sprawdza kolizji mi�dzy nimi
		program.MoveObjects(); //porusza obiektami
		program.GetDataFromPlayer(); //ustawia flag� IsPlayerAlive (przed remove objects)
		program.RemoveObjects(); //usuwa niepotrzebne ju� obiekty
		program.DrawObjects(textWindow); //nanosi obiekty na bufor ekranu

		textWindow.Display();//wy�wietla bufor
		program.Delay();
		textWindow.Clear();//bufor jest czyszczony
	}
	
	program.DrawGameOver(textWindow);
	textWindow.Display();
	program.Delay();

	return 0;
}
