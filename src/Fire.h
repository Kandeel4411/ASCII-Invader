#pragma once
#include <windows.h>
#include <curses.h>
#include <chrono>
#include <iostream>
#include <random>

#include <thread>   
#include <ctime>
#include <vector>



class Fire {

public:

	int x;
	int y;
	Fire(const int set_x, const int set_y)
	{
		x = set_x;
		y = set_y;
	}
	Fire()
	{
		x = 0;
		y = 0;
	}
	static void PlayerFireMove(const std::vector<Fire>::iterator first, const std::vector<Fire>::iterator last);
	static void MonsterFireMove(const std::vector<Fire>::iterator first, const std::vector<Fire>::iterator last);

	static void DrawFire1(const std::vector<Fire>::iterator i);
	static void DrawFire2(const std::vector<Fire>::iterator i);
	static void DrawFire3(const std::vector<Fire>::iterator i);
	static void DrawFire4(const std::vector<Fire>::iterator i);


};
