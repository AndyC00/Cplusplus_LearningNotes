#ifndef AMMOPACK_H
#define AMMOPACK_H

#include "Entity.h"

class AmmoPack : public Entity 
{
public:
	AmmoPack() {
		std::cout << "AmmoPack created." << std::endl;
	}
	~AmmoPack() {}
};

#endif // AMMOPACK_H