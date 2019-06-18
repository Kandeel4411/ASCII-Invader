#include "Menu.h"
#include "Fire.h"
#include "Monster.h"
#include "Player.h"
#include "Invader.h"
#include <limits>


int main()
{
	Invader game;

	game.SetupLevel();
	while (game.playing)
	{
		game.InputWindow();
		game.Logic();
		game.DisplayWindow();
		SLEEP_THREAD;
	}

	echo();
	nocbreak();
	endwin();

	mciSendString("close intro1_sound", NULL, 0, NULL);
	mciSendString("close intro2_sound", NULL, 0, NULL);
	mciSendString("close shooting_sound", NULL, 0, NULL);
	mciSendString("close b_death_sound", NULL, 0, NULL);

	if (Invader::setLevel != 6)
	{
		std::cout << "\t\t GAME OVER --- YOU LOST\n";
	}
	else
	{
		std::cout << "W.O.W! Congratulations!! You finally did it! Who would have thought after all these tries!\n\n";
	}

	std::cin.clear();
	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	std::cin.get();
	return 0;
}	