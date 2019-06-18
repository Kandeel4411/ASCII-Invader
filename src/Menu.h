#pragma once

#include <windows.h>
#include <curses.h>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>   
#include <ctime>
#include <vector>


#ifndef C_MONSTER_FIRE

constexpr auto C_MONSTER_FIRE = 1;
constexpr auto C_MONSTER = 4;

constexpr auto C_PLAYER_FIRE = 2;
constexpr auto C_PLAYER = 5;

constexpr auto C_BOSS_FIRE = 3;
constexpr auto C_BOSS = 6;

constexpr auto C_INVADER_COUNT = 7;
constexpr auto C_PLAYER_LIVE = 8;

constexpr auto C_PLAYER_SCORE = 9;
constexpr auto C_SET_LIFE = 10;

constexpr auto C_BORDER = 11;

constexpr auto C_STAR1 = 12;
constexpr auto C_STAR2 = 13;
constexpr auto C_STAR3 = 14;

#define SLEEP_THREAD std::this_thread::sleep_for(std::chrono::milliseconds(30));
#endif

struct Settings {
	int timeSpawn = 1;
	int setLifeScore;
	int moveBoost;
	int move;
	int shipSpawn;
	static int row, col;
	static int score, life;
	static bool Boss;
	int incScore;
	// 6 over all levels in game implemented , shortcuts for above variables
	int setLs[6] = { 50,75,100,125,150,175 };
	int mvBst[6] = { 3,3,2,2,1,1 };
	int mv[6] = { 1,1,1,1,1,1 };
	int shipS[6] = { 1,1,10,40,30,20 };
	int iScore[6] = { 10,10,10,5,5,5 };

	Settings(int setLevel)
	{
		setLifeScore = setLs[setLevel];
		moveBoost = mvBst[setLevel];
		move = mv[setLevel];
		shipSpawn = shipS[setLevel];
		incScore = iScore[setLevel];
	}

};

class Menu
{

public:

	Menu();
	static WINDOW *win;
	static int maxX, maxY;
	static std::vector <Settings> settingsLevel;


	static void MainMenu();
		static void DisplayMenu();
	static void LevelMenu();
	static void OptionMenu();
	static void TerminalColour();
	static void AudioNcolour();

};

