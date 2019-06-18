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

Player Player::player;

void Player::DrawPlayer(const std::vector<Fire>::iterator first, const std::vector<Fire>::iterator last)
{
	attron(COLOR_PAIR(C_PLAYER));
	DrawShip1();
	attroff(COLOR_PAIR(C_PLAYER));

	attron(A_BOLD);
	attron(COLOR_PAIR(C_PLAYER_FIRE));
	for (auto i = first; i < last; i++)
	{
		if (RandInt(0, 1) == 1)
		{

			mvaddch(i->x + 1, i->y, '|');
			mvaddch(i->x, i->y, ACS_BLOCK);
		}
		else
		{
			mvaddch(i->x + 1, i->y, ' ');
			mvaddch(i->x, i->y, ACS_DIAMOND);
		}
	}
	attroff(A_BOLD);
	attroff(COLOR_PAIR(C_PLAYER_FIRE));
}

void Player::DrawShip1()
{
	mvaddch( Player::player.x - 1, Player::player.y, '^');
	mvaddch( Player::player.x, Player::player.y, ACS_LANTERN);
	mvaddch( Player::player.x, Player::player.y - 1, '<');
	mvaddch( Player::player.x, Player::player.y + 1, '>');
}
