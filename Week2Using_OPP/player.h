#ifndef player_H
#define player_H

class Player
{
private:
	int health;
	int expLevel;
	int power;
public:
    Player();

    Player(int h, int exp, int power);

    ~Player();

    int getHealth();

    int getExperienceLevel();

    int getPowerUpLevel();

    void setHealth(int h);

    void setExperienceLevel(int exp);

    void setPowerUpLevel(int power);

    void PrintStats() const;
};

#endif // player_H