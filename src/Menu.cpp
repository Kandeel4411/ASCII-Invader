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
#include <string>
#pragma comment(lib, "Winmm.lib")

/////////
WINDOW* Menu::win;
int Menu::maxX;
int Menu::maxY;

std::vector <Settings> Menu::settingsLevel;
bool Settings::Boss = 0;
int Settings::score = 0;
int Settings::life = 3;
int Settings::row = 25;
int Settings::col = 100;
/////////

Menu::Menu()
{
	refresh();
	initscr();
	cbreak();
	curs_set(0);
	nodelay(stdscr, true);
	TerminalColour();
	start_color();
	AudioNcolour();

	resize_term(Settings::row,Settings::col);

	/*Menu::win = newwin(40, 40, 10, 10);
	getmaxyx(Menu::win, maxX, maxX);
	nodelay(Menu::win, true);
	box(Menu::win, '|', '_');*/
}

void Menu::MainMenu()
{
	Menu();


	DisplayMenu();
}
void Menu::DisplayMenu()
{

}
void Menu::OptionMenu()
{

}
void Menu::LevelMenu()
{

}
void Menu::TerminalColour()
{
	if (!has_colors())
	{
		clear();
		printw("Terminal doesn't support colour.");
		getch();
		Invader::playing = 0;
	}
}

std::string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

void Menu::AudioNcolour()
{
	std::string enemy_shooting_sound = ExePath()+"\\assets\\shot.mp3";
	std::string player_shooting_sound = ExePath() + "\\assets\\player.mp3";
	std::string intro1_sound = ExePath() + "\\assets\\loop.mp3";
	std::string intro2_sound = ExePath() + "\\assets\\boss_loop.mp3";
	std::string b_death_sound = ExePath() + "\\assets\\boss.mp3";
	std::string enemy_death_sound = ExePath() + "\\assets\\enemy.mp3";
	std::string life_lost_sound = ExePath() + "\\assets\\life.mp3";
	std::string final_sound = ExePath() + "";

	mciSendString(std::string("open \"" + enemy_death_sound + "\" type mpegvideo alias enemy_sound").c_str(), NULL, 0, NULL);
	mciSendString(std::string("open \"" + player_shooting_sound + "\" type mpegvideo alias player_sound").c_str(), NULL, 0, NULL);
	mciSendString(std::string("open \"" + enemy_shooting_sound +"\" type mpegvideo alias shooting_sound").c_str(), NULL, 0, NULL);
	mciSendString(std::string("open \"" + intro1_sound + "\" type mpegvideo alias intro1_sound").c_str(), NULL, 0, NULL);
	mciSendString(std::string("open \"" + intro2_sound + "\" type mpegvideo alias intro2_sound").c_str(), NULL, 0, NULL);
	mciSendString(std::string("open \"" + b_death_sound + "\" type mpegvideo alias b_death_sound").c_str(), NULL, 0, NULL);
	mciSendString(std::string("open \"" + life_lost_sound + "\" type mpegvideo alias life_lost_sound").c_str(), NULL, 0, NULL);
	mciSendString(std::string("open \"" + final_sound + "\" type mpegvideo alias final_sound").c_str(), NULL, 0, NULL);

	init_pair(C_MONSTER, COLOR_GREEN, COLOR_BLACK);
	init_pair(C_MONSTER_FIRE, COLOR_GREEN, COLOR_BLACK);

	init_pair(C_BOSS, COLOR_RED, COLOR_BLACK);
	init_pair(C_BOSS_FIRE, COLOR_YELLOW, COLOR_BLACK);

	init_pair(C_PLAYER, COLOR_RED, COLOR_BLACK);
	init_pair(C_PLAYER_FIRE, COLOR_RED, COLOR_BLACK);

	init_pair(C_INVADER_COUNT, COLOR_YELLOW, COLOR_BLACK);
	init_pair(C_SET_LIFE, COLOR_YELLOW, COLOR_BLACK);

	init_pair(C_PLAYER_LIVE, COLOR_YELLOW, COLOR_BLACK);
	init_pair(C_PLAYER_SCORE, COLOR_YELLOW, COLOR_BLACK);

	init_pair(C_BORDER, COLOR_RED, COLOR_BLACK);

	init_pair(C_STAR1, COLOR_CYAN, COLOR_BLACK);
	init_pair(C_STAR2, COLOR_RED, COLOR_BLACK);
	init_pair(C_STAR3, COLOR_YELLOW, COLOR_BLACK);
}
