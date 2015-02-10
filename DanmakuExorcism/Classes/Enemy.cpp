//
//  Enemy.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-16.
//
//

#include "Enemy.h"
#include "DanmakuPool.h"
#include "GameLogic.h"

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
    m_danmaku = Danmaku::create();
    m_danmaku->setOwner(this);
    this->addChild(m_danmaku);
    setBulletGeneratorType(BulletGeneratorType::ENEMY);
}

// public func...
void Enemy::setEnemyInfo(EnemyInfo info)
{
    m_enemyInfo = info;
    // Init texture
    setSprite();
    // Enemy behavior hard code
    setEnemyBehavior();
    DanmakuPool::getInstance()->push(this);
    // Show danmaku of enemy
    setDanmaku();
}

EnemyInfo Enemy::getEnemyInfo()
{
    return m_enemyInfo;
}

void Enemy::setDanmaku()
{
    m_danmaku->setDanmakuType(m_enemyInfo.DmkID);
    m_danmaku->setDelay(m_enemyInfo.ShootDelay);
    m_danmaku->setCount(m_enemyInfo.ShootCount);
    m_danmaku->setInterval(m_enemyInfo.ShootInterval);
    m_danmaku->run();
}

void Enemy::die()
{
    m_danmaku->stop();
}


// private func...
void Enemy::setSprite()
{
    // Set texture
    TextureType txrType = m_enemyInfo.TxrID;
    if (txrType == TXR_BLUE_SOUL) {
        _sp = Sprite::create("playertest.png");
    }
    this->addChild(_sp, 0);
    this->setContentSize(_sp->getContentSize());
}

void Enemy::setEnemyBehavior()
{
    Size contentSize = this->getContentSize();
    if (m_enemyInfo.EnemyID == ENEMY_1_1) {
        
        this->setPosition(Vec2(-contentSize.width, m_enemyInfo.ShowPos.y));
        this->runAction(Sequence::create(EaseExponentialOut::create(MoveTo::create(0.5f, m_enemyInfo.ShowPos)),
//                                         MoveTo::create(6, Vec2(GameLogic::getInstance()->winSize.width + this->getContentSize().width, m_enemyInfo.ShowPos.y)),
                                         NULL));
    }
}





