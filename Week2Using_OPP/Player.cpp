#include "player.h"
#include <iostream>

using namespace std;

Player::Player(int h, int exp, int power) : health(h), expLevel(exp), power(power) {}

Player::Player() 
{  
    std::cout << "A Player object was created!" << std::endl;
}

Player::~Player()
{
    std::cout << "A Player object was destroyed!" << std::endl;
}

int Player::getHealth() {
    cout << "Please input the health point" << endl;
    cin >> health;
    return health;
}

int Player::getExperienceLevel() {
    cout << "Please input the Experience Level:" << endl;
    cin >> expLevel;
    return expLevel;
}

int Player::getPowerUpLevel() {
    cout << "Please input the power level" << endl;
    cin >> power;
    return power;
}

void Player::setHealth(int h) {
    health = h;
}

void Player::setExperienceLevel(int exp) {
    expLevel = exp;
}

void Player::setPowerUpLevel(int powL) {
    power = powL;
}

void Player::PrintStats() const
{
    std::cout << "Health:" << health << endl;
    std::cout << "Experience Level:" << expLevel << endl;
    std::cout << "PowerLevel:" << power << endl;

}