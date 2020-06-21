#ifndef __Setting_SCENE_H__  
#define __Setting_SCENE_H__  

#include "cocos2d.h"  
#include "SimpleAudioEngine.h"  

class Setting : public cocos2d::Scene
{
    bool isEffect;                                                     
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void cleanup();

    void menuSoundToggleCallback(cocos2d::Ref* pSender);
    void menuMusicToggleCallback(cocos2d::Ref* pSender);
    void menuOkCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(Setting);
};

#endif // __Setting_SCENE_H__  


