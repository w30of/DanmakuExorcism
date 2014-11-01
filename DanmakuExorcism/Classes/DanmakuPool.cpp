//
//  DanmakuPool.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-24.
//
//

#include "DanmakuPool.h"

static DanmakuPool *s_danmakuPool = nullptr;

DanmakuPool* DanmakuPool::getInstance()
{
    if (!s_danmakuPool) {
        s_danmakuPool = new DanmakuPool();
    }
    
    return s_danmakuPool;
}

DanmakuPool::DanmakuPool()
{
    
}

DanmakuPool::~DanmakuPool()
{
    
}

void DanmakuPool::push(BulletGenerator *pBG)
{
    BulletGeneratorType type = pBG->getBulletGeneratorType();
    if (type == ENEMY) {
        v_enemy.push_back(pBG);
    }
    else if (type == ENEMY_BULLET)
    {
        v_enemyBullet.push_back(pBG);
    }
    else if (type == PLAYER)
    {
        v_player.push_back(pBG);
    }
    else if (type == PLAYER_BULLET)
    {
        v_playerBullet.push_back(pBG);
    }
}







