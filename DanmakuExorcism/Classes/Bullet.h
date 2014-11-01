//
//  Bullet.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-23.
//
//

#ifndef __DanmakuExorcism__Bullet__
#define __DanmakuExorcism__Bullet__

#include "BulletGenerator.h"
#include "DanmakuPool.h"

class Bullet : public BulletGenerator
{
public:
    CREATE_FUNC(Bullet);
    
    // will add bullet to danmaku pool
    void setBulletInfo(BulletType bulletType, float angle, float velocityLength);
    void setBulletInfo(BulletType bulletType, Vec2 angle, float velocityLength);
    // enable to show and move, disable to stop and hide
    void bulletEnable();
    void bulletDisable();
    
protected:
    Bullet();
    virtual ~Bullet();
    virtual bool init() override;
private:
    void initialize();
    void move(float dt);
    void setTextureByBulletType(BulletType type);       // create texture by bullet type and put it into danmaku pool
    
    // property
    CC_SYNTHESIZE(Sprite*, _sprTexture, SprTexture);
    CC_SYNTHESIZE(float, _velocityLength, VelocityLength);
    CC_SYNTHESIZE(float, _angle, Angle);
    CC_SYNTHESIZE(float, _pointAngle, PointAngle);
    
    // offsets
    CC_SYNTHESIZE(float, _angleOffset, AngleOffset);
    CC_SYNTHESIZE(float, _angleLimit, AngleLimit);
    CC_SYNTHESIZE(float, _velocityOffset, VelocityOffset);
    CC_SYNTHESIZE(float, _velocityLimit, VelocityLimit);
    
    Vec2 m_velocity;
    Sprite* m_sprite;
    CC_SYNTHESIZE(bool, _isBulletEnable, BulletEnable);
};

#endif /* defined(__DanmakuExorcism__Bullet__) */
