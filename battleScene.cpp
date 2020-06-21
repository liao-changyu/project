#include "battleScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "weaPon.h"
#include "monster.h"
#include "Tip.h"
#include "safeMap.h"

USING_NS_CC;

static int Hp1 = 30, Hp2 = 300, Hpf = 300;
static int Num = 3;
static int Damage = 0;
static int judgepig2 = 1;


//����һ������
Scene* battleScene::createScene()
{
	return battleScene::create();
}
//
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//�����ĳ�ʼ��
bool battleScene::init()
{
	do {
		CC_BREAK_IF(!Scene::init());
		//ÿ��0.2S����һ�η����ӵ�����
		if (judgepig2 == 1)
		{
			this->schedule(schedule_selector(battleScene::attack), 1.0f);
			this->schedule(schedule_selector(battleScene::running1), 1.5f);
			this->schedule(schedule_selector(battleScene::running2), 2.0f);
		}
		
	} while (0);
	
	//����cocos�а����ĵ�����
	this->scheduleUpdate();
	//���õ�����
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//�����رռ�
	auto closeItem = MenuItemImage::create(
		"Close.png",
		"Close.png",
		CC_CALLBACK_1(battleScene::Close1, this));

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


	//��������
	mainActor = Sprite::create("z1.png");
	if (mainActor == nullptr)
	{
		problemLoading("'z1.png'");
	}
	auto lightStaff = Sprite::create("light.png");
	mainActor->addChild(lightStaff);
	lightStaff->setAnchorPoint(Vec2(-0.5, -0.5));
	lightStaff->setPosition(Vec2(10, 6));
	mainActor->setAnchorPoint(Vec2(0.5, 0.5));
	//�������ǵ�֡����
	cocos2d::Vector<SpriteFrame*> animFrames;
	animFrames.reserve(3);
	animFrames.pushBack(SpriteFrame::create("z2.png", Rect(0, 0, 85, 90)));
	animFrames.pushBack(SpriteFrame::create("z3.png", Rect(0, 0, 85, 90)));
	animFrames.pushBack(SpriteFrame::create("z4.png", Rect(0, 0, 85, 90)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	mainActor->runAction(RepeatForever::create(animate));


	//������Ƭ��ͼ
	map1 = TMXTiledMap::create("battle1.tmx");
	addChild(map1, 1); 
	map1->setAnchorPoint(Vec2(0,0));
	map1->setPosition(0, 0);
	map1->addChild(mainActor, 2);

	//������Ƭ��ͼ������ж����λ����Ϣ
	TMXObjectGroup* ob1 = map1->getObjectGroup("sprite1");
	ValueMap val = ob1->getObject("sp1");

	//��Ƭ��ͼ�е�����ת��Ϊcocos����
	float x = val["x"].asFloat();
	float y = val["y"].asFloat();
	//�����Ǽ��뵽cocos��ͼ��
	mainActor->setPosition(Vec2(x, y));

	//��ʼ��Ѫ��
	blood = Sprite::create("blood6.png");
	blood1 = Sprite::create("blood5.png");
	blood2 = Sprite::create("blood4.png");
	blood3 = Sprite::create("blood3.png");
	blood4 = Sprite::create("blood2.png");
	blood5 = Sprite::create("blood1.png");
	blood6 = Sprite::create("blood0.png");
	mainActor->addChild(blood);

	mainActor->addChild(blood1);
	mainActor->addChild(blood2);
	mainActor->addChild(blood3);
	mainActor->addChild(blood4);
	mainActor->addChild(blood5);
	mainActor->addChild(blood6);

	blood->setScale(0.6);
	blood->setPosition(Vec2(-30, 100));
	blood1->setPosition(Vec2(-1000, 100));
	blood2->setPosition(Vec2(-1000, 100));
	blood3->setPosition(Vec2(-1000, 100));
	blood4->setPosition(Vec2(-1000, 100));
	blood5->setPosition(Vec2(-1000, 100));
	blood6->setPosition(Vec2(-1000, 100));

	//�����ϰ���Ĳ��ɼ�����
	_collidable1 = map1->getLayer("collide");
	_collidable1->setVisible(false);

	

	//����cocos��ͼ���������ӽ��ƶ�
	Point orig = Point(mainActor->getPositionX(), mainActor->getPositionY());
	Point dest = Point(visibleSize.width / 2, visibleSize.height / 2);
	Point distance = dest - orig;
	Point newMapPos = Point(0, 0) + distance;
	newMapPos.x = (newMapPos.x > 0 ? 0 : newMapPos.x);
	newMapPos.y = (newMapPos.y > 0 ? 0 : newMapPos.y);
	newMapPos.x = (newMapPos.x < -visibleSize.width ?
		-visibleSize.width : newMapPos.x);
	newMapPos.y = (newMapPos.y < -visibleSize.height ?
		-visibleSize.height : newMapPos.y);
	map1->setPosition(newMapPos);

	//��ȡ��Ƭ��ͼ����ͼ���й��޵ĳ�����
	ValueMap val2 = ob1->getObject("mons1");
	float x1 = val2["x"].asFloat();
	float y1 = val2["y"].asFloat();

	//����һ���粼�ֹ���
	goblin = Sprite::create("flower.png");
	if (goblin == nullptr)
	{
		problemLoading("'flower.png'");
	}
	map1->addChild(goblin, 1);
	//�������Ĵ�С
	goblin->setScale(1.2);
	goblin->setPosition(Vec2(x1, y1));
	mons[0] = goblin;
	
	//����Ұ���
	ValueMap val3 = ob1->getObject("mons2");
	float x2 = val3["x"].asFloat();
	float y2 = val3["y"].asFloat();

	Pig1 = Sprite::create("Runningpig.png");
	if (goblin == nullptr)
	{
		problemLoading("'Runningpig.png'");
	}
	map1->addChild(Pig1, 1);
	Pig1->setScale(1.2);
	Pig1->setPosition(Vec2(x2, y2));
	mons[1] = Pig1;

	//������һ��Ұ���
	ValueMap val4 = ob1->getObject("mons3");
	float x3 = val4["x"].asFloat();
	float y3 = val4["y"].asFloat();

	Pig2 = Sprite::create("Crab.png");
	if (Pig2 == nullptr)
	{
		problemLoading("'Crab.png'");
	}
	map1->addChild(Pig2, 1);
	Pig2->setScale(1.2);
	Pig2->setPosition(Vec2(x3, y3));
	//�����޷���Vector
	mons[2] = Pig2;
	/*
	bullet = Sprite::create("ball.png");
	map1->addChild(bullet, 1);
	bullet->setPosition(Vec2(x1, y1));
	*/
	
	
	//���������¼�������
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event) {
		keys1[code] = true;
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {
		keys1[code] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

//�жϼ����Ƿ񱻰���
bool battleScene::isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {
	if (keys1[code]) {
		return true;
	}
	else return false;
}

//���̰���ʱ���еĲ���
void battleScene::keyPressedDuration(cocos2d::EventKeyboard::KeyCode code) 
{
	int setX = 0, setY = 0;

	//���һ��������Ч
	sprite_1 = Sprite::create("s1.png");
	switch (code)
	{
		//���������ƶ�ʱ�Ĳ���
	case EventKeyboard::KeyCode::KEY_W:setY = 5;
		break;
	case EventKeyboard::KeyCode::KEY_S:setY = -5;
		break;
	case EventKeyboard::KeyCode::KEY_A:setX = -5;
		break;
	case EventKeyboard::KeyCode::KEY_D:setX = 5;
		break;

		//�����Ĳ���
	case EventKeyboard::KeyCode::KEY_J:
	{
		if (Num > 0)
		{
			if (judgepig2 == 1)
			{
				Hp1--;
				if (Hp1 > 0)
				{
					map1->addChild(sprite_1, 1);
					//�����������еĹ�������
					weaPon staff;
					staff.attack(sprite_1, sprite_1, sprite_1,
						mons[0], mons[1], mons[2]);
				}
				else
				{
					judgepig2 = 0;
					Num = 0;
					auto deadpig = Sprite::create("DeadPig.png");
					map1->addChild(deadpig);
					deadpig->setPosition(Vec2(Pig1->getPositionX(),
						goblin->getPositionY()));
					Pig2->setScale(0.01);
					auto deadCrab = Sprite::create("DeadCrab.png");
					map1->addChild(deadCrab);
					deadCrab->setPosition(Vec2(Pig2->getPositionX(),
						Pig2->getPositionX()));
					Pig1->setScale(0.01);

					auto deadflower = Sprite::create("DeadFlower.png");
					map1->addChild(deadflower);
					deadflower->setPosition(Vec2(goblin->getPositionX(),
						goblin->getPositionY()));
					goblin->setPosition(Vec2(-1000, -800));

					auto blood_resume = Sprite::create("blood_resume.png");
					map1->addChild(blood_resume);
					blood_resume->setPosition(Vec2(512, 500));

					auto blue_resume = Sprite::create("blue_resume.png");
					map1->addChild(blue_resume);
					blue_resume->setPosition(Vec2(400, 500));

					auto Gun = Sprite::create("Gun.png");
					map1->addChild(Gun);
					Gun->setPosition(Vec2(500, 600));

					if (Num == 0)
					{
						auto visibleSize = Director::getInstance()->getVisibleSize();
						Vec2 origin = Director::getInstance()->getVisibleOrigin();
						auto win = Sprite::create("victory.png");
						map1->addChild(win);
						win->setPosition(Vec2(visibleSize.width / 2,
							visibleSize.height / 2));
						auto label = Label::createWithTTF("Click CloseItem To End",
							"fonts/Marker Felt.ttf", 36);
						if (label == nullptr)
						{
							problemLoading("'fonts/Marker Felt.ttf'");
						}
						else
						{
							// position the label on the center of the screen
							label->setColor(Color3B::WHITE);
							label->setPosition(Vec2(visibleSize.width / 2,
								visibleSize.height / 2 + 150));

							// add the label as a child to this layer
							map1->addChild(label, 1);
						}
					}
				}
			}
		}
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

	int dest_X = mainActor->getPositionX() + setX;
	int dest_Y = mainActor->getPositionY() + setY;
	Point pos = Point(dest_X, dest_Y);

	//���õ�ͼ���������ӽ��ƶ�
	setPlayerPosition(pos);
}

//���������õ�Update����
void battleScene::update(float delta) {
	Node::update(delta);
	auto up = EventKeyboard::KeyCode::KEY_W;
	auto down = EventKeyboard::KeyCode::KEY_S;
	auto right = EventKeyboard::KeyCode::KEY_A;
	auto left = EventKeyboard::KeyCode::KEY_D;
	auto attack= EventKeyboard::KeyCode::KEY_J;
	auto re_safe= EventKeyboard::KeyCode::KEY_F;
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
	else if (isKeyPressed(attack)) {
		keyPressedDuration(attack);
	}
	else if (isKeyPressed(re_safe)) {
		keyPressedDuration(re_safe);
	}
	setmap();
}

//��ͼ��������
void battleScene::setmap()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Point orig = Point(mainActor->getPositionX(),mainActor->getPositionY());
	Point dest = Point(visibleSize.width / 2, visibleSize.height / 2);
	Point distance = dest - orig;
	Point newMapPos = Point(0, 0) + distance;
	newMapPos.x = (newMapPos.x > 0 ? 0 : newMapPos.x);
	newMapPos.y = (newMapPos.y > 0 ? 0 : newMapPos.y);
	newMapPos.x = (newMapPos.x < visibleSize.width - 960 ?
		visibleSize.width - 960 : newMapPos.x);
	newMapPos.y = (newMapPos.y < visibleSize.height - 960 ?
		visibleSize.height - 960 : newMapPos.y);
	map1->setPosition(newMapPos);
}

void battleScene::setPlayerPosition(Point position)
{
	//�����ص�����ת��Ϊ��Ƭ���� 
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//�����Ƭ��GID  
	Point tileCoord = this->tileCoordFromPosition(position);
	int tileGid = _collidable1->getTileGIDAt(tileCoord);

	//�����Ƭ�Ƿ������ײ����
	if (tileGid > 0) {

		Value prop = map1->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		std::string collision = propValueMap["Collidable"].asString();

		//��ײ���ɹ� 
		if (collision == "true") 
		{ 
			int tempX = mainActor->getPositionX();
			int tempY = mainActor->getPositionY();

			//ײ���ϰ�������ǻᱻ����
			if (tempX < visibleSize.width / 2 && tempY < visibleSize.height / 2)
			{
				auto moveTo = MoveTo::create(0.1, Vec2(tempX + 6, tempY + 6));
				mainActor->runAction(moveTo);
				return;
			}
			else if (tempX < visibleSize.width / 2 && tempY > visibleSize.height / 2)
			{
				auto moveTo = MoveTo::create(0.1, Vec2(tempX + 6, tempY - 6));
				mainActor->runAction(moveTo);
				return;
			}
			else if (tempX > visibleSize.width / 2 && tempY > visibleSize.height / 2)
			{
				auto moveTo = MoveTo::create(0.1, Vec2(tempX - 6, tempY - 6));
				mainActor->runAction(moveTo);
				return;
			}
			else if (tempX > visibleSize.width / 2 && tempY < visibleSize.height / 2)
			{
				auto moveTo = MoveTo::create(0.1, Vec2(tempX - 6, tempY + 6));
				mainActor->runAction(moveTo);
				return;
			}

		}
	}
	auto moveTo = MoveTo::create(0.3, Vec2(position.x, position.y));
	mainActor->runAction(moveTo);

}

//��ȡ��Ƭ����ĺ���
Point battleScene::tileCoordFromPosition(Point pos)
{
	int x = pos.x / map1->getTileSize().width;
	int y = ((map1->getMapSize().height * map1->getTileSize().height) - pos.y) /
		map1->getTileSize().height;
	return Point(x, y);
}

void battleScene::attack(float dt)
{
	
		auto bullte = Sprite::create("bullet.png");
		map1->addChild(bullte, 2);
		bullte->setPosition(Vec2(goblin->getPositionX(), goblin->getPositionY()));
		auto moveTo = MoveTo::create(1.2, Vec2(1000,
			-500));
		bullte->runAction(moveTo);
		auto rec1 = bullte->getBoundingBox();
		auto rec2 = mainActor->getBoundingBox();
		bool collision = rec2.intersectsRect(rec1);
		if (collision)
		{
			map1->removeChild(goblin);
		}
	
}


void battleScene::running1(float dt)
{
	
	auto moveTo = MoveTo::create(1.2, Vec2(mainActor->getPositionX() -25,
		mainActor->getPositionY() + 25));
	Pig1->runAction(moveTo);
		auto rec1 = Pig1->getBoundingBox();
		auto rec2 = mainActor->getBoundingBox();
		bool collision = rec2.intersectsRect(rec1);
		if (collision&&Num>0)
		{
			Damage++;

			if (Damage == 1)
			{
				blood->setPosition(Vec2(-1000, 100));
				blood1->setScale(0.6);
				blood1->setPosition(Vec2(-30, 100));
			}
			else if (Damage == 2)
			{
				blood1->setPosition(Vec2(-1000, 100));
				blood2->setScale(0.6);
				blood2->setPosition(Vec2(-30, 100));
			}
			else if (Damage == 3)
			{
				blood2->setPosition(Vec2(-1000, 100));
				blood3->setScale(0.6);
				blood3->setPosition(Vec2(-30, 100));
			}
			else if (Damage == 4)
			{
				blood3->setPosition(Vec2(-1000, 100));
				blood4->setScale(0.6);
				blood4->setPosition(Vec2(-30, 100));
			}
			else if (Damage == 5)
			{
				blood4->setPosition(Vec2(-1000, 100));
				blood5->setScale(0.6);
				blood5->setPosition(Vec2(-30, 100));
			}
			else if (Damage == 6)
			{
				blood5->setPosition(Vec2(-1000, 100));
				blood6->setScale(0.6);
				blood6->setPosition(Vec2(-30, 100));
				auto visibleSize = Director::getInstance()->getVisibleSize();
				Vec2 origin = Director::getInstance()->getVisibleOrigin();
				auto lose = Sprite::create("lose.png");
				map1->addChild(lose);
				lose->setPosition(Vec2(visibleSize.width / 2,
					visibleSize.height / 2));
				auto label = Label::createWithTTF("Press F To Return Safemap",
					"fonts/Marker Felt.ttf", 36);
				if (label == nullptr)
				{
					problemLoading("'fonts/Marker Felt.ttf'");
				}
				else
				{
					// position the label on the center of the screen
					label->setColor(Color3B::WHITE);
					label->setPosition(Vec2(visibleSize.width / 2,
						visibleSize.height / 2 + 150));

					// add the label as a child to this layer
					map1->addChild(label, 1);
				}
			}
		}
	
}

void battleScene::running2(float dt)
{
	if (judgepig2)
	{
		auto moveTo = MoveTo::create(1.2, Vec2(mainActor->getPositionX() - 50,
		mainActor->getPositionY() + 50));
		Pig2->runAction(moveTo);
		auto rec1 = Pig2->getBoundingBox();
		auto rec2 = mainActor->getBoundingBox();
		bool collision = rec2.intersectsRect(rec1);
		if (collision&&Num>0)
		{
			Damage++;

			if (Damage == 1)
			{
				blood->setPosition(Vec2(-1000, 100));
				blood1->setScale(0.6);
				blood1->setPosition(Vec2(-30, 100));
			}
			else if (Damage == 2)
			{
				blood1->setPosition(Vec2(-1000, 100));
				blood2->setScale(0.6);
				blood2->setPosition(Vec2(-30, 100));
			}
			else if (Damage == 3)
			{
				blood2->setPosition(Vec2(-1000, 100));
				blood3->setScale(0.6);
				blood3->setPosition(Vec2(-30, 100));
			}
			else if (Damage == 4)
			{
				blood3->setPosition(Vec2(-1000, 100));
				blood4->setScale(0.6);
				blood4->setPosition(Vec2(-30, 100));
			}
			else if (Damage == 5)
			{
				blood4->setPosition(Vec2(-1000, 100));
				blood5->setScale(0.6);
				blood5->setPosition(Vec2(-30, 100));
			}
			else if (Damage == 6)
			{
				blood5->setPosition(Vec2(-1000, 100));
				blood6->setScale(0.6);
				blood6->setPosition(Vec2(-30, 100));
				auto visibleSize = Director::getInstance()->getVisibleSize();
				Vec2 origin = Director::getInstance()->getVisibleOrigin();
				auto lose = Sprite::create("lose.png");
				map1->addChild(lose);
				lose->setPosition(Vec2(visibleSize.width / 2,
					visibleSize.height / 2));
				//��ʾʧ�ܺ󷵻ذ�ȫ��ͼ
				auto label = Label::createWithTTF("Press F To Return Safemap",
					"fonts/Marker Felt.ttf", 36);
				if (label == nullptr)
				{
					problemLoading("'fonts/Marker Felt.ttf'");
				}
				else
				{
					// position the label on the center of the screen
					label->setColor(Color3B::WHITE);
					label->setPosition(Vec2(visibleSize.width / 2,
						visibleSize.height / 2 + 150));

					// add the label as a child to this layer
					map1->addChild(label, 1);
				}
			}
		}
	}
}

void battleScene::Close1(Ref* pSender)
{
	Director::getInstance()->end();
}

void battleScene::setBpause()
{
	b_pause = 1;
}

int battleScene::getBpause()
{
	return b_pause;
}