//
//  DanmakuPool.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-24.
//
//

#ifndef __DanmakuExorcism__DanmakuPool__
#define __DanmakuExorcism__DanmakuPool__

//#include <stdio.h>
#include "cocos2d.h"
#include "BulletGenerator.h"

class DanmakuPool
{
public:
    static DanmakuPool *getInstance();
    
    void push(BulletGenerator* pBG);
    BulletGenerator* getPlayerBullet();
    BulletGenerator* getEnemyBullet();
    void clearPool();
    void clearOneThing(BulletGeneratorType type, bool withAnimate);
    void eraseEnemy(BulletGenerator* enemyToErase);
    
    std::vector<BulletGenerator*> v_player;
    std::vector<BulletGenerator*> v_enemy;
    std::vector<BulletGenerator*> v_enemyBullet;
    std::vector<BulletGenerator*> v_playerBullet;
    
private:
    DanmakuPool();
    virtual ~DanmakuPool();
    
    BulletGenerator* getBulletByType(BulletGeneratorType type);
};

#endif /* defined(__DanmakuExorcism__DanmakuPool__) */
