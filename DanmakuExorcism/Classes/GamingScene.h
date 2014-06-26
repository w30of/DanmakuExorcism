#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GamingScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GamingScene);
private:
// inner funcs
    void GamePreparing();
    
    // callbacks
    void menuCloseCallback(cocos2d::Ref* pSender);
    
};

#endif // __HELLOWORLD_SCENE_H__
