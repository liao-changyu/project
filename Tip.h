#pragma once
#include "cocos2d.h"
class Tip :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void replace(cocos2d::Ref* pSender);
	void Close2(cocos2d::Ref* pSender);

	CREATE_FUNC(Tip);

};

