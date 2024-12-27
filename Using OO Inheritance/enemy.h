#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__
class Enemy
{
public:
	Enemy();
	~Enemy();
	void MakeNoise() const;

protected:
	int m_x;
	int m_y;

private:
	Enemy(const Enemy& other);

};
#endif // __ENEMY_H_ce
