#include <iostream>
#include "Entity.h"
#include "Zombie.h"
#include "HealthPack.h"
#include "AmmoPack.h"

using namespace std;

enum EntityType
{
	ZOMBIE, HEALTHPACK, AMMOPACK
};

Entity* CreateEntity(EntityType entityType);

int main()
{
    Entity* ptr1 = CreateEntity(EntityType(0));
    Entity* ptr2 = CreateEntity(EntityType(1));
    Entity* ptr3 = CreateEntity(EntityType(2));

    Entity* functions[3] = {ptr1, ptr2, ptr3};

    for (int i = 0; i < 3; i++)
    {
        cout << functions[i] << endl;
        delete functions[i];
        functions[i] = nullptr;
    }

    cout << "ptr1: " << functions[0] << endl;

    cout << "ptr1: " << ptr1 << endl;


	return 0;
}

Entity* CreateEntity(EntityType entityType)
{
    switch (entityType) 
    {
    case 0:
        return new Zombie;
    case 1:
        return new HealthPack();
    case 2:
        return new AmmoPack();
    default:
        return nullptr;
    }
}