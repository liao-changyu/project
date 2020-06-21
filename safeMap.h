#ifndef __SAFEMAP__
#define __SAFEMAP__ 
#include "cocos2d.h"
class safeMap :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	cocos2d::Sprite* lightStaff;
	cocos2d::Sprite* mainActor3;
	int s_pause;

	void setPause();
	int getPause();
	void Close(Ref* pSender);
	void update(float delta) override;
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode code);
	void keyPressedDuration(cocos2d::EventKeyboard::KeyCode code);
	void setmap();
	void setPlayerPosition(cocos2d::Point position);
	cocos2d::Point tileCoordFromPosition(cocos2d::Point position);

	CREATE_FUNC(safeMap);
private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys2;
	cocos2d::TMXTiledMap* map2;
	cocos2d::TMXLayer* _collidable2;
};
#endif
