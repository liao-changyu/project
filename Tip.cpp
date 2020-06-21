#include "Tip.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "battleScene1.h"
#include "safeMap.h"
#include "battleScene.h"

USING_NS_CC;


Scene* Tip::createScene()
{
	return Tip::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Tip::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->scheduleUpdate();
	//创建关闭键
	auto closeItem = MenuItemImage::create(
		"Close.png",
		"Close.png",
		CC_CALLBACK_1(Tip::Close2, this));

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
	auto menu2 = Menu::create(closeItem, NULL);
	menu2->setColor(Color3B::WHITE);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 3);
	//return键
	auto returnItem = MenuItemImage::create(
		"return.png",
		"return.png",
		CC_CALLBACK_1(Tip::replace, this));

	if (returnItem == nullptr ||
		returnItem->getContentSize().width <= 0 ||
		returnItem->getContentSize().height <= 0)
	{
		problemLoading("'return.png' and 'return.png'");
	}
	else
	{
		returnItem->setPosition(Vec2(180, 170));
	}
	// create menu, it's an autorelease object
	auto menu = Menu::create(returnItem, NULL);
	menu->setColor(Color3B::WHITE);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	
	auto tip = Sprite::create("TipBoard.png");
	tip->setScale(0.8);
	tip->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(tip, 0);

	
}
	
void Tip::Close2(Ref* pSender)
{
	Director::getInstance()->end();
}

void Tip::replace(Ref* pSender)
{
	auto hello = HelloWorld::createScene();
	TransitionCrossFade* trs = TransitionCrossFade::create(1.0, hello);
	Director::getInstance()->replaceScene(trs);
}

//判断键盘是否被按下

