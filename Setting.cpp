#include "Setting.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* Setting::createScene()
{
	return Setting::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Setting::init()
{
    if (!Scene::init())
    {
        return false;
    }

 

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    Sprite* bg = Sprite::create("pause.png");

    bg->setPosition(Point(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(bg);

    //ÒôÐ§  
    auto soundOnMenuItem = MenuItemImage::create(
        "on.png",
        "on.png");
    auto soundOffMenuItem = MenuItemImage::create(
        "off.png",
        "off.png");
    auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(Setting::menuSoundToggleCallback, this),
        soundOffMenuItem,
        soundOnMenuItem,
        NULL);
    soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Point(818, 220)));

    //±³¾°ÒôÀÖ  
    auto musicOnMenuItem = MenuItemImage::create(
        "on.png",
        "on.png");
    auto musicOffMenuItem = MenuItemImage::create(
        "off.png",
        "off.png");
    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(Setting::menuMusicToggleCallback, this),
        musicOffMenuItem,
        musicOnMenuItem,
        NULL);
    musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Point(818, 362)));

    //Ok°´Å¥  
    auto okMenuItem = MenuItemImage::create(
        "start.png",
        "pause.png",
        CC_CALLBACK_1(Setting::menuOkCallback, this));
    okMenuItem->setPosition(Director::getInstance()->convertToGL(Point(600, 510)));

    Menu* mn = Menu::create(soundToggleMenuItem, musicToggleMenuItem, okMenuItem, NULL);
    mn->setPosition(Point::ZERO);
    this->addChild(mn);

    return true;
}

void Setting::menuOkCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
    if (isEffect) {
        SimpleAudioEngine::getInstance()->playEffect("click.wav");                  
    }
}

void Setting::menuSoundToggleCallback(Ref* pSender)                         
{
    auto soundToggleMenuItem = (MenuItemToggle*)pSender;
    log("soundToggleMenuItem %d", soundToggleMenuItem->getSelectedIndex());

    if (isEffect) {
        SimpleAudioEngine::getInstance()->playEffect("click.wav");                  
    }

    if (soundToggleMenuItem->getSelectedIndex() == 1) {//Ñ¡ÖÐ×´Ì¬Off -> On                  
        isEffect = false;
    }
    else {
        isEffect = true;
        SimpleAudioEngine::getInstance()->playEffect("click.wav");                  
    }
}

void Setting::menuMusicToggleCallback(Ref* pSender)                         
{
    auto musicToggleMenuItem = (MenuItemToggle*)pSender;
    
    if (musicToggleMenuItem->getSelectedIndex() == 1) {//Ñ¡ÖÐ×´Ì¬Off -> On                 
        SimpleAudioEngine::getInstance()->stopBackgroundMusic("bgm.mp3");
    }
    else {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3");
    }
    if (isEffect) {
        SimpleAudioEngine::getInstance()->playEffect("click.wav");                  
    }
}

void Setting::onEnter()
{
   Scene::onEnter();
}

void Setting::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    isEffect = true;
    //²¥·Å  
    SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3", true);      
}

void Setting::onExit()
{
    Scene::onExit();
}

void Setting::onExitTransitionDidStart()
{
   Scene::onExitTransitionDidStart();
}

void Setting::cleanup()
{
    Scene::cleanup();
    //Í£Ö¹  
    SimpleAudioEngine::getInstance()->stopBackgroundMusic("bgm.mp3");            
}