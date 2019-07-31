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

	DrawPlayerBullet(first, last);
}

void Player::DrawPlayerBullet(const std::vector<Fire>::iterator first, const std::vector<Fire>::iterator last)
{
	attron(A_BOLD);

	// Set different bullets based on score
	int score = Menu::settingsLevel[Invader::setLevel].score;
	int bulletColor = -1;

	if (score > 500)
		bulletColor = RandInt(0, 3);
	else
		bulletColor = C_PLAYER_FIRE;

	attron(COLOR_PAIR(bulletColor));

	for (auto i = first; i < last; i++)
	{
		if (RandInt(0, 1) == 1)
		{
			if (score > 250)
			{
				mvaddch(i->x + 1, i->y, '|');
				mvaddch(i->x, i->y, ACS_BLOCK);
			}
			else
			{
				mvaddch(i->x + 1, i->y, ' ');
				mvaddch(i->x, i->y, '1');
			}

		}
		else
		{
			if (score > 200)
			{
				mvaddch(i->x + 1, i->y, ' ');
				mvaddch(i->x, i->y, ACS_DIAMOND);
			}
			else
			{
				mvaddch(i->x + 1, i->y, ' ');
				mvaddch(i->x, i->y, '0');
			}
		}
	}

	attroff(A_BOLD);
	attroff(bulletColor);
}

void Player::DrawShip1()
{
	mvaddch( Player::player.x - 1, Player::player.y, '^');
	mvaddch( Player::player.x, Player::player.y, ACS_LANTERN);
	mvaddch( Player::player.x, Player::player.y - 1, '<');
	mvaddch( Player::player.x, Player::player.y + 1, '>');
}
