//
//  GameLogic.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-28.
//
//

#ifndef __DanmakuExorcism__GameLogic__
#define __DanmakuExorcism__GameLogic__

#include "cocos2d.h"
#include "Protocol.h"
#include "GamingLayer.h"
#include "Bullet.h"

class GameLogic
{
public:
    static GameLogic *getInstance();
    // public property
    GamingLayer *gLayer;
    Size winSize;
    
    // public function
    static void addPlayerBullet(Bullet *bullet);
    static void createEnemy(float time);
    
private:
    GameLogic();
    virtual ~GameLogic();
};

#endif /* defined(__DanmakuExorcism__GameLogic__) */
