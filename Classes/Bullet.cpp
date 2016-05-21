//
//  Bullet.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-23.
//
//

#include "Bullet.h"
#include "GameLogic.h"

using namespace std;

Bullet::Bullet()
{
    m_sprite = nullptr;
    _isBulletEnable = false;
    m_bInPool = false;
    
    damage = 0;
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
    setVisible(true);
    this->schedule(schedule_selector(Bullet::move));
}

void Bullet::bulletDisable()
{
    setBulletEnable(false);
    this->setVisible(false);
    unschedule(schedule_selector(Bullet::move));
}

void Bullet::bulletDisappear()
{
    // TODO: Bullet will not check to hit anyone
    m_sprite->runAction(Sequence::create(Spawn::create(FadeTo::create(0.3, 0),
                                                       ScaleTo::create(0.3, 1,2),
                                                       NULL),
                                         CallFunc::create([=](){  this->bulletDisable();  }),
                                         NULL));
}

void Bullet::setAngle(float a)
{
    m_bltInfo.a = a;
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
        strFileName = "bullets/daoshi_mian.png";
        setShouldRotate(true);
    } else if (type == BULLET_ENEMY_BLUE_1) {
        strFileName = "bullets/enemy_bullet_blue_1.png";
        setShouldRotate(false);
        m_collideRadius = 10;
    } else if (type == BULLET_ENEMY_RED_1) {
        strFileName = "bullets/enemy_bullet_red_1.png";
        setShouldRotate(true);
        m_collideRadius = 10;
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
    m_bulletSize = m_sprite->getContentSize();
}

void Bullet::updateV()
{
    if (m_bltInfo.vLimit) {
        if ((m_bltInfo.vOff > 0 && m_bltInfo.v >= m_bltInfo.vLimit) || (m_bltInfo.vOff < 0 && m_bltInfo.v <= m_bltInfo.vLimit)) {
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

void Bullet::updateRotate(bool forceToDo /* = false */)
{
    if (shouldRotate || forceToDo) {
        if (forceToDo) updateV();
        float a = m_v.getAngle();
        m_sprite->setRotation(-CC_RADIANS_TO_DEGREES(a));
    }
}

void Bullet::checkCollide()
{
    if (_bulletGeneratorType == PLAYER_BULLET)
    {
        vector<BulletGenerator*> v_enemys = DanmakuPool::getInstance()->v_enemy;
        size_t len = v_enemys.size();
        Vec2 bltPos = this->getPosition();
        for (size_t i = 0; i < len; ++i) {
            Enemy* enemy = (Enemy*)v_enemys.at(i);
            if (enemy->getEnemyRect().intersectsRect(getBulletRect(this->getPosition()))) {
                // TODO: collide efx
                if ( enemy->hurt(getDamage()) )
                {
                    this->bulletDisable();
                }
                
            }
        }
    }
    else if (_bulletGeneratorType == ENEMY_BULLET)
    {
        Vec2 playerPos = GameLogic::getInstance()->gPlayer->getPosition();
        int dis = floorf(this->getPosition().distance(playerPos));
        if (dis < m_collideRadius + 10)
        {
            log("danger close!!!!!");
            if (dis < m_collideRadius) {
                // TODO: player dead
//                log("collide!!!!!");
            }
        }
    }
}

Rect Bullet::getBulletRect(Vec2 pos)
{
    return Rect(pos.x - m_bulletSize.width,
                pos.y - m_bulletSize.height,
                m_bulletSize.width,
                m_bulletSize.height);
}

void Bullet::move(float dt)
{
    m_lastPos = this->getPosition();
    this->setPosition(this->getPosition() + m_v * dt);
    
    checkCollide();
    
    updateV();
    updateRotate();
    
    Rect screen = GameLogic::getInstance()->gameRect;
    if (!screen.containsPoint(this->getPosition())) {
        this->bulletDisable();
    }
}









