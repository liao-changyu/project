#include "monster.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

monster::monster()
{
	Health = 3, bulletNum = 60;
	bulletSpeed = 6; monsterNum = 5;
	mons_Pig = 0; mons_Gun = 1;
}

void monster::setSpeed(int speed)
{
	bulletSpeed = speed;
}

void monster::attack(int mons)
{

}

void monster::setHealth(int health)
{
	Health = health;
}


void monster::randomMove(cocos2d::Sprite* sp,int mons)
{
	if (!judgeMonster(mons))
	{
		while (Health!=0)
		{
			auto moveTo1 = MoveTo::create(0.5, Vec2(sp->getPositionX() + 50,
				sp->getPositionY()));
			sp->runAction(moveTo1);
			auto moveTo2 = MoveTo::create(0.5, Vec2(sp->getPositionX() ,
				sp->getPositionY()-50));
			sp->runAction(moveTo1);
			auto moveTo3 = MoveTo::create(0.5, Vec2(sp->getPositionX() - 50,
				sp->getPositionY()));
			sp->runAction(moveTo1);
			auto moveTo4 = MoveTo::create(0.5, Vec2(sp->getPositionX() ,
				sp->getPositionY()+50));
			sp->runAction(moveTo1);
		}
	}
}

bool monster::judgeMonster(int mons)
{
	if (mons == 1)
		return true;
	else
		return false;
}

void monster::setmonsNum(int num)
{
	monsterNum = num;
}

int monster::getmonsNum()
{
	return monsterNum;
}

int monster::getHealth()
{
	return Health;
}