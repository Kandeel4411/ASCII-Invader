#include "Menu.h"
#include "Fire.h"
#include "Player.h"
#include "Monster.h"
#include "Invader.h"

#include <windows.h>
#include <curses.h>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>   
#include <ctime>
#include <vector>
#pragma comment(lib, "Winmm.lib")

bool Invader::playing = true;
int Invader::borderY;
int Invader::setLevel = -1;
Monster Invader::Boss;

void Invader::SetupLevel()
{

	firePlayer.clear();
	
	if (!Settings::Boss)
	{
		bossWait = clock() + 0 * CLOCKS_PER_SEC;

		setLevel++;
		Menu::settingsLevel.push_back(Settings(setLevel));
		
		if (setLevel == 6) playing = false;
		mciSendString("stop intro2_sound", NULL, 0, NULL);
		mciSendString("play intro1_sound repeat", NULL, 0, NULL);
	}
	else
	{
		mciSendString("stop intro1_sound", NULL, 0, NULL);
		mciSendString("play intro2_sound repeat", NULL, 0, NULL);
		bossWait = clock() + (setLevel + 3) * CLOCKS_PER_SEC;
		Menu::settingsLevel[setLevel] = Settings(setLevel);
	}

	bossDeath = 0;
	bossCreated = 0;

	getmaxyx(stdscr, maxX, maxY);
	borderY = maxY-1;
	borderX = maxX-1;
	endWait = clock() + 0* CLOCKS_PER_SEC;

	Player::player.movement = Player::STOP;
	Player::player.x = maxX - 4;
	Player::player.y = (Settings::col / 2) - 1;
}
void Invader::InputWindow()
{

	if ((ch == 'd' || ch == 'D') && Player::player.movement == Player::RIGHT)
	{
		Player::player.y += Menu::settingsLevel[setLevel].moveBoost;
	}
	else if ((ch == 'a' || ch == 'A') && Player::player.movement == Player::LEFT) 
	{
		Player::player.y -= Menu::settingsLevel[setLevel].moveBoost; 
	}
	else if (ch == 'd' || ch == 'D')
	{
		Player::player.movement = Player::RIGHT; 
	}
	else if (ch == 'a' || ch == 'A') 
	{
		Player::player.movement = Player::LEFT;
	} 
	else if (ch == 'x')
	{
		if(Menu::settingsLevel[setLevel].score >= Menu::settingsLevel[setLevel].setLifeScore)
		{
			Menu::settingsLevel[setLevel].life++;
			Menu::settingsLevel[setLevel].score -= Menu::settingsLevel[setLevel].setLifeScore;
		}
	}
	else if (ch == ' ') 
	{
		if (bossWait < clock())
		{
		firePlayer.push_back(Fire(Player::player.x + 1,Player::player.y+1));
		firePlayer.push_back(Fire(Player::player.x + 1, Player::player.y-1));
		mciSendString("play player_sound from 0", NULL, 0, NULL);

		}
	}
}
void Invader::Logic()
{
	MovementLogic();
	CollisionLogic();
	GeneralLogic();
	MonsterLogic();
}
void Invader::DisplayWindow()
{
	for (int i = 0; i < maxX; i++)
	{
		for (int j = 0; j < maxY; j++)
		{
			if (RandInt(0, 100) < 99)
			{
				mvaddch(i, j, ' ');
			}
			else
			{
				if (RandInt(0, 1) == 1)
				{
						mvaddch(i, j, '.');
				}
				else
				{
					mvaddch(i, j, '.' | COLOR_PAIR(RandInt(12, 14)) );
				}
			}
		}
	}
	attron(A_BOLD);
	if (Settings::Boss)
	{
		int x = RandInt(12, 14);
		attron(COLOR_PAIR(x));
		box(stdscr, '|', '-');
		attroff(COLOR_PAIR(x));
	}
	else
	{
	attron(COLOR_PAIR(C_BORDER));
	box(stdscr, '|', '-');
	attroff(COLOR_PAIR(C_BORDER));
	}

	attron(COLOR_PAIR(C_INVADER_COUNT));
	mvprintw(0, borderY - 10, "Level : %d", setLevel);
	attroff(COLOR_PAIR(C_INVADER_COUNT));

	attron(COLOR_PAIR(C_INVADER_COUNT));
	mvprintw( 0, 1, "INVADERS : %d", Menu::settingsLevel[setLevel].shipSpawn);
	attroff(COLOR_PAIR(C_INVADER_COUNT));
	attroff(A_BOLD);

		Player::DrawPlayer(firePlayer.begin(),firePlayer.end());
		Monster::DrawMonster(monsterShip.begin(),monsterShip.end(),fireMonster.begin(), fireMonster.end());
		if(bossCreated)
		Monster::DrawBoss(fireBoss.begin(), fireBoss.end());
	
	attron(A_BOLD);
	attron(COLOR_PAIR(C_PLAYER_LIVE));
	mvprintw( borderX - 2, 1, "LIVES : %d", Menu::settingsLevel[setLevel].life);
	attroff(COLOR_PAIR(C_PLAYER_LIVE));

	attron(COLOR_PAIR(C_PLAYER_SCORE));
	mvprintw( borderX - 1, 1, "SCORE : %d", Menu::settingsLevel[setLevel].score);
	attroff(COLOR_PAIR(C_PLAYER_SCORE));

	attron(COLOR_PAIR(C_SET_LIFE));
	mvprintw( borderX    , 1 , "*** PRESS 'X' TO SPEND %d SCORE POINTS FOR A life *** ",Menu::settingsLevel[setLevel].setLifeScore);
	attroff(COLOR_PAIR(C_SET_LIFE));
	attroff(A_BOLD);

		
		refresh();
		ch = getch();
		clear();
}

void Invader::CreateAlien()
{
	if (!Settings::Boss)
	{
		randY = RandInt(4, Settings::col - 4);
		monsterShip.push_back(Monster(1, randY));
	}
	else
	{
		monsterShip.push_back(Monster(1, 4));
	}
}
void Invader::CreateBoss()
{
	Invader::Boss = Monster(1, 4, 5);
	bossCreated = 1;
}

void Invader::MovementLogic()
{
	Fire::MonsterFireMove(fireMonster.begin(), fireMonster.end());
	Fire::MonsterFireMove(fireBoss.begin(), fireBoss.end());

	if (clock() > bossWait)
	{
		Fire::PlayerFireMove(firePlayer.begin(), firePlayer.end());

		if (Player::player.y >= borderY - 2)
		{
			Player::player.movement = Player::LEFT;
		}
		else if (Player::player.y <= 2)
		{
			Player::player.movement = Player::RIGHT;
		}

		switch (Player::player.movement)
		{
		case Player::LEFT:
			Player::player.y -= Menu::settingsLevel[setLevel].move;
			break;
		case Player::RIGHT:
			Player::player.y += Menu::settingsLevel[setLevel].move;
			break;
		default:
			break;
		}
	}
}
void Invader::CollisionLogic()
{
	CollisionFireMonster();
	CollisionFireBoss();
	CollisionFirePlayer();
	CollisionMonsterShip();
}
void Invader::MonsterLogic()
{
	if (bossCreated)
	{
		Monster::BossMove();
		Monster::MonsterMove(monsterShip.begin(), monsterShip.end());
	}
	if (clock() > endWait)
	{
		if (Menu::settingsLevel[setLevel].shipSpawn != 0)
		{
			Menu::settingsLevel[setLevel].shipSpawn--;
			CreateAlien();
		}
		if (Settings::Boss == 0)
		{
			Monster::turn = !(Monster::turn);
			Monster::MonsterMove(monsterShip.begin(), monsterShip.end());
		}
		
		bool flag = 0;
		for (int i = 0; i < static_cast<int>(monsterShip.size()); i++)
		{
			if (Settings::Boss && setLevel >= 3)
			{
				if (clock() > bossWait)
				{
					flag = 1;
					fireMonster.push_back(Fire(monsterShip[i].x + 1, monsterShip[i].y));
				}
			}
			else
			{
				if (RandInt(0, 1) == 1)
				{
					if (clock() > bossWait)
					{
						flag = 1;
						fireMonster.push_back(Fire(monsterShip[i].x + 1, monsterShip[i].y));
					}
				}
			}
		}

		endWait = clock() + Menu::settingsLevel[setLevel].timeSpawn * CLOCKS_PER_SEC;
		
		if (bossCreated)
		{
			if (clock() > bossWait)
			{
				flag = 1;
				fireBoss.push_back(Fire(Invader::Boss.x + 1, Invader::Boss.y - 1));
				fireBoss.push_back(Fire(Invader::Boss.x + 1, Invader::Boss.y + 1));
			}
		}
		if (flag)
		{
			mciSendString("play shooting_sound from 0", NULL, 0, NULL);
		}

	}
}
void Invader::GeneralLogic()
{
	if (Menu::settingsLevel[setLevel].life <= 0)
	{
		playing = false;
		mciSendString("play final_sound wait", NULL, 0, NULL);
		return;
	}
    if (Menu::settingsLevel[setLevel].shipSpawn == 0 && monsterShip.size() == 0)
	{
		if (setLevel >= 2 && Settings::Boss == 0)
		{
			Settings::Boss = 1;
			SetupLevel();
			Settings::score += Menu::settingsLevel[setLevel].life * Menu::settingsLevel[setLevel].incScore;
			CreateBoss();
		}
		else if (bossDeath)
		{
			Settings::Boss = 0;
			mciSendString("play b_death_sound from 0", NULL, 0, NULL);
			SetupLevel();
			Settings::score += Menu::settingsLevel[setLevel].life * Menu::settingsLevel[setLevel].incScore;
		}
		else if (setLevel < 2)
		{
			SetupLevel();
			Settings::score += Menu::settingsLevel[setLevel].life * Menu::settingsLevel[setLevel].incScore;
		}
	}
}

void Invader::CollisionFireMonster()
{
	for (int i = 0; i < fireMonster.size(); i++)
	{
		if (fireMonster[i].x > Player::player.x)
		{
			fireMonster[i] = fireMonster[fireMonster.size() - 1];
			fireMonster.pop_back();
			--i;
			continue;
		}

		for (int j = 1; j >= 0; j--)
		{

			if (fireMonster[i].x == Player::player.x && ((fireMonster[i].y == Player::player.y - j) || (fireMonster[i].y == Player::player.y + j)))
			{
				fireMonster[i] = fireMonster[fireMonster.size() - 1];
				fireMonster.pop_back();
				--i;
				if (clock() > bossWait)
				{
					Menu::settingsLevel[setLevel].life--;
					mciSendString("play life_lost_sound from 0", NULL, 0, NULL);
				}
				break;
			}
		}
	}
	//////////////////////////////////////////////////////////
	for (int i = 0; i < fireMonster.size(); i++)
	{
		for (int j = 0; j < firePlayer.size(); j++)
		{
			for (int k = 1; k >= 0; k--)
			{
				if (firePlayer[j].x == fireMonster[i].x && ((fireMonster[i].y == firePlayer[j].y - k) || (fireMonster[i].y == firePlayer[j].y + k)))
				{
					firePlayer[j] = firePlayer[firePlayer.size() - 1];
					firePlayer.pop_back();
					fireMonster[i] = fireMonster[fireMonster.size() - 1];
					fireMonster.pop_back();
					--i;
					j = firePlayer.size();

					mciSendString("play b_death_sound from 0", NULL, 0, NULL);
					break;
				}
			}
		}
	}
} 
void Invader::CollisionFireBoss()
{
	for (int i = 0; i < fireBoss.size(); i++)
	{
		if (fireBoss[i].x > Player::player.x)
		{
			fireBoss[i] = fireBoss[fireBoss.size() - 1];
			fireBoss.pop_back();
			--i;
			continue;
		}
		for (int j = 1; j >= 0; j--)
		{

			if (fireBoss[i].x == Player::player.x && ((fireBoss[i].y == Player::player.y - j) || (fireBoss[i].y == Player::player.y + j)))
			{
				fireBoss[i] = fireBoss[fireBoss.size() - 1];
				fireBoss.pop_back();
				--i;
				Menu::settingsLevel[setLevel].life--;
				mciSendString("play life_lost_sound from 0", NULL, 0, NULL);
				break;
			}
		}
	}
}
void Invader::CollisionFirePlayer()
{
	for (int i = 0; i < firePlayer.size(); i++)
	{
		if (firePlayer[i].x <= 0)
		{
			firePlayer[i] = firePlayer[firePlayer.size() - 1];
			firePlayer.pop_back();
			--i;
			continue;
		}
		for (int j = 0; j < monsterShip.size(); j++)
		{
			for (int k = 2; k >= 0; k--)
			{

				if (firePlayer[i].x == monsterShip[j].x && ((firePlayer[i].y == monsterShip[j].y - k) || (firePlayer[i].y == monsterShip[j].y + k)))
				{
					firePlayer[i] = firePlayer[firePlayer.size() - 1];
					firePlayer.pop_back();
					--i;
					monsterShip[j] = monsterShip[monsterShip.size() - 1];
					monsterShip.pop_back();
					j = monsterShip.size();

					mciSendString("play enemy_sound from 0", NULL, 0, NULL);
					Menu::settingsLevel[setLevel].score += Menu::settingsLevel[setLevel].incScore;
					break;
				}
			}
		}
	}
	/////////////////////////////////////////////////////
	for (int i = 0; i < firePlayer.size(); i++)
	{
		for (int k = 2; k >= 0; k--)
		{

			if (firePlayer[i].x == Invader::Boss.x && ((firePlayer[i].y == Invader::Boss.y - k) || (firePlayer[i].y == Invader::Boss.y + k)))
			{
				firePlayer[i] = firePlayer[firePlayer.size() - 1];
				firePlayer.pop_back();
				--i;
				Invader::Boss.bossHP--;
				if (Invader::Boss.bossHP == 0)
				{
					i = firePlayer.size();
					bossDeath = 1;
					Menu::settingsLevel[setLevel].score += Menu::settingsLevel[setLevel].incScore * 5;
				}
				break;
			}
		}
	}

}
void Invader::CollisionMonsterShip()
{
	for (int i = 0; i < monsterShip.size(); i++)
	{
		if (monsterShip[i].x >= Player::player.x)
		{
			Menu::settingsLevel[setLevel].life--;

			monsterShip[i] = monsterShip[monsterShip.size() - 1];
			monsterShip.pop_back();

			Menu::settingsLevel[setLevel].shipSpawn++;
			--i;

		}
	}
}

Invader::Invader()
{
	Menu::MainMenu();
}