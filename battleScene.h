#ifndef __GUANQIA__
#define __GUANQIA__ 
#include "cocos2d.h"
#include "monster.h"
class battleScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	cocos2d::Sprite* mainActor;
	cocos2d::Sprite* goblin;
	cocos2d::Sprite* Pig1;
	cocos2d::Sprite* Pig2;
	cocos2d::Sprite* sprite_1;
	cocos2d::Sprite* bullet;
	cocos2d::Sprite* blood;
	cocos2d::Sprite* blood1;
	cocos2d::Sprite* blood2;
	cocos2d::Sprite* blood3;
	cocos2d::Sprite* blood4;
	cocos2d::Sprite* blood5;
	cocos2d::Sprite* blood6;
	monster pig1;
	monster pig2;
	monster flower;
	cocos2d::Sprite* mons[4] = {0};
	int b_pause;

	void setBpause();
	int getBpause();
	void update(float delta) override;
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode code);
	void keyPressedDuration(cocos2d::EventKeyboard::KeyCode code);
	void Close1(Ref* psender);
	void setmap();
	void attack(float dt);
	void running1(float dt);
	void running2(float dt);
	void setPlayerPosition(cocos2d::Point position);
	cocos2d::Point tileCoordFromPosition(cocos2d::Point position);

	CREATE_FUNC(battleScene);
private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys1;
	cocos2d::TMXTiledMap* map1;
	cocos2d::TMXLayer* _collidable1;
};

#endif