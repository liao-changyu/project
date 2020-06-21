#include "weaPon.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

weaPon::weaPon()
{
	health = 3, bulletNum = 60;
	bulletSpeed = 6; weapon = 0;
}

void weaPon::setSpeed(int speed)
{
	bulletSpeed = speed;
}

void weaPon::attack(cocos2d::Sprite*sp1, cocos2d::Sprite* sp2,
	cocos2d::Sprite* sp3,cocos2d::Sprite* aim1,
	cocos2d::Sprite* aim2, cocos2d::Sprite* aim3)
{
	//锁定怪兽进行攻击
	
	sp1->setPosition(Vec2(aim1->getPositionX() - 10,
		aim1->getPositionY() - 10));
	sp2->setPosition(Vec2(aim2->getPositionX() - 10,
		aim2->getPositionY() - 10));
	sp3->setPosition(Vec2(aim3->getPositionX() - 10,
		aim3->getPositionY() - 10));
	//攻击特效的帧动画
	cocos2d::Vector<SpriteFrame*> animFrames;
	animFrames.reserve(5);
	animFrames.pushBack(SpriteFrame::create("s2.png", Rect(0, 0, 125, 124)));
	animFrames.pushBack(SpriteFrame::create("s3.png", Rect(0, 0, 124, 125)));
	animFrames.pushBack(SpriteFrame::create("s4.png", Rect(0, 0, 124, 125)));
	animFrames.pushBack(SpriteFrame::create("s5.png", Rect(0, 0, 125, 125)));
	animFrames.pushBack(SpriteFrame::create("s6.png", Rect(0, 0, 125, 125)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate1 = Animate::create(animation);
	Animate* animate2 = Animate::create(animation);
	Animate* animate3 = Animate::create(animation);
	sp1->runAction(animate1);
	sp2->runAction(animate2);
	sp3->runAction(animate3);
}

void initHealth(cocos2d::TMXTiledMap* map)
{
	auto blood = Sprite::create("hp1.png");
	map->addChild(blood);
	blood->setPosition(Vec2(10, 800));
}

void weaPon::setBooldStrip()
{
	//if (health == 3)
		////////
}

void weaPon::setweaPon(cocos2d::Sprite* sp)
{
	if (judgeWeapon())
	{
		auto staff = Sprite::create("RocketGun.png");
		staff->setAnchorPoint(Vec2(-0.5, -0.5));
		sp->addChild(staff);
	}
}

bool weaPon::judgeWeapon()
{
	if (weapon == 0)
		return true;
	else
		return false;
}