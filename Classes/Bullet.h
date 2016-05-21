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
#include "Protocol.h"

class Bullet : public BulletGenerator
{
public:
    CREATE_FUNC(Bullet);
    
    // will add bullet to danmaku pool
    void setBulletInfo(BulletInfo bltInfo);
    BulletInfo getBulletInfo();
    
    void resetInfo();
    void defaultInfo();
    
    // setters...
    void setBulletID(BulletType bltId){ m_bltInfo.BulletID = bltId; };
    void setVelocity(float v){ m_bltInfo.v = v; };
    void setVelocityOffset(float vOff){ m_bltInfo.vOff = vOff; };
    void setVelocityOffsetEx(float vOffEx){ m_bltInfo.vExOff = vOffEx; };
    void setVelocityLimit(float vLimit){ m_bltInfo.vLimit = vLimit; };
    void setAngle(float a);
    void setAngleOffset(float aOff){ m_bltInfo.aOff = aOff; };
    void setAngleOffsetEx(float aOffEx){ m_bltInfo.aExOff = aOffEx; };
    void setAngleLimit(float aLimit){ m_bltInfo.aLimit = aLimit; };
    
    void updateRotate(bool forceToDo = false);
    
    CC_SYNTHESIZE(bool, shouldRotate, ShouldRotate);
    CC_SYNTHESIZE(bool, damage, Damage);
    
    // enable to show and move, disable to stop and hide
    void bulletEnable();
    void bulletDisable();
    void bulletDisappear();
    
protected:
    Bullet();
    virtual ~Bullet();
    virtual bool init() override;
private:
    void initialize();
    void move(float dt);
    void setTextureByBulletType(BulletType type);       // create texture by bullet type and put it into danmaku pool
    
    // inner funcs...
    void updateV();
    void checkCollide();
    Rect getBulletRect(Vec2 pos);
    
    // property...
    BulletInfo m_bltInfo;
    Sprite* m_sprite;
    
    bool m_bInPool;
    int m_collideRadius;
    Vec2 m_v; // Position offset of every frames
    Vec2 m_lastPos;
    Vec2 m_velocity;
    Size m_bulletSize;
    
    CC_SYNTHESIZE(bool, _isBulletEnable, BulletEnable);
};

#endif /* defined(__DanmakuExorcism__Bullet__) */
