#pragma once

#include <array>
#include <curses.h>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>   
#include <ctime>
#include <vector>

static int RandInt(int low, int high)
{
	static std::default_random_engine re{};
	using Dist = std::uniform_int_distribution<int>;
	static Dist uid{};
	return uid(re, Dist::param_type{ low,high });
}


class Invader
{
private:

	int  randY = 0;
	int maxY = 0, maxX = 0;
	int  borderX = 0;
	char ch = '1';
	int prevLife = 0;
	int prevInvader = 0;

	clock_t bossWait;
    clock_t endWait;

	std::vector <Fire> firePlayer;
	std::vector <Fire> fireMonster;
	std::vector <Fire> fireBoss;
	std::vector <Monster> monsterShip;

public:

	static int setLevel;
	static Monster Boss;
	static	int  borderY;
	static bool playing;

	bool bossDeath = 0;
	bool bossCreated = 0;
	
public:

	Invader(); // Window initialize

	void SetupLevel(); // Sets variables and starting functions.
	void InputWindow(); // Input checks.
	void Logic(); // Main Game Logic, Contains all Logic Functions
		void MonsterLogic();    
		void GeneralLogic(); 
		void CollisionLogic();
			void CollisionFireMonster();
			void CollisionFireBoss();
			void CollisionFirePlayer();
			void CollisionMonsterShip();
		void MovementLogic();
	void DisplayWindow(); // Game display prints.
	void CreateAlien(); // Randomize spawn monster.
	void CreateBoss();

};

