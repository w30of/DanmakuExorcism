//
//
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
, _floatStay(0)
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
void Danmaku::setDanmakuType(DanmakuType type)
{
    _danmakuType = type;
    _delay = 0;
    _count = 0;
    _schOffset = 0;
    _schExtOffset = 0;
    _floatStay = 0;
}

void Danmaku::run()
{
    if (_delay > 0) {
        this->runAction(Sequence::create(DelayTime::create(_delay),
                                         CallFunc::create([=]{ showDanmaku(); }),
                                         NULL));
    } else {
        showDanmaku();
    }
}

void Danmaku::showDanmaku()
{
    if (_danmakuType == DANMAKU_ENEMY_1_1)
    {
        schedule(schedule_selector(Danmaku::danmaku_1_1), _interval, _count, 0);
        
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_3)
    {
        schedule(schedule_selector(Danmaku::danmaku_1_3), _interval, _count, 0);
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_4 || _danmakuType == DANMAKU_ENEMY_1_5)
    {
        if (_schOffset < 1) {
            schedule(schedule_selector(Danmaku::danmaku_1_4), _interval, _count, 0);
        } else {
            int startAngle;
            if (_danmakuType == DANMAKU_ENEMY_1_4) {
                startAngle = 100;
            } else {
                startAngle = -80;
            }
            for (int i = 0; i < 9; ++i) {
                GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, _pOwner->getPosition(), 200, startAngle+i*20);
            }
        }
        _schOffset = 1;
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_6)
    {
        Vec2 pos = _pOwner->getPosition();
        float agl = GameLogic::getAngleToPlayer(pos);
        for (int i = 0; i < 3; ++i) {
            GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, Vec2(pos.x + (-20 + i*20), pos.y), 200+ 30*i, agl + (-10 + i*10));
        }
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_7)
    {
        schedule(schedule_selector(Danmaku::danmaku_1_7), _interval, _count, 0);
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_8)
    {
        schedule(schedule_selector(Danmaku::danmaku_1_8), _interval, _count, 0);
    }
    
}

void Danmaku::stop()
{
    this->stopAllActions();
    this->unscheduleAllCallbacks();
}





// Danmakus...
/* Tips: _schOffset and _schExtOffset for make surprise! */
void Danmaku::danmaku_1_1(float dt)
{
    // Prepare...
    Vec2 startPos = _pOwner->getPosition();
    float angle = GameLogic::getAngleToPlayer(startPos);
    // Calc arguments...
    int count;
    if (_schOffset > 0) {
        count = 2;
        angle -= 10;
        _schOffset = 0;
    } else {
        count = 3;
        angle -= 20;
        ++_schOffset;
    }
    // Create bullets...
    for (int i = 0; i < count; ++i) {
        GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 300, angle + 20*i);
    }
}

void Danmaku::danmaku_1_3(float dt)
{
    // Prepare...
    Vec2 startPos = _pOwner->getPosition();
    // Create bullets...
    for (int i = 0; i < 3; ++i) {
        Bullet* blt = GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 600, _schOffset*17+i*120, 10, 0, -50);
        blt->setShouldRotate(false);
        std::function<void()> funcChangeV = [=](){
            blt->setVelocityLimit(400);
            blt->setVelocityOffset(20); };
        blt->runAction(Sequence::create(DelayTime::create(1),
                                        CallFunc::create(funcChangeV),
                                        NULL));
    }
    ++_schOffset;
}

void Danmaku::danmaku_1_4(float dt)
{
    // Prepare...
    Vec2 startPos = _pOwner->getPosition();
    float angle = GameLogic::getAngleToPlayer(startPos);
    // Create bullets...
    GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 400, angle);
}

void Danmaku::danmaku_1_7(float dt)
{
    // Prepare,,,
    Vec2 startPos = _pOwner->getPosition();
    float angle = GameLogic::getAngleToPlayer(startPos);
    // Shoot...
    float count = 10;
    if (_schOffset%2 == 0) {
        count = 9;
    }

    for (int i = 0; i < count; ++i) {
        GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 250+30*_schOffset, (angle - count/2*15)+i*15);
    }
    _schOffset++;
}

void Danmaku::danmaku_1_8(float dt)
{
    // Prepare...
    Vec2 startPos = _pOwner->getPosition();
    float agl = GameLogic::getAngleToPlayer(startPos);
    // Shoot...
    for (int i = 0; i < _schOffset + 1; ++i) {
        Bullet* blt = GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 600, (agl - _schOffset/2*15) + i*15, 2, 0, -40);
        blt->runAction(Sequence::create(DelayTime::create(1),
                                        CallFunc::create([=]()
                                                         {
                                                             BulletInfo bi = blt->getBulletInfo();
                                                             blt->setAngle(bi.a+13);
                                                             blt->setVelocityLimit(300);
                                                             blt->setVelocityOffset(50);
                                                             GameLogic::setBullet(ENEMY_BULLET, bi.BulletID, blt->getPosition(), 2, bi.a-13, 300, 0, 50);
                                                         }),
                                        NULL));
    }
    ++_schOffset;
}









