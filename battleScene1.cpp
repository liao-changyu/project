#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "battleScene1.h"
#include "battleScene.h"
#include "ui/CocosGUI.h"
#include "weaPon.h"
#include "monster.h"
#include "Tip.h"
#include "safeMap.h"
USING_NS_CC;

static int Num_1= 3;
static int Damage1 = 0;
static int judgepig2_1 = 1;
static int Hp = 30;
//创建一个场景
Scene* battleScene1::createScene()
{
	return battleScene1::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//场景的初始化
bool battleScene1::init()
{
	do {
		CC_BREAK_IF(!Scene::init());
		//每隔0.2S调用一次发射子弹函数
		if (judgepig2_1 == 1)
		{
			this->schedule(schedule_selector(battleScene1::attack_1), 1.0f);
			this->schedule(schedule_selector(battleScene1::running1_1), 1.5f);
			this->schedule(schedule_selector(battleScene1::running2_1), 2.0f);
		}

	} while (0);
	//调用cocos中包含的调度器
	this->scheduleUpdate();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建关闭键
	auto closeItem = MenuItemImage::create(
		"Close.png",
		"Close.png",
		CC_CALLBACK_1(battleScene1::Close2, this));

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
	this->addChild(menu, 3);

	//创建主角
	 mainActor2 = Sprite::create("z1.png");
	if (mainActor2 == nullptr)
	{
		problemLoading("'z1.png'");
	}
	mainActor2->setAnchorPoint(Vec2(0.5,0.5));
	auto lightStaff = Sprite::create("light.png");
	mainActor2->addChild(lightStaff);
	lightStaff->setAnchorPoint(Vec2(-0.5, -0.5));
	lightStaff->setPosition(Vec2(10, 6));
	//创造主角的帧动画
	cocos2d::Vector<SpriteFrame*> animFrames;
	animFrames.reserve(3);
	animFrames.pushBack(SpriteFrame::create("z2.png", Rect(0, 0, 85, 90)));
	animFrames.pushBack(SpriteFrame::create("z3.png", Rect(0, 0, 85, 90)));
	animFrames.pushBack(SpriteFrame::create("z4.png", Rect(0, 0, 85, 90)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	mainActor2->runAction(RepeatForever::create(animate));


	//加载瓦片地图
	map = TMXTiledMap::create("battle2.tmx");
	addChild(map, 1); 
	map->setAnchorPoint(Vec2(0,0));
	map->setPosition(0, 0);
	map->addChild(mainActor2, 2);

	//加载瓦片地图对象层中对象的位置信息
	TMXObjectGroup* ob1 = map->getObjectGroup("sprite2");
	ValueMap val = ob1->getObject("sp1");

	//瓦片地图中的坐标转换为cocos坐标
	float x = val["x"].asFloat();
	float y = val["y"].asFloat();
	//将主角加入到cocos地图中
	mainActor2->setPosition(Vec2(x,y));

	//设置障碍物的不可见属性
	_collidable = map->getLayer("collide");                                  
	_collidable->setVisible(false);

	//初始化血条
	blood = Sprite::create("blood6.png");
	blood1 = Sprite::create("blood5.png");
	blood2 = Sprite::create("blood4.png");
	blood3 = Sprite::create("blood3.png");
	blood4 = Sprite::create("blood2.png");
	blood5 = Sprite::create("blood1.png");
	blood6 = Sprite::create("blood0.png");
	mainActor2->addChild(blood);

	mainActor2->addChild(blood1);
	mainActor2->addChild(blood2);
	mainActor2->addChild(blood3);
	mainActor2->addChild(blood4);
	mainActor2->addChild(blood5);
	mainActor2->addChild(blood6);

	blood->setScale(0.6);
	blood->setPosition(Vec2(-30, 100));
	blood1->setPosition(Vec2(-1000, 100));
	blood2->setPosition(Vec2(-1000, 100));
	blood3->setPosition(Vec2(-1000, 100));
	blood4->setPosition(Vec2(-1000, 100));
	blood5->setPosition(Vec2(-1000, 100));
	blood6->setPosition(Vec2(-1000, 100));



	ValueMap val2 = ob1->getObject("mons1");
	float x1 = val2["x"].asFloat();
	float y1 = val2["y"].asFloat();
	flower = Sprite::create("flower.png");
	if (flower == nullptr)
	{
		problemLoading("'flower.png'");
	}
	map->addChild(flower, 1);
	//调整花的大小
	flower->setScale(1.2);
	flower->setPosition(Vec2(x1, y1));

	//加载野猪怪
	ValueMap val3 = ob1->getObject("mons2");
	float x2 = val3["x"].asFloat();
	float y2 = val3["y"].asFloat();

	pig1 = Sprite::create("Runningpig.png");
	if (pig1 == nullptr)
	{
		problemLoading("'Runningpig.png'");
	}
	map->addChild(pig1, 1);
	pig1->setScale(1.2);
	pig1->setPosition(Vec2(x2, y2));

	//加载另一个野猪怪
	ValueMap val4 = ob1->getObject("mons3");
	float x3 = val4["x"].asFloat();
	float y3 = val4["y"].asFloat();

	pig2 = Sprite::create("Crab.png");
	if (pig2== nullptr)
	{
		problemLoading("'Crab.png'");
	}
	map->addChild(pig2, 1);
	pig2->setScale(1.2);
	pig2->setPosition(Vec2(x3, y3));
	//将怪兽放入Vector

		
	//设置cocos地图跟随主角视角移动
	Point orig = Point(mainActor2->getPositionX(), 
		mainActor2->getPositionY());
	Point dest = Point(visibleSize.width / 2, visibleSize.height / 2);
	Point distance = dest - orig;
	Point newMapPos = Point(0, 0) + distance;
	newMapPos.x = (newMapPos.x > 0 ? 0 : newMapPos.x);
	newMapPos.y = (newMapPos.y > 0 ? 0 : newMapPos.y);
	newMapPos.x = (newMapPos.x < -visibleSize.width ? 
		-visibleSize.width  : newMapPos.x);
	newMapPos.y = (newMapPos.y < -visibleSize.height  ? 
		-visibleSize.height : newMapPos.y);
	map->setPosition(newMapPos);

	//创建键盘事件监听器
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event) {
		keys[code] = true;
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {
		keys[code] = false;
	};
_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void battleScene1::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

//判断键盘是否被按下
bool battleScene1::isKeyPressed(cocos2d::EventKeyboard::KeyCode code){
	if (keys[code]) {
			return true;		
	}
	else return false;
}

//键盘按下时进行的操作
void battleScene1::keyPressedDuration(cocos2d::EventKeyboard::KeyCode code) {
	int setX=0, setY=0;
	//添加一个攻击特效
	staff_1 = Sprite::create("s1.png");
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
		//攻击的操作

	case EventKeyboard::KeyCode::KEY_J:
	{
		if (Num_1 > 0)
		{
			if (judgepig2_1 == 1)
			{
				Hp--;
				if (Hp > 0)
				{
					map->addChild(staff_1, 1);
					//调用武器类中的攻击函数
					weaPon staff;
					staff.attack(staff_1, staff_1, staff_1,
						flower, pig1, pig2);
				}

				else
				{
					judgepig2_1 = 0;
					Num_1 = 0;
					auto deadpig = Sprite::create("DeadPig.png");
					map->addChild(deadpig);
					deadpig->setPosition(Vec2(pig1->getPositionX(),
						flower->getPositionY()));
					pig2->setScale(0.01);
					auto DeadCrab = Sprite::create("DeadCrab.png");
					map->addChild(DeadCrab);
					DeadCrab->setPosition(Vec2(pig2->getPositionX(),
						pig2->getPositionX()));
					pig1->setScale(0.01);

					auto deadflower = Sprite::create("DeadFlower.png");
					map->addChild(deadflower);
					deadflower->setPosition(Vec2(flower->getPositionX(),
						flower->getPositionY()));
					flower->setPosition(Vec2(-1000, -800));

					auto blood_resume = Sprite::create("blood_resume.png");
					map->addChild(blood_resume);
					blood_resume->setPosition(Vec2(512,500));

					auto RocketGun = Sprite::create("RocketGun.png");
					map->addChild(RocketGun);
					RocketGun->setPosition(Vec2(500, 600));

					if (Num_1 == 0)
					{
						auto visibleSize = Director::getInstance()->getVisibleSize();
						Vec2 origin = Director::getInstance()->getVisibleOrigin();
						auto label = Label::createWithTTF("Press G To Continue", "fonts/Marker Felt.ttf", 36);
						if (label == nullptr)
						{
							problemLoading("'fonts/Marker Felt.ttf'");
						}
						else
						{
							// position the label on the center of the screen
							label->setColor(Color3B::WHITE);
							label->setPosition(Vec2(visibleSize.width / 2,
								visibleSize.height / 2));

							// add the label as a child to this layer
							map->addChild(label, 1);
						}
					}
				}

			}
		}
	}
	break;
		//关卡的转换
	case EventKeyboard::KeyCode::KEY_G:
	{
		auto transp= battleScene::createScene();
		TransitionCrossFade* trs = TransitionCrossFade::create(1.0, transp);
		Director::getInstance()->replaceScene(trs);
	}
		break;
	case EventKeyboard::KeyCode::KEY_F:
	{
		auto transp = safeMap::createScene();
		TransitionCrossFade* trs = TransitionCrossFade::create(1.0, transp);
		Director::getInstance()->replaceScene(trs);
	}
	break;
	default:
		setX = setY = 0;
		break;
	}
	int dest_X = mainActor2->getPositionX() + setX;
	int dest_Y = mainActor2->getPositionY() + setY;
	Point pos = Point(dest_X, dest_Y);

	//设置地图跟随主角视角移动
	setPlayerPosition(pos);
}

//调度器调用的Update函数
void battleScene1::update(float delta) {
	Node::update(delta);
	auto up = EventKeyboard::KeyCode::KEY_W;
	auto down = EventKeyboard::KeyCode::KEY_S;
	auto right = EventKeyboard::KeyCode::KEY_A;
	auto left  = EventKeyboard::KeyCode::KEY_D;
	auto trans =  EventKeyboard::KeyCode::KEY_G;
	auto attack = EventKeyboard::KeyCode::KEY_J;
	auto return_safe = EventKeyboard::KeyCode::KEY_F;
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
	else if (isKeyPressed(trans)) {
		keyPressedDuration(trans);
	}
	else if (isKeyPressed(attack)) {
		keyPressedDuration(attack);
	}
	else if (isKeyPressed(return_safe)) {
		keyPressedDuration(return_safe);
	}
	setmap();
}

//地图滚动函数
void battleScene1::setmap()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Point orig = Point(mainActor2->getPositionX(), mainActor2->getPositionY());
	Point dest = Point(visibleSize.width / 2, visibleSize.height / 2);
	Point distance = dest - orig;
	Point newMapPos = Point(0, 0) + distance;
	newMapPos.x = (newMapPos.x > 0 ? 0 : newMapPos.x);
	newMapPos.y = (newMapPos.y > 0 ? 0 : newMapPos.y);
	newMapPos.x = (newMapPos.x < visibleSize.width - 960 ?
		visibleSize.width - 960 : newMapPos.x);
	newMapPos.y = (newMapPos.y < visibleSize.height - 960 ?
		visibleSize.height - 960 : newMapPos.y);
	map->setPosition(newMapPos);
}

void battleScene1::setPlayerPosition(Point position)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//从像素点坐标转化为瓦片坐标  
	Point tileCoord = this->tileCoordFromPosition(position);                            
		//获得瓦片的GID  
		int tileGid = _collidable->getTileGIDAt(tileCoord);                              

		if (tileGid > 0) {
			
				Value prop = map->getPropertiesForGID(tileGid);                         
				ValueMap propValueMap = prop.asValueMap();                              

				std::string collision = propValueMap["Collidable"].asString();                      

				if (collision == "true") { //碰撞检测成功                                   
					//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
					int tempX = mainActor2->getPositionX();
					int tempY = mainActor2->getPositionY();
					if (tempX < visibleSize.width / 2 && tempY < visibleSize.height / 2)
					{
						auto moveTo = MoveTo::create(0.1, Vec2(tempX + 6, tempY + 6));
						mainActor2->runAction(moveTo);
						return;
					}
					else if(tempX < visibleSize.width / 2 && tempY > visibleSize.height / 2)
					{
						auto moveTo = MoveTo::create(0.1, Vec2(tempX + 6, tempY - 6));
						mainActor2->runAction(moveTo);
						return;
					}
					else if (tempX > visibleSize.width / 2 && tempY > visibleSize.height / 2)
					{
						auto moveTo = MoveTo::create(0.1, Vec2(tempX - 6, tempY - 6));
						mainActor2->runAction(moveTo);
						return;
					}
					else if (tempX > visibleSize.width / 2 && tempY < visibleSize.height / 2)
					{
						auto moveTo = MoveTo::create(0.1, Vec2(tempX - 6, tempY + 6));
						mainActor2->runAction(moveTo);
						return;
					}
					
				}
				
		}
		auto moveTo = MoveTo::create(0.2, Vec2(position.x, position.y));
		mainActor2->runAction(moveTo);

}

//获取瓦片坐标的函数
Point battleScene1::tileCoordFromPosition(Point pos)
{
	int x = pos.x / map->getTileSize().width;                                   
		int y = ((map->getMapSize().height * map->getTileSize().height) - pos.y) /
		map->getTileSize().height;         
		return Point(x, y);
}

void battleScene1::attack_1(float dt)
{

	auto bullte = Sprite::create("bullet.png");
	map->addChild(bullte, 2);
	bullte->setPosition(Vec2(flower->getPositionX(), flower->getPositionY()));
	auto moveTo = MoveTo::create(1.2, Vec2(-1000,
		-500));
	bullte->runAction(moveTo);
	auto rec1 = bullte->getBoundingBox();
	auto rec2 = mainActor2->getBoundingBox();
	bool collision = rec2.intersectsRect(rec1);
	if (collision)
	{
		map->removeChild(flower);
	}

}


void battleScene1::running1_1(float dt)
{

	auto moveTo = MoveTo::create(1.2, Vec2(mainActor2->getPositionX() - 25,
		mainActor2->getPositionY() + 25));
	pig1->runAction(moveTo);
	auto rec1 = pig1->getBoundingBox();
	auto rec2 = mainActor2->getBoundingBox();
	bool collision = rec2.intersectsRect(rec1);
	if (collision&&Num_1>0)
	{
		Damage1++;

		if (Damage1 == 1)
		{
			blood->setPosition(Vec2(-1000, 100));
			blood1->setScale(0.6);
			blood1->setPosition(Vec2(-30, 100));
		}
		else if (Damage1 == 2)
		{
			blood1->setPosition(Vec2(-1000, 100));
			blood2->setScale(0.6);
			blood2->setPosition(Vec2(-30, 100));
		}
		else if (Damage1 == 3)
		{
			blood2->setPosition(Vec2(-1000, 100));
			blood3->setScale(0.6);
			blood3->setPosition(Vec2(-30, 100));
		}
		else if (Damage1 == 4)
		{
			blood3->setPosition(Vec2(-1000, 100));
			blood4->setScale(0.6);
			blood4->setPosition(Vec2(-30, 100));
		}
		else if (Damage1 == 5)
		{
			blood4->setPosition(Vec2(-1000, 100));
			blood5->setScale(0.6);
			blood5->setPosition(Vec2(-30, 100));
		}
		else if (Damage1 == 6)
		{
			blood5->setPosition(Vec2(-1000, 100));
			blood6->setScale(0.6);
			blood6->setPosition(Vec2(-30, 100));
			auto visibleSize = Director::getInstance()->getVisibleSize();
			Vec2 origin = Director::getInstance()->getVisibleOrigin();
			auto lose = Sprite::create("lose.png");
			map->addChild(lose);
			lose->setPosition(Vec2(visibleSize.width / 2,
				visibleSize.height / 2));
			auto label = Label::createWithTTF("Press F To Return SafeMap", "fonts/Marker Felt.ttf", 36);
			if (label == nullptr)
			{
				problemLoading("'fonts/Marker Felt.ttf'");
			}
			else
			{
				// position the label on the center of the screen
				label->setColor(Color3B::WHITE);
				label->setPosition(Vec2(visibleSize.width / 2 + 150,
					visibleSize.height / 2));

				// add the label as a child to this layer
				map->addChild(label, 1);
			}
		}
	}

}

void battleScene1::running2_1(float dt)
{
	if (judgepig2_1)
	{
		auto moveTo = MoveTo::create(1.2, Vec2(mainActor2->getPositionX() - 50,
			mainActor2->getPositionY() + 50));
		pig2->runAction(moveTo);
		auto rec1 = pig2->getBoundingBox();
		auto rec2 = mainActor2->getBoundingBox();
		bool collision = rec2.intersectsRect(rec1);
		if (collision&&Num_1>0)
		{
			Damage1++;

			if (Damage1 == 1)
			{
				blood->setPosition(Vec2(-1000, 100));
				blood1->setScale(0.6);
				blood1->setPosition(Vec2(-30, 100));
			}
			else if (Damage1 == 2)
			{
				blood1->setPosition(Vec2(-1000, 100));
				blood2->setScale(0.6);
				blood2->setPosition(Vec2(-30, 100));
			}
			else if (Damage1 == 3)
			{
				blood2->setPosition(Vec2(-1000, 100));
				blood3->setScale(0.6);
				blood3->setPosition(Vec2(-30, 100));
			}
			else if (Damage1 == 4)
			{
				blood3->setPosition(Vec2(-1000, 100));
				blood4->setScale(0.6);
				blood4->setPosition(Vec2(-30, 100));
			}
			else if (Damage1 == 5)
			{
				blood4->setPosition(Vec2(-1000, 100));
				blood5->setScale(0.6);
				blood5->setPosition(Vec2(-30, 100));
			}
			else if (Damage1 == 6)
			{
				blood5->setPosition(Vec2(-1000, 100));
				blood6->setScale(0.6);
				blood6->setPosition(Vec2(-30, 100));
				auto visibleSize = Director::getInstance()->getVisibleSize();
				Vec2 origin = Director::getInstance()->getVisibleOrigin();
				auto lose = Sprite::create("lose.png");
				map->addChild(lose);
				lose->setPosition(Vec2(visibleSize.width / 2,
					visibleSize.height / 2));
				auto label = Label::createWithTTF("Press F To Return SafeMap", "fonts/Marker Felt.ttf", 36);
				if (label == nullptr)
				{
					problemLoading("'fonts/Marker Felt.ttf'");
				}
				else
				{
					// position the label on the center of the screen
					label->setColor(Color3B::WHITE);
					label->setPosition(Vec2(visibleSize.width / 2 + 150,
						visibleSize.height / 2));

					// add the label as a child to this layer
					map->addChild(label, 1);
				}
			}
		}
	}
}

void battleScene1::Close2(Ref* pSender)
{
	Director::getInstance()->end();
}

void battleScene1::setB1pause()
{
	b1_pause = 1;
}

int battleScene1::getB1pause()
{
	return b1_pause;
}