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
    // These will help you...
    Size contentSize = this->getContentSize();
    Size winSize = GameLogic::getInstance()->winSize;
    Action *shoot = CallFunc::create([=](){  this->m_danmaku->run();  });
    Action *remove = CallFunc::create([=](){  this->removeFromParent();  });
    
    // Now, enemy will trying tu kill you...
    /* Stage 1: initShot */
    if (m_enemyInfo.EnemyID == ENEMY_1_1 || m_enemyInfo.EnemyID == ENEMY_1_2)
    {
        // Prepare...
        Vec2 startPos;
        if (m_enemyInfo.EnemyID == ENEMY_1_1) {
            startPos = Vec2(winSize.width + contentSize.width, winSize.height * 0.875);
        } else {
            startPos = Vec2(-contentSize.width, winSize.height * 0.875);
        }
        
        this->setPosition(startPos);
        
        Vec2 bcEndPos = m_enemyInfo.ShowPos;
        ccBezierConfig bc;
        bc.controlPoint_1 = Vec2(startPos.x - (startPos.x - bcEndPos.x)/2, startPos.y);
        bc.controlPoint_2 = Vec2(bcEndPos.x, (startPos.y - bcEndPos.y)/2 + bcEndPos.y);
        bc.endPosition = bcEndPos;
        
        int endPosX = m_enemyInfo.ShowPos.x;;
        if (m_enemyInfo.EnemyID == ENEMY_1_1) {
            endPosX -= 30*(3-m_enemyInfo.ShowCount);
        } else {
            endPosX += 30*(3-m_enemyInfo.ShowCount);
        }
        
        // Show...
        this->runAction(Sequence::create(EaseSineOut::create(BezierTo::create(1, bc)),
                                         shoot,
                                         MoveBy::create(1, Vec2(0, -50)),
                                         EaseSineIn::create(MoveTo::create(2, Vec2(endPosX, -contentSize.height))),
                                         remove,
                                         NULL));
    }
    else if (m_enemyInfo.EnemyID == ENEMY_1_3)
    {
        // Prepare...
        Vec2 startPos = Vec2(winSize.width/2, contentSize.height + winSize.height);
        Vec2 endPos = Vec2(winSize.width/2, -contentSize.height);
        
        this->setPosition(startPos);
        
        // Show...
        this->runAction(Sequence::create(EaseSineOut::create(MoveTo::create(1, m_enemyInfo.ShowPos)),
                                         shoot,
                                         DelayTime::create(1),
                                         EaseSineIn::create(MoveTo::create(2, endPos)),
                                         remove,
                                         NULL));
    }
    else if (m_enemyInfo.EnemyID == ENEMY_1_4 || m_enemyInfo.EnemyID == ENEMY_1_5)
    {
        // Prepare...
        Vec2 startPos;
        Vec2 endPos;
        Vec2 endPos1;
        ccBezierConfig bc;
        if (m_enemyInfo.EnemyID == ENEMY_1_4) {
            startPos = Vec2(winSize.width + contentSize.width, m_enemyInfo.ShowPos.y);
            endPos = Vec2(winSize.width - contentSize.width/2, m_enemyInfo.ShowPos.y - 150);
            endPos1 = Vec2(winSize.width + contentSize.width, m_enemyInfo.ShowPos.y - 150);
            
            Vec2 offset = Vec2(winSize.width - m_enemyInfo.ShowPos.x, startPos.y - endPos.y);
            bc.controlPoint_1 = Vec2(m_enemyInfo.ShowPos.x, endPos.y + offset.y/2);
            bc.controlPoint_2 = Vec2(winSize.width - offset.x/2, endPos.y);
            bc.endPosition = endPos;
        } else {
            startPos = Vec2(-contentSize.width, m_enemyInfo.ShowPos.y);
            endPos = Vec2(contentSize.width/2, m_enemyInfo.ShowPos.y - 150);
            endPos1 = Vec2(-contentSize.width, m_enemyInfo.ShowPos.y - 150);
            
            Vec2 offset = Vec2(m_enemyInfo.ShowPos.x, startPos.y - endPos.y);
            bc.controlPoint_1 = Vec2(m_enemyInfo.ShowPos.x, endPos.y + offset.y/2);
            bc.controlPoint_2 = Vec2(offset.x/2, endPos.y);
            bc.endPosition = endPos;
        }
        
        
        
        
        this->setPosition(startPos);
        // Show...
        this->runAction(Sequence::create(DelayTime::create(0.1),
                                         shoot,
                                         EaseSineOut::create(MoveTo::create(1, m_enemyInfo.ShowPos)),
                                         DelayTime::create(0.3),
                                         EaseExponentialIn::create(BezierTo::create(1.8, bc)),
                                         CallFunc::create([=](){  this->m_danmaku->run();  }),
                                         MoveTo::create(0.2, endPos1),
                                         remove,
                                         NULL));
    }
    else if (m_enemyInfo.EnemyID == ENEMY_1_6)
    {
        // Prepare...
        Vec2 startPos = Vec2(winSize.width + contentSize.width, winSize.height / 2);
        this->setPosition(startPos);
        ccBezierConfig bc;
        bc.endPosition = Vec2(-contentSize.width/2, m_enemyInfo.ShowPos.y);
        bc.controlPoint_1 = Vec2(startPos.x, (startPos.y + bc.endPosition.y)/2);
        bc.controlPoint_2 = Vec2(winSize.width / 2, bc.endPosition.y);
        
        // Show...
        this->runAction(Sequence::create(Spawn::create(BezierTo::create(2, bc),
                                                       Sequence::create(DelayTime::create(2-m_enemyInfo.ShowCount*0.2),
                                                                        shoot,
                                                                        NULL),
                                                       NULL),
                                         remove,
                                         NULL));
    }
    else if (m_enemyInfo.EnemyID == ENEMY_1_7)
    {
        // Show...
        this->setPosition(m_enemyInfo.ShowPos);
        this->runAction(Sequence::create(Spawn::create(MoveBy::create(3, Vec2(0, 20)),
                                                       shoot,
                                                       NULL),
                                         remove,
                                         NULL));
    }
    else if (m_enemyInfo.EnemyID == ENEMY_1_8)
    {
        // Prepare...
        Vec2 startPos = Vec2(winSize.width * 0.6, winSize.height + contentSize.height);
        ccBezierConfig bc;
        bc.endPosition = Vec2(-contentSize.width, m_enemyInfo.ShowPos.y);
        Vec2 offset = Vec2(startPos.x, startPos.y - bc.endPosition.y);
        bc.controlPoint_1 = Vec2(startPos.x, bc.endPosition.y + offset.y/2);
        bc.controlPoint_2 = Vec2(bc.endPosition.x + offset.x / 2, bc.endPosition.y);
        // Show...
        this->setPosition(startPos);
        this->runAction(Spawn::create(EaseSineIn::create(BezierTo::create(2.6f, bc)),
                                      Sequence::create(DelayTime::create(0.5),
                                                       shoot,
                                                       DelayTime::create(2.1f),
                                                       remove,
                                                       NULL),
                                      NULL));
    }
    
    /* Stage 1: watchDog */
    /* Stage 1: dangerClose */
    /* Stage 1: BOSS */
}



