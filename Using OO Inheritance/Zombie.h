#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__
#include "enemy.h"
#include <iostream>

using namespace std;

class Zombie : public Enemy
{
public:
	Zombie() 
	{
		cout << "Constructor called on object at: " << this << " (Zombie)." << endl;
	}
	~Zombie()
	{
		cout << "Destructor called on object at: " << this << " (Zombie)." << endl;
	}

	void MakeNoise();
};

#endif // __ZOMBIE_H__