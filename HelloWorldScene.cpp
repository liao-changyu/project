/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "safeMap.h"
#include "Tip.h"
#include "ui/CocosGUI.h"
using namespace CocosDenshion;
USING_NS_CC;


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
  
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	audio = SimpleAudioEngine::getInstance();//background music

   // set the background music and continuously play it.
	audio->playBackgroundMusic("bgm.mp3", true);

    
 auto startItem = MenuItemImage::create(
	                                         "play.png",
	                                         "play.png",
                                           CC_CALLBACK_1(HelloWorld::replace, this));

    if (startItem == nullptr ||
        startItem->getContentSize().width <= 0 ||
        startItem->getContentSize().height <= 0)
    {
        problemLoading("'play.png' and 'play.png'");
    }
    else
    {
        startItem->setPosition(Vec2(870,100));
    }
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, NULL);
	menu->setColor(Color3B::WHITE);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    /////////////////////////////
    // 3. add your codes below...
	//创建关闭键
auto closeItem = MenuItemImage::create(
		"Close.png",
		"Close.png",
		CC_CALLBACK_1(HelloWorld::Close2, this));

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
	//创建TIP键
auto tipItem = MenuItemImage::create(
		"Tip.png",
		"Tip.png",
		CC_CALLBACK_1(HelloWorld::replace2, this));

	if (tipItem == nullptr ||
		tipItem->getContentSize().width <= 0 ||
		tipItem->getContentSize().height <= 0)
	{
		problemLoading("'Tip.png' and 'Tip.png'");
	}
	else
	{
		tipItem->setPosition(Vec2(50, 50));
	}
	// create menu, it's an autorelease object
	auto menu3 = Menu::create(tipItem, NULL);
	menu3->setColor(Color3B::WHITE);
	menu3->setPosition(Vec2::ZERO);
	this->addChild(menu3, 1);
    
	//创建静音键
	auto offItem = MenuItemImage::create(
		"off.png",
		"off.png",
		CC_CALLBACK_1(HelloWorld::Stop, this));

	if (offItem == nullptr ||
		offItem->getContentSize().width <= 0 ||
		offItem->getContentSize().height <= 0)
	{
		problemLoading("'off.png' and 'off.png'");
	}
	else
	{
		offItem->setPosition(Vec2(250, 50));
	}
	// create menu, it's an autorelease object
	auto menu4 = Menu::create(offItem, NULL);
	menu4->setColor(Color3B::WHITE);
	menu4->setPosition(Vec2::ZERO);
	this->addChild(menu4, 1);

	//创建开音键
	auto onItem = MenuItemImage::create(
		"on.png",
		"on.png",
		CC_CALLBACK_1(HelloWorld::On, this));

	if (onItem == nullptr ||
		onItem->getContentSize().width <= 0 ||
		onItem->getContentSize().height <= 0)
	{
		problemLoading("'on.png' and 'on.png'");
	}
	else
	{
		onItem->setPosition(Vec2(150, 50));
	}
	// create menu, it's an autorelease object
	auto menu5 = Menu::create(onItem, NULL);
	menu5->setColor(Color3B::WHITE);
	menu5->setPosition(Vec2::ZERO);
	this->addChild(menu5, 1);

	//添加背景图
	auto startBackground = Sprite::create("FirstScene.png");
	if (startBackground == nullptr)
	{
		problemLoading("'FirstScene.png'");
	}
	else
	{
		startBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(startBackground, 0);
	}


    return true;
}

void HelloWorld::replace(Ref* pSender)
{
	auto hello = safeMap::createScene();
	TransitionCrossFade* trs = TransitionCrossFade::create(1.0, hello);
	Director::getInstance()->replaceScene(trs);
}

void HelloWorld::replace2(Ref* pSender)
{
	auto hello = Tip::createScene();
	TransitionCrossFade* trs = TransitionCrossFade::create(1.0, hello);
	Director::getInstance()->replaceScene(trs);
}

void HelloWorld::Close2(Ref* pSender)
{
	Director::getInstance()->end();
}

void HelloWorld::Stop(Ref* pSender)
{
	audio->pauseBackgroundMusic();
}

void HelloWorld::On(Ref* pSender)
{
	audio->resumeBackgroundMusic();
}