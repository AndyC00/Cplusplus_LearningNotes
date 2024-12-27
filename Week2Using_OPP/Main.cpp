#include "player.h"
#include <iostream>

using namespace std;

int main()
{
	Player testPlayer(560, 100, 5);

	testPlayer.PrintStats();

	testPlayer.setExperienceLevel(1000);
	testPlayer.setHealth(780);
	testPlayer.setPowerUpLevel(10);
	testPlayer.PrintStats();

	testPlayer.getHealth();
	testPlayer.getExperienceLevel();
	testPlayer.getPowerUpLevel();
	testPlayer.PrintStats();

	Player* pPlayer = nullptr;
	pPlayer = new Player();

	pPlayer->PrintStats();

	delete pPlayer;
	pPlayer = nullptr;

	return 0;
}