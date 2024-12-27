#ifndef HEALTHPACK_H
#define HEALTHPACK_H

#include "Entity.h"

class HealthPack : public Entity 
{
public:
	HealthPack() {
		std::cout << "HealthPack created." << std::endl;
	}
	~HealthPack() {}
};

#endif // HEALTHPACK_H
