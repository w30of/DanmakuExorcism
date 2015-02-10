//
//  Danmaku.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-16.
//
//

#include "Danmaku.h"
#include "GameLogic.h"

Danmaku::Danmaku()
: _pOwner(nullptr)
, _danmakuType(DANMAKU_NONE)
, _delay(0)
, _count(0)
, _schOffset(0)
, _schExtOffset(0)
{
    
}

Danmaku::~Danmaku()
{
    
}

bool Danmaku::init()
{
    if (Node::init())
    {
        initialize();
        return true;
    }
    return false;
}

void Danmaku::initialize()
{
    
}

// public funcs
void Danmaku::run()
{
    if (_delay > 0) {
        this->runAction(Sequence::create(DelayTime::create(_delay),
                                         CallFunc::create([=]{ showDanmaku(); }),
                                         NULL));
    } else {
    }
}

void Danmaku::showDanmaku()
{
    if (_danmakuType == DANMAKU_ENEMY_1_1)
    {
        _schExtOffset = 1;
        schedule(schedule_selector(Danmaku::danmaku_1_1), 0.04);
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_2)
    {
        // Bullet to player
        // Get angle to player
        Vec2 tarPos = GameLogic::getInstance()->gPlayer->getPosition();
        Vec2 startPos = _pOwner->getPosition();
        Vec2 dir = tarPos - startPos;
        float a = dir.getAngle();
        
        Bullet* blt = Bullet::create();
        blt->setPosition(startPos);
        BulletInfo bi;
        GameLogic::defaultBltInfo(bi);
        bi.BulletID = BULLET_ENEMY_RED_1;
        bi.v = 500;
        bi.a = CC_RADIANS_TO_DEGREES(a);
        blt->setBulletInfo(bi);
        blt->bulletEnable();
        GameLogic::addPlayerBullet(blt);
    }
}

void Danmaku::stop()
{
    this->stopAllActions();
    this->unscheduleAllCallbacks();
}





// Danmakus...
void Danmaku::danmaku_1_1(float dt)
{
//    Vec2 playerPos = GameLogic::getInstance()->gPlayer->getPosition();
    Vec2 startPos = _pOwner->getPosition();
//    Vec2 dir = playerPos - startPos;
//    float a = dir.getAngle();
    for (int i = 0; i < 4; ++i) {
        Bullet* blt = (Bullet*)DanmakuPool::getInstance()->getEnemyBullet();
        blt->setBulletID(BULLET_ENEMY_RED_1);
        blt->setVelocity(400);
        blt->setVelocityOffset(-20);
        blt->setVelocityOffsetEx(1);
        blt->setVelocityLimit(100);
        blt->setAngle((_schOffset*13) + 90*i);
        blt->resetInfo();
        blt->setPosition(startPos);
        blt->bulletEnable();
    }
    
//    if (_schOffset > 128) _schExtOffset = -1;
//    else if (_schOffset < 0) _schExtOffset = 1;
    _schOffset += _schExtOffset;
}





