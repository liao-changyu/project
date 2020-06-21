
#ifndef __nHELLOWORLD_SCENE_H__
#define __nHELLOWORLD_SCENE_H__ 

#include "cocos2d.h"
class battleScene1 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	cocos2d::Sprite *mainActor2;
	cocos2d::Sprite* flower;
	cocos2d::Sprite* pig1;
	cocos2d::Sprite* pig2;
	cocos2d::Sprite* staff_1;
	cocos2d::Sprite* bullet;
	cocos2d::Sprite* blood;
	cocos2d::Sprite* blood1;
	cocos2d::Sprite* blood2;
	cocos2d::Sprite* blood3;
	cocos2d::Sprite* blood4;
	cocos2d::Sprite* blood5;
	cocos2d::Sprite* blood6;
	int b1_pause;

	void setB1pause();
	int getB1pause();
	void update(float delta) override;
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode code);
	void keyPressedDuration(cocos2d::EventKeyboard::KeyCode code);
	void setmap();
	void Close2(Ref* psender);
	void attack_1(float dt);
	void running1_1(float dt);
	void running2_1(float dt);
	void setPlayerPosition(cocos2d::Point position);                                
	cocos2d::Point tileCoordFromPosition(cocos2d::Point position);
	void menuCloseCallback(Ref* pSender);
	CREATE_FUNC(battleScene1);
private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	cocos2d::TMXTiledMap* map;
	cocos2d::TMXLayer* _collidable;
};

#endif// __nHELLOWORLD_SCENE_H__
