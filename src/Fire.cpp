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


void Fire::PlayerFireMove(const std::vector<Fire>::iterator first, const std::vector<Fire>::iterator last)
{
	for (auto i = first; i < last; ++i)
		i->x--;
}
void Fire::MonsterFireMove(const std::vector<Fire>::iterator first, const std::vector<Fire>::iterator last)
{
	for (auto i = first; i < last; ++i)
		i->x++;
}

void Fire::DrawFire1(const std::vector<Fire>::iterator i)
{
	mvaddch( i->x - 1, i->y, '|');
	mvaddch( i->x, i ->y, ACS_BLOCK);

}
void Fire::DrawFire2(const std::vector<Fire>::iterator i)
{
	mvaddch( i->x - 1, i->y, ' ');
	mvaddch( i->x, i->y, ACS_DARROW);
 }
void Fire::DrawFire3(const std::vector<Fire>::iterator i)
{
	mvaddch( i->x, i->y, ACS_DIAMOND);
}

void Fire::DrawFire4(const std::vector<Fire>::iterator i)
{
	mvaddch( i->x - 1, i->y, '|');
	mvaddch( i->x, i->y, '*');
}
