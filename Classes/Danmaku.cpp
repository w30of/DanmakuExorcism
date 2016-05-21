//
//
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-16.
//
//

#include "Danmaku.h"
#include "GameLogic.h"

using namespace std;

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
    else if (_danmakuType == DANMAKU_ENEMY_1_4)
    {
        schedule(schedule_selector(Danmaku::danmaku_1_4), _interval, _count, 0);
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_5)
    {
        schedule(schedule_selector(Danmaku::danmaku_1_5), _interval, _count, 0);
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_6)
    {
        schedule(schedule_selector(Danmaku::danmaku_1_6), _interval, _count, 0);
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_7 || _danmakuType == DANMAKU_ENEMY_1_8)
    {
        if (_schOffset < 1) {
            schedule(schedule_selector(Danmaku::danmaku_1_7), _interval, _count, 0);
        } else {
            int startAngle;
            if (_danmakuType == DANMAKU_ENEMY_1_8) {
                startAngle = 100;
            } else {
                startAngle = -80;
            }
            for (int i = 0; i < 9; ++i) {   
                GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, _pOwner->getPosition(), 200, startAngle+i*20);
            }
        }
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_9)
    {
        schedule(schedule_selector(Danmaku::danmaku_1_9), _interval, _count, 0);
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_11)
    {
        schedule(schedule_selector(Danmaku::danmaku_1_11), _interval, _count, 0);
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_12)
    {
        schedule(schedule_selector(Danmaku::danmaku_1_12), _interval, _count, 0);
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_13)
    {
        danmaku_1_13(0);
        this->runAction(Sequence::create(DelayTime::create(2),
                                         CallFunc::create([=]{
            schedule(schedule_selector(Danmaku::danmaku_1_13), _interval, _count, 0);
        }),
                                         NULL));
    }
    else if (_danmakuType == DANMAKU_ENEMY_1_14)
    {
        schedule(schedule_selector(Danmaku::danmaku_1_14), _interval, _count, 0);
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
        Bullet* blt = GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 600, _schOffset*17+i*120, 0.01, 0, -50);
        blt->setShouldRotate(false);
        std::function<void()> funcChangeV = [=](){
            blt->setVelocityLimit(400);
            blt->setVelocityOffset(20);
        };
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
    for (int i = 0; i < 5; ++i) {
        GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 600+i*80, angle, 300, 0, -20);
    }
}
void Danmaku::danmaku_1_5(float dt)
{
    //Prepare...
    Vec2 startPos = _pOwner->getPosition();
    float angle = GameLogic::getAngleToPlayer(startPos);
    // Create bullets...
    for (int i = 0; i < 3; ++i) {
        Bullet* blt = GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 800, angle+20*(i-1), 100, 0, -120);
        blt->runAction(Sequence::create(DelayTime::create(1),
                                        CallFunc::create([=](){
                                                                 blt->setVelocityOffset(10);
                                                                 blt->setVelocityLimit(300);
                                                              }),
                                        NULL));
    }
}

void Danmaku::danmaku_1_6(float dt)
{
    // Prepare...
    Vec2 startPos = _pOwner->getPosition();
    float angle = -70;
    // Shoot...
    int count = 7;
    for (int i = 0; i < count; ++i) {
        GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 250, (angle - count/2*15)+i*15);
    }
    
    ++_schOffset;
}

void Danmaku::danmaku_1_7(float dt)
{
    // Prepare...
    Vec2 startPos = _pOwner->getPosition();
    float angle = GameLogic::getAngleToPlayer(startPos);
    // Shoot...
    GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 420-40*_schOffset, angle);
    ++_schOffset;
}

//void Danmaku::danmaku_1_8(float dt)
//{
//    // Prepare...
//    Vec2 startPos = _pOwner->getPosition();
//    float agl = GameLogic::getAngleToPlayer(startPos) + random(-10, 10);
//    // Shoot...
//    /* Fission bullet example */
//    
//    ++_schOffset;
//}

void Danmaku::danmaku_1_9(float dt) {
    // Prepare...
    Vec2 startPos = _pOwner->getPosition();
    float agl = GameLogic::getAngleToPlayer(startPos) + random(-20, 20);
    // Shoot...
    Bullet* blt = GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 600, agl, 5, 0, -50);
    blt->setShouldRotate(false);
    blt->runAction(Sequence::create(DelayTime::create(1),
                                    CallFunc::create([=]() {
        BulletInfo bi = blt->getBulletInfo();
        blt->setAngle(bi.a+17);
        blt->setVelocity(600);
        blt->setVelocityLimit(200);
        blt->setVelocityOffset(80);
        blt->updateRotate(true);
        GameLogic::setBullet(ENEMY_BULLET, bi.BulletID, blt->getPosition(), 600, bi.a-17, 300, 0, 80);
    }),
    NULL));
}

void Danmaku::danmaku_1_11(float dt) {
    // Prepare...
    Vec2 startPos = _pOwner->getPosition();
    float angle = -110;
    // Shoot...
    int count = 7;
    for (int i = 0; i < count; ++i) {
        GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 250, (angle - count/2*15)+i*15);
    }
    
    ++_schOffset;
}

void Danmaku::danmaku_1_12(float dt) {
    // Prepare...
    Vec2 startPos = _pOwner->getPosition();
    // Shoot...
    for (int i = 0; i < 12; ++i) {
        Bullet* blt = GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, startPos, 600, i*30+_schOffset*13, 200, 0, -50);
        blt->setShouldRotate(false);
    }
    ++_schOffset;
}

void Danmaku::danmaku_1_13(float dt)
{
    Sprite* spBlade = Sprite::create("bullets/blade.png");
    spBlade->setOpacity(0);
    GameLogic::getInstance()->gLayer->addChild(spBlade,999);
    spBlade->setPosition(_pOwner->getPosition() + Vec2(0, -100));
    spBlade->runAction(Sequence::create(FadeTo::create(0.1f, 255),
                                        DelayTime::create(0.4f),
                                        FadeTo::create(2, 0),
                                        CallFunc::create([=](){  spBlade->removeFromParent();  }),
                                        NULL));
    vector<Vec2> v_points;
    int off = _schOffset%2 == 0 ? 1 : -1;
    if (off < 0) spBlade->setScaleX(-1);
    v_points.push_back(Vec2(off*-149,147));
    v_points.push_back(Vec2(off*-133,90));
    v_points.push_back(Vec2(off*-113,43));
    v_points.push_back(Vec2(off*-88,4));
    v_points.push_back(Vec2(off*-52,-35));
    v_points.push_back(Vec2(off*-4,-74));
    v_points.push_back(Vec2(off*45,-107));
    v_points.push_back(Vec2(off*93,-130));
    v_points.push_back(Vec2(off*142,-146));
    
    int count = 30;
    size_t len = v_points.size();
    for (size_t i = 0; i < len; ++i) {
        Vec2 pos = v_points.at(i);
        for (int j = 0; j < count; ++j) {
            this->runAction(Sequence::create(DelayTime::create(0.03f*i),
                                             CallFunc::create([=](){
                GameLogic::setBullet(ENEMY_BULLET, BULLET_ENEMY_RED_1, pos + spBlade->getPosition(), 800, 360/count*j, 200+i*15, 0, -80);
            }),
                                             NULL));
        }
    }
    ++_schOffset;
}

void Danmaku::danmaku_1_14(float dt)
{
    
}








