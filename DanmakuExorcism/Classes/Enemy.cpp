//
//  Enemy.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-16.
//
//

#include "Enemy.h"

Enemy::Enemy()
: m_danmaku(nullptr)
{
    
}

Enemy::~Enemy()
{
    
}

bool Enemy::init()
{
    if (BulletGenerator::init())
    {
        initialize();
        return true;
    }
    return false;
}

void Enemy::initialize()
{
    
}

// public func...
void Enemy::setEnemyInfo(EnemyInfo info)
{
    m_enemyInfo = info;
    setSprite();
    setEnemyBehavior();
}

void Enemy::setDanmaku(Danmaku* danmaku)
{
    m_danmaku = danmaku;
}

// private func...
void Enemy::setSprite()
{
    TextureType txrType = m_enemyInfo.TxrID;
    if (txrType == TXR_BLUE_SOUL) {
//        ret = Sprite::create("");
    }
}

void Enemy::setEnemyBehavior()
{
    
}





