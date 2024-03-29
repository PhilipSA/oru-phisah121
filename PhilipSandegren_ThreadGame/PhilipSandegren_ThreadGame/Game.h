#pragma once

#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include "Player.h"

using namespace std;

class Game
{
private:
	mutex mutex_queue;
	char knapp;
	deque<char> *key1;
	deque<char> *key2;
	deque<playerInfo> *pos;
	playerInfo thePlayer;
public:
	//Den ber�mda gotoxy f�r att flytta mark�ren i konsoll f�nster
	void gotoxy(int x, int y)
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
	//Ritar ut spelplanen
	void drawGameField()
	{
		for (int a = 0; a<7; ++a)
		{
			for (int i = 0; i < 67; ++i)
			{
				cout << "-";
			}
			cout << "\n";
			for (int i = 0; i < 12; ++i)
			{
				cout << "|     ";
			}
			cout << "\n";
			for (int i = 0; i < 67; ++i)
			{
				cout << "-";
			}
			cout << "\n";
		}
	}

	//Ritar ut aktuell spelares position baserat p� datat som ligger f�rst i k�n
	void movePlayer(char getch)
	{
		if (!pos->empty())
		{
			mutex_queue.lock();
			thePlayer = pos->front();
			pos->pop_front();
			mutex_queue.unlock();
			gotoxy(thePlayer.x, thePlayer.y);
			if (thePlayer.id == 1)
			{
				std::cout << '1';
			}
			else if (thePlayer.id == 2)
			{
				std::cout << '2';
			}
		}
	}

	//Main funktionen som k�r ig�ng programmet
	void GameMain()
	{
		drawGameField();
		gotoxy(3,1);
		cout << '1';
		do {
			if (_kbhit())
			{
				knapp = _getch();
				if (whichPlayer(knapp) == true)
				{
					mutex_queue.lock();
					key1->push_back(knapp);
					mutex_queue.unlock();
				}
				else if (whichPlayer(knapp) == false)
				{
					mutex_queue.lock();
					key2->push_back(knapp);
					mutex_queue.unlock();
				}
				movePlayer(knapp);
			}
		} while (true);
	}
	
	//Avg�r om spelare 1 eller 2 tryckte p� tangetbordet
	bool whichPlayer(char enKnapp)
	{
		if (knapp == 'w' || knapp == 'a' || knapp == 's' || knapp == 'd')
			return true;
		else
			return false;
	}

	Game(void)
	{

	}
	//Konstruktor med pekare till alla k�er
	Game(deque<char> *k1, deque<char> *k2, deque<playerInfo> *p)
	{
		key1=k1;
		key2=k2;
		pos=p;
	}

	~Game(void)
	{
	}
};

