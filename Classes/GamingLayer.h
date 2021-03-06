//
//  GamingLayer.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-6-25.
//
//

#ifndef __DanmakuExorcism__GamingLayer__
#define __DanmakuExorcism__GamingLayer__

#include "cocos2d.h"
#include "BulletGenerator.h"
#include "Bullet.h"
#include "Player.h"
#include "DanmakuPool.h"

USING_NS_CC;

class GamingLayer : public Layer
{
public:
    GamingLayer();
    virtual ~GamingLayer();
    virtual bool init();
    CREATE_FUNC(GamingLayer);
    
    bool onTouchBegan(Touch* touch, Event  *event);
    void onTouchMoved(Touch* touch, Event  *event);
    void onTouchEnded(Touch* touch, Event  *event);
    
    void setPlayerType(PlayerType type);
    void showLogo(int stageID);
private:
    
    void prepare();                     // data preset
    void update(float dt);              // main schedule, stage creator
    
    // members
    Size m_WinSize;

    Player* _player;
};

#endif /* defined(__DanmakuExorcism__GamingLayer__) */
