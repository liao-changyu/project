#pragma once
#include "cocos2d.h"
class weaPon :public cocos2d::Scene
{
private:
	int monsterNum;
	int health;
	int weapon;
	int bulletNum;
	int bulletSpeed;
public:
	weaPon();
	void setSpeed(int speed);
	void initHealth(cocos2d::TMXTiledMap* map);
	void setHealth(int health);
	void attack(cocos2d::Sprite* sp1, cocos2d::Sprite* sp2,
		cocos2d::Sprite* sp3, cocos2d::Sprite* aim1,
		cocos2d::Sprite* aim2, cocos2d::Sprite* aim3);
	void setBooldStrip();
	void setweaPon(cocos2d::Sprite* sp);
	bool judgeWeapon();
};

