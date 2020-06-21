#include "safeMap.h"
#include "SimpleAudioEngine.h"
#include "weaPon.h"
#include "monster.h"
#include "battleScene1.h"
#include "Tip.h"
USING_NS_CC;

//����һ������
Scene* safeMap::createScene()
{
	return safeMap::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//�����ĳ�ʼ��
bool safeMap::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//����cocos�а����ĵ�����
	this->scheduleUpdate();
	//���õ�����
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//��������
	mainActor3 = Sprite::create("z1.png");
	if (mainActor3 == nullptr)
	{
		problemLoading("'z1.png'");
	}
	mainActor3->setAnchorPoint(Vec2(0.5, 0.5));
	//�������ǵ�֡����
	cocos2d::Vector<SpriteFrame*> animFrames;
	animFrames.reserve(3);
	animFrames.pushBack(SpriteFrame::create("z2.png", Rect(0, 0, 85, 90)));
	animFrames.pushBack(SpriteFrame::create("z3.png", Rect(0, 0, 85, 90)));
	animFrames.pushBack(SpriteFrame::create("z4.png", Rect(0, 0, 85, 90)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	mainActor3->runAction(RepeatForever::create(animate));

	//������Ƭ��ͼ
	map2 = TMXTiledMap::create("safemap.tmx");
	addChild(map2, 1);
	map2->setAnchorPoint(Vec2(0, 0));
	map2->setPosition(0, 0);
	map2->addChild(mainActor3, 2);


	//�����رռ�
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


	//������Ƭ��ͼ������ж����λ����Ϣ
	TMXObjectGroup* ob1 = map2->getObjectGroup("object1");
	ValueMap val = ob1->getObject("sp1");

	//��Ƭ��ͼ�е�����ת��Ϊcocos����
	float x = val["x"].asFloat();
	float y = val["y"].asFloat();
	//�����Ǽ��뵽cocos��ͼ��
	mainActor3->setPosition(Vec2(x, y));

	//��ӷ���
	ValueMap val2 = ob1->getObject("staff");
	float x1 = val2["x"].asFloat();
	float y1 = val2["y"].asFloat();
	 lightStaff = Sprite::create("light.png");
	map2->addChild(lightStaff);
	lightStaff->setPosition(Vec2(x1, y1));

	//�����ϰ���Ĳ��ɼ�����
	_collidable2 = map2->getLayer("collide");
	_collidable2->setVisible(false);

	
	


	//����cocos��ͼ���������ӽ��ƶ�
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

	//���������¼�������
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

//�жϼ����Ƿ񱻰���
bool safeMap::isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {
	if (keys2[code]) {
		return true;
	}
	else return false;
}

//���̰���ʱ���еĲ���
void safeMap::keyPressedDuration(cocos2d::EventKeyboard::KeyCode code) {
	int setX = 0, setY = 0;
	switch (code) {
		//���������ƶ�ʱ�Ĳ���
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

	//���õ�ͼ���������ӽ��ƶ�
	setPlayerPosition(pos);
}

//���������õ�Update����
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

//��ͼ��������
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
	//�����ص�����ת��Ϊ��Ƭ���� 
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//�����Ƭ��GID  
	Point tileCoord = this->tileCoordFromPosition(position);
	int tileGid = _collidable2->getTileGIDAt(tileCoord);

	//�����Ƭ�Ƿ������ײ����
	if (tileGid > 0) {

		Value prop = map2->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		std::string collision = propValueMap["Collidable"].asString();

		//��ײ���ɹ� 
		if (collision == "true")
		{
			int tempX = mainActor3->getPositionX();
			int tempY = mainActor3->getPositionY();

			//ײ���ϰ�������ǻᱻ����
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