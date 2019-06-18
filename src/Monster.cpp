#include "Fire.h"
#include "Player.h"
#include "Monster.h"
#include "Invader.h"
#include "Menu.h"

#include <windows.h>
#include <curses.h>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>   
#include <ctime>
#include <vector>

bool Monster::turn = false;

void Monster::MonsterMove(const std::vector<Monster>::iterator first, const std::vector<Monster>::iterator last)
{
	if (!Settings::Boss)
	{

	for (auto i = first; i < last; ++i)
		i->x++;
	}
	else
	{
		for (auto i = first; i < last; ++i)
		{
			if (i->y >= Invader::borderY - 6)
			{
				i->x+=3;
				i->check = 1;
			}
			else if (i->y <= 4)
			{
				i->x+=3;
				i->check = 0;
			}

			if (i->check)
			{
				i->y--;
			}
			else
			{
				i->y++;
			}
		}
	}
}
void Monster::DrawMonster(const std::vector<Monster>::iterator first, const std::vector<Monster>::iterator last, const std::vector<Fire>::iterator first2, const std::vector<Fire>::iterator last2)
{

	attron(COLOR_PAIR(C_MONSTER));

	if (Settings::Boss)
	{
		for (auto i = first; i < last; i++)
		{
			if (RandInt(0, 1) == 1)
			{
				DrawShip1(i);
			}
			else
			{
				DrawShip2(i);
			}
		}
	}
	else
	{
		for (auto i = first; i < last; i++)
		{
			if (Monster::turn)
			{
				DrawShip1(i);
			}
			else
			{
				DrawShip2(i);
			}
		}
	}

	attroff(COLOR_PAIR(C_MONSTER));


	attron(A_BOLD);
	attron(COLOR_PAIR(C_MONSTER_FIRE));

	for (auto i = first2; i < last2; i++)
	{
		if (RandInt(0, 1) == 1)
			Fire::DrawFire2(i);
		else
			Fire::DrawFire4(i);

	}

	attroff(A_BOLD);
	attroff(COLOR_PAIR(C_MONSTER_FIRE));

}

void Monster::BossMove()
{
	if (Invader::Boss.y >= Invader::borderY - 6)
	{
		Invader::Boss.check = 1;
	}
	else if (Invader::Boss.y <= 4)
	{
		Invader::Boss.check = 0;
	}

	if (Invader::Boss.check)
	{
		Invader::Boss.y -= 1;
	}
	else
	{
		Invader::Boss.y += 1;
	}
}

void Monster::DrawBoss(const std::vector<Fire>::iterator first, const std::vector<Fire>::iterator last)
{
	attron(A_BOLD);
	attron(COLOR_PAIR(C_BOSS));
	DrawShip3();
	attroff(COLOR_PAIR(C_BOSS));
	attroff(A_BOLD);

	attron(A_BOLD);
	attron(COLOR_PAIR(C_BOSS_FIRE));
	for (auto i = first; i < last; i++)
	{
		if (RandInt(0, 1) == 1)
		{

			Fire::DrawFire1(i);
		}
		else
		{
			Fire::DrawFire3(i);
		}
	}
	attroff(A_BOLD);
	attroff(COLOR_PAIR(C_BOSS_FIRE));

}

void Monster::DrawShip1(const std::vector<Monster>::iterator i)
{
	mvaddch( i->x, i->y, '@');
	mvaddch( i->x, i->y - 1, '-');
	mvaddch( i->x, i->y - 2, '/');
	mvaddch( i->x, i->y + 1, '-');
	mvaddch( i->x, i->y + 2, '\\');
	mvaddch( i->x + 1, i->y + 2, '/');
	mvaddch( i->x + 1, i->y - 2, '\\');
}
void Monster::DrawShip2(const std::vector<Monster>::iterator i)
{
	mvaddch( i->x, i->y, '@');
	mvaddch( i->x, i->y - 1, '-');
	mvaddch( i->x, i->y - 2, '\\');
	mvaddch( i->x, i->y + 1, '-');
	mvaddch( i->x, i->y + 2, '/');
	mvaddch( i->x + 1, i->y + 2, '\\');
	mvaddch( i->x + 1, i->y - 2, '/');
}
void Monster::DrawShip3()
{
	mvaddch( Invader::Boss.x, Invader::Boss.y - 3, '<');
	mvaddch( Invader::Boss.x, Invader::Boss.y + 3, '>');
	mvaddch( Invader::Boss.x, Invader::Boss.y - 2, ACS_LRCORNER);
	mvaddch( Invader::Boss.x, Invader::Boss.y + 2, ACS_LLCORNER);
	mvaddch( Invader::Boss.x, Invader::Boss.y - 1, ACS_NEQUAL);
	mvaddch( Invader::Boss.x, Invader::Boss.y + 1, ACS_NEQUAL);
	mvaddch( Invader::Boss.x, Invader::Boss.y , ACS_PI | A_BOLD);
	mvaddch( Invader::Boss.x + 1, Invader::Boss.y + 1, ACS_BTEE);
	mvaddch( Invader::Boss.x + 1, Invader::Boss.y - 1, ACS_BTEE);
	mvaddch( Invader::Boss.x + 1, Invader::Boss.y + 2, '/');
	mvaddch( Invader::Boss.x + 1, Invader::Boss.y - 2, '\\');
}
