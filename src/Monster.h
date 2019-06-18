#pragma once
#include <windows.h>
#include <curses.h>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>   
#include <ctime>
#include <vector>

class Monster {

public:

	int x;
	int y;
    bool check = 0;
    int bossHP = 5;
	static bool turn;

public:

	Monster(const int set_x, const int set_y)
	{
		x = set_x;
		y = set_y;
	}
	Monster(const int set_x, const int set_y,const int hp)
	{
		x = set_x;
		y = set_y;
		bossHP = hp;
	}
	Monster()
	{
		x = 0;
		y = 0;
	}
	static void MonsterMove(const std::vector<Monster>::iterator first, const std::vector<Monster>::iterator last);
	static void DrawMonster(const std::vector<Monster>::iterator first, const std::vector<Monster>::iterator last, const std::vector<Fire>::iterator first2, const std::vector<Fire>::iterator last2);

	static void BossMove();
	static void DrawBoss(const std::vector<Fire>::iterator first, const std::vector<Fire>::iterator last);

	static void DrawShip1(const std::vector<Monster>::iterator i);
	static void DrawShip2(const std::vector<Monster>::iterator i);
	static void DrawShip3();
};
