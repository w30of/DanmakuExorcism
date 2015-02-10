//
//  Bullet.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-23.
//
//

#include "Bullet.h"
#include "GameLogic.h"

Bullet::Bullet()
{
    m_sprite = nullptr;
    _isBulletEnable = false;
    m_bInPool = false;
}

Bullet::~Bullet()
{
    
}

bool Bullet::init()
{
    if (BulletGenerator::init())
    {
        initialize();
        return true;
    }
    return false;
}

void Bullet::initialize()
{
    this->setVisible(false);
}

// public funcs...
void Bullet::setBulletInfo(BulletInfo bltInfo)
{
//    float agl = CC_DEGREES_TO_RADIANS(bltInfo.a);
    m_v = Vec2::forAngle(bltInfo.a).getNormalized();
    setTextureByBulletType(bltInfo.BulletID);
    m_bltInfo = bltInfo;
}

BulletInfo Bullet::getBulletInfo()
{
    return m_bltInfo;
}

void Bullet::resetInfo()
{
    setBulletInfo(m_bltInfo);
}

void Bullet::defaultInfo()
{
    GameLogic::defaultBltInfo(m_bltInfo);
}

void Bullet::bulletEnable()
{
    updateV();
    updateRotate();
    setBulletEnable(true);
    this->setVisible(true);
    schedule(schedule_selector(Bullet::move));
}

void Bullet::bulletDisable()
{
    setBulletEnable(false);
    this->setVisible(false);
    unschedule(schedule_selector(Bullet::move));
}







// private funcs...
void Bullet::setTextureByBulletType(BulletType type)
{
    // set texture by type
    // there are lots of bullet types
//    if (type == m_bltInfo.BulletID) {
//        return;
//    }
    std::string strFileName;
    if (type == BULLET_DAOSHI_A) {
        strFileName = "daoshi_mian.png";
        setShouldRotate(true);
    } else if (type == BULLET_ENEMY_BLUE_1) {
        strFileName = "enemy_bullet_blue_1.png";
        setShouldRotate(false);
    } else if (type == BULLET_ENEMY_RED_1) {
        strFileName = "enemy_bullet_red_1.png";
        setShouldRotate(true);
    }
    
    if (strFileName.empty()) {
        return;
    }
    
    if (!m_bInPool) {
        m_bInPool = true;
        m_sprite = Sprite::create(strFileName.c_str());
        this->addChild(m_sprite);
    } else {
        m_sprite->setTexture(strFileName.c_str());
    }
}

void Bullet::updateV()
{
    if (m_bltInfo.vLimit) {
        if ((m_bltInfo.vLimit > 0 && m_bltInfo.v >= m_bltInfo.vLimit) || (m_bltInfo.vLimit < 0 && m_bltInfo.v <= m_bltInfo.vLimit)) {
            m_bltInfo.v = m_bltInfo.vLimit;
        } else {
            if (m_bltInfo.vOff) {
                m_bltInfo.v += m_bltInfo.vOff;
            }
            if (m_bltInfo.vExOff) {
                m_bltInfo.vOff += m_bltInfo.vExOff;
            }
        }
    }
    
    if (m_bltInfo.aLimit) {
        if ((m_bltInfo.aLimit > 0 && m_bltInfo.a >= m_bltInfo.aLimit) || (m_bltInfo.aLimit < 0 && m_bltInfo.a <= m_bltInfo.aLimit)) {
            m_bltInfo.a = m_bltInfo.aLimit;
        } else {
            if (m_bltInfo.aOff) {
                m_bltInfo.a += m_bltInfo.aOff;
            }
            if (m_bltInfo.aExOff) {
                m_bltInfo.aOff += m_bltInfo.aExOff;
            }
        }
    }
    
    float agl = CC_DEGREES_TO_RADIANS(m_bltInfo.a);
    m_v = Vec2::forAngle(agl) * m_bltInfo.v;
}

void Bullet::updateRotate()
{
    if (shouldRotate) {
        float a = m_v.getAngle();
        m_sprite->setRotation(-CC_RADIANS_TO_DEGREES(a));
    }
}

void Bullet::move(float dt)
{
    this->setPosition(this->getPosition() + m_v * dt);
    
    updateV();
    updateRotate();
    
    Rect screen = GameLogic::getInstance()->gameRect;
    if (!screen.containsPoint(this->getPosition())) {
        this->bulletDisable();
    }
}









