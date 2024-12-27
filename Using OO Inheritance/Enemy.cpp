#include "enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy() 
{
	m_x = 0;
	m_y = 0;
	cout << "Constructor called on object at: " << this << " (Enemy)." << endl;
}

Enemy::~Enemy()
{
	cout << "Destructor called on object at: " << this << " (Enemy)." << endl;
}

 void Enemy::MakeNoise() const
{
	 //print out the address of the object
	 cout << "Enemy [" << this << "] makes generic noise." << endl;
}