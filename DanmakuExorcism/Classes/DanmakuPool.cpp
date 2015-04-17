//
//  DanmakuPool.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-24.
//
//

#include "DanmakuPool.h"
#include "Bullet.h"
#include "GameLogic.h"

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

BulletGenerator* DanmakuPool::getPlayerBullet()
{
    return getBulletByType(PLAYER_BULLET);
}

BulletGenerator* DanmakuPool::getEnemyBullet()
{
    return getBulletByType(ENEMY_BULLET);
}

void DanmakuPool::clearPool()
{
    v_player.clear();
    v_enemy.clear();
    v_playerBullet.clear();
    v_enemyBullet.clear();
    GameLogic::clearDanmakuContainer();
}



// private funcs...
BulletGenerator* DanmakuPool::getBulletByType(BulletGeneratorType type)
{
    // Seek a free bullet from danmaku pool
    if (type == ENEMY_BULLET && v_enemyBullet.size() > 0) {
        for (int i = 0; i < v_enemyBullet.size(); ++i) {
            Bullet* bullet = (Bullet*)v_enemyBullet.at(i);
            if (!bullet->getBulletEnable()) {
                bullet->defaultInfo();
                return bullet;
            }
        }
    } else if (type == PLAYER_BULLET && v_playerBullet.size() > 0) {
        for (int i = 0; i < v_playerBullet.size(); ++i) {
            Bullet* bullet = (Bullet*)v_playerBullet.at(i);
            if (!bullet->getBulletEnable()) {
                bullet->defaultInfo();
                return bullet;
            }
        }
    }
    
    // Has no free bullet, create one
    Bullet* blt = Bullet::create();
    blt->defaultInfo();
    blt->bulletDisable();   // Bullet is disable at firsts
    blt->setBulletGeneratorType(type);
    // Add it to layer for show
    if (type == PLAYER_BULLET) {
        GameLogic::addPlayerBullet(blt);
    } else if (ENEMY_BULLET) {
        GameLogic::addEnemyBullet(blt);
    }
    
    DanmakuPool::getInstance()->push(blt);  // Will add to the matched danmaku pool by BulletGeneratorType
    return blt;
}





