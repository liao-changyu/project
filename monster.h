#pragma once
#include "cocos2d.h"
class monster :public cocos2d::Scene
{
private:
	int monsterNum;
	int Health;
	int bulletNum;
	int bulletSpeed;
	int mons_Pig;
	int mons_Gun;
public:
	monster();
	void setSpeed(int speed);
	void setHealth(int health);
	int getHealth();
	void attack(int mons);
	void randomMove(cocos2d::Sprite* sp,int mons);
	bool judgeMonster(int mons);
	void setmonsNum(int num);
	int getmonsNum();
};

