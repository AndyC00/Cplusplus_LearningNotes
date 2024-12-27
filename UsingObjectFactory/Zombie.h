#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Entity.h"

class Zombie : public Entity 
{
public:
	Zombie(int i) {
		std::cout << "Zombie created." << std::endl;
		std::cout << i << std::endl;
	}
	Zombie() {
		std::cout << "Zombie created." << std::endl;
	}
	~Zombie() {
		std::cout << "Zombie, deleted!" << std::endl;
	}
};

#endif // ZOMBIE_H#pragma once
