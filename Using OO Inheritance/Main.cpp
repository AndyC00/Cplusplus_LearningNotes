#include <iostream>
#include <array>
#include "enemy.h"
#include "Zombie.h"

using namespace std;

int main()
{
	cout << "STARTING PROGRAM" << endl;

	constexpr int size = 8;
	array <Enemy*, size> basicContainer = {nullptr};

	for (int i = 0; i < size; i++)
	{
		basicContainer[i] = new Enemy();
	}

	for (int i = 0; i < size; ++i) 
	{
		basicContainer[i]->MakeNoise();
	}

	cout << "sizeof(Enemy) is: " << sizeof(Enemy) << endl;

	for (int i = 0; i < size; ++i) 
	{
		delete basicContainer[i];
	}

	for (int i = 0; i < size - 5; i++)
	{
		basicContainer[i] = new Zombie();
	}

	return 0;
}