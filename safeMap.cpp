#include "safeMap.h"
#include "SimpleAudioEngine.h"
#include "weaPon.h"
#include "monster.h"
#include "battleScene1.h"
#include "Tip.h"
USING_NS_CC;

//创建一个场景
Scene* safeMap::createScene()
{
	return safeMap::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//场景的初始化
bool safeMap::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//调用cocos中包含的调度器
	this->scheduleUpdate();
	//调用导演类
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//创建主角
	mainActor3 = Sprite::create("z1.png");
	if (mainActor3 == nullptr)
	{
		problemLoading("'z1.png'");
	}
	mainActor3->setAnchorPoint(Vec2(0.5, 0.5));
	//创造主角的帧动画
	cocos2d::Vector<SpriteFrame*> animFrames;
	animFrames.reserve(3);
	animFrames.pushBack(SpriteFrame::create("z2.png", Rect(0, 0, 85, 90)));
	animFrames.pushBack(SpriteFrame::create("z3.png", Rect(0, 0, 85, 90)));
	animFrames.pushBack(SpriteFrame::create("z4.png", Rect(0, 0, 85, 90)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	mainActor3->runAction(RepeatForever::create(animate));

	//加载瓦片地图
	map2 = TMXTiledMap::create("safemap.tmx");
	addChild(map2, 1);
	map2->setAnchorPoint(Vec2(0, 0));
	map2->setPosition(0, 0);
	map2->addChild(mainActor3, 2);


	//创建关闭键
	auto closeItem = MenuItemImage::create(
		"Close.png",
		"Close.png",
		CC_CALLBACK_1(safeMap::Close, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'Close.png' and 'Close.png'");
	}
	else
	{
		closeItem->setPosition(Vec2(970, 530));
	}
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setColor(Color3B::WHITE);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	//加载瓦片地图对象层中对象的位置信息
	TMXObjectGroup* ob1 = map2->getObjectGroup("object1");
	ValueMap val = ob1->getObject("sp1");

	//瓦片地图中的坐标转换为cocos坐标
	float x = val["x"].asFloat();
	float y = val["y"].asFloat();
	//将主角加入到cocos地图中
	mainActor3->setPosition(Vec2(x, y));

	//添加法杖
	ValueMap val2 = ob1->getObject("staff");
	float x1 = val2["x"].asFloat();
	float y1 = val2["y"].asFloat();
	 lightStaff = Sprite::create("light.png");
	map2->addChild(lightStaff);
	lightStaff->setPosition(Vec2(x1, y1));

	//设置障碍物的不可见属性
	_collidable2 = map2->getLayer("collide");
	_collidable2->setVisible(false);

	
	


	//设置cocos地图跟随主角视角移动
	Point orig = Point(mainActor3->getPositionX(), mainActor3->getPositionY());
	Point dest = Point(visibleSize.width / 2, visibleSize.height / 2);
	Point distance = dest - orig;
	Point newMapPos = Point(0, 0) + distance;
	newMapPos.x = (newMapPos.x > 0 ? 0 : newMapPos.x);
	newMapPos.y = (newMapPos.y > 0 ? 0 : newMapPos.y);
	newMapPos.x = (newMapPos.x < -visibleSize.width ?
		-visibleSize.width : newMapPos.x);
	newMapPos.y = (newMapPos.y < -visibleSize.height ?
		-visibleSize.height : newMapPos.y);
	map2->setPosition(newMapPos);

	//创建键盘事件监听器
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event) {
		keys2[code] = true;
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {
		keys2[code] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

//判断键盘是否被按下
bool safeMap::isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {
	if (keys2[code]) {
		return true;
	}
	else return false;
}

//键盘按下时进行的操作
void safeMap::keyPressedDuration(cocos2d::EventKeyboard::KeyCode code) {
	int setX = 0, setY = 0;
	switch (code) {
		//上下左右移动时的操作
	case EventKeyboard::KeyCode::KEY_W:setY = 5;
		break;
	case EventKeyboard::KeyCode::KEY_S:setY = -5;
		break;
	case EventKeyboard::KeyCode::KEY_A:setX = -5;
		break;
	case EventKeyboard::KeyCode::KEY_D:setX = 5;
		break;
	case EventKeyboard::KeyCode::KEY_K:
	{
		map2->removeChild(lightStaff);
		lightStaff = Sprite :: create("light.png");
		mainActor3->addChild(lightStaff);
		lightStaff->setAnchorPoint(Vec2(-0.5, -0.5));
		lightStaff->setPosition(Vec2(10, 6));
	}
		break;
	case EventKeyboard::KeyCode::KEY_G:
	{
		auto transp = battleScene1::createScene();
		TransitionCrossFade* trs = TransitionCrossFade::create(1.0, transp);
		Director::getInstance()->replaceScene(trs);
	}
	break;
	default:
		setX = setY = 0;
		break;
	}
	int dest_X = mainActor3->getPositionX() + setX;
	int dest_Y = mainActor3->getPositionY() + setY;
	Point pos = Point(dest_X, dest_Y);

	//设置地图跟随主角视角移动
	setPlayerPosition(pos);
}

//调度器调用的Update函数
void safeMap::update(float delta) {
	Node::update(delta);
	auto up = EventKeyboard::KeyCode::KEY_W;
	auto down = EventKeyboard::KeyCode::KEY_S;
	auto right = EventKeyboard::KeyCode::KEY_A;
	auto left = EventKeyboard::KeyCode::KEY_D;
	auto pick = EventKeyboard::KeyCode::KEY_K;
	auto trans= EventKeyboard::KeyCode::KEY_G;
	if (isKeyPressed(up)) {
		keyPressedDuration(up);
	}
	else if (isKeyPressed(down)) {
		keyPressedDuration(down);
	}
	else if (isKeyPressed(right)) {
		keyPressedDuration(right);
	}
	else if (isKeyPressed(left)) {
		keyPressedDuration(left);
	}
	else if (isKeyPressed(pick)) {
		keyPressedDuration(pick);
	}
	else if (isKeyPressed(trans)) {
		keyPressedDuration(trans);
	}
	setmap();
}

//地图滚动函数
void safeMap::setmap()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Point orig = Point(mainActor3->getPositionX(), mainActor3->getPositionY());
	Point dest = Point(visibleSize.width / 2, visibleSize.height / 2);
	Point distance = dest - orig;
	Point newMapPos = Point(0, 0) + distance;
	newMapPos.x = (newMapPos.x > 0 ? 0 : newMapPos.x);
	newMapPos.y = (newMapPos.y > 0 ? 0 : newMapPos.y);
	newMapPos.x = (newMapPos.x < visibleSize.width - 960 ?
		visibleSize.width - 960 : newMapPos.x);
	newMapPos.y = (newMapPos.y < visibleSize.height - 960 ?
		visibleSize.height - 960 : newMapPos.y);
	map2->setPosition(newMapPos);
}

void safeMap::setPlayerPosition(Point position)
{
	//从像素点坐标转化为瓦片坐标 
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//获得瓦片的GID  
	Point tileCoord = this->tileCoordFromPosition(position);
	int tileGid = _collidable2->getTileGIDAt(tileCoord);

	//检测瓦片是否具有碰撞属性
	if (tileGid > 0) {

		Value prop = map2->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		std::string collision = propValueMap["Collidable"].asString();

		//碰撞检测成功 
		if (collision == "true")
		{
			int tempX = mainActor3->getPositionX();
			int tempY = mainActor3->getPositionY();

			//撞到障碍物后主角会被弹开
			if (tempX < visibleSize.width / 2 && tempY < visibleSize.height / 2)
			{
				auto moveTo = MoveTo::create(0.1, Vec2(tempX + 6, tempY + 6));
				mainActor3->runAction(moveTo);
				return;
			}
			else if (tempX < visibleSize.width / 2 && tempY > visibleSize.height / 2)
			{
				auto moveTo = MoveTo::create(0.1, Vec2(tempX + 6, tempY - 6));
				mainActor3->runAction(moveTo);
				return;
			}
			else if (tempX > visibleSize.width / 2 && tempY > visibleSize.height / 2)
			{
				auto moveTo = MoveTo::create(0.1, Vec2(tempX - 6, tempY - 6));
				mainActor3->runAction(moveTo);
				return;
			}
			else if (tempX > visibleSize.width / 2 && tempY < visibleSize.height / 2)
			{
				auto moveTo = MoveTo::create(0.1, Vec2(tempX - 6, tempY + 6));
				mainActor3->runAction(moveTo);
				return;
			}

		}
	}
	auto moveTo = MoveTo::create(0.3, Vec2(position.x, position.y));
	mainActor3->runAction(moveTo);

}

Point safeMap::tileCoordFromPosition(Point pos)
{
	int x = pos.x / map2->getTileSize().width;
	int y = ((map2->getMapSize().height * map2->getTileSize().height) - pos.y) /
		map2->getTileSize().height;
	return Point(x, y);
}

void safeMap::Close(Ref* pSender)
{
	Director::getInstance()->end();
}

void safeMap::setPause()
{
	s_pause = 1;
}

int safeMap::getPause()
{
	return s_pause;
}