//
//  Bullet.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-23.
//
//

#include "Bullet.h"

Bullet::Bullet()
{
    m_sprite = nullptr;
    _isBulletEnable = false;
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
    
}

void Bullet::setBulletInfo(BulletType bulletType, float angle, float velocityLength)
{
    _velocityLength = velocityLength;
    
    _angle = CC_DEGREES_TO_RADIANS(angle);
    m_velocity = Vec2::forAngle(_angle);
    m_velocity.normalize();
    
    setBulletType(bulletType);
    setTextureByBulletType(bulletType);
}

void Bullet::setBulletInfo(BulletType bulletType, Vec2 angle, float velocityLength)
{
    _velocityLength = velocityLength;
    
    m_velocity = angle.getNormalized();
    
    setBulletType(bulletType);
    setTextureByBulletType(bulletType);
}

void Bullet::bulletEnable()
{
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

void Bullet::setTextureByBulletType(BulletType type)
{
    // set texture by type
    // there are lots of bullet types
    if (type == BULLET_DAOSHI_A) {
        m_sprite = Sprite::create("bullettest.png");
    }
    this->addChild(m_sprite);
    this->setBulletGeneratorType(PLAYER_BULLET);
    DanmakuPool::getInstance()->push(this);
}

void Bullet::move(float dt)
{
    float realVLength = _velocityLength * dt;
    
    this->setPosition(this->getPosition() + (m_velocity * realVLength));
    
    Rect screen = Rect(0, 0, 640, 960);
    if (!screen.containsPoint(this->getPosition())) {
        this->bulletDisable();
    }
}









