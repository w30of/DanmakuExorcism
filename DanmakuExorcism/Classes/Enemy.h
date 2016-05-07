//
//  Enemy.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-16.
//
//

#ifndef __DanmakuExorcism__Enemy__
#define __DanmakuExorcism__Enemy__

#include "cocos2d.h"
#include "Protocol.h"
#include "BulletGenerator.h"
#include "Danmaku.h"

class Enemy : public BulletGenerator
{
public:
    CREATE_FUNC(Enemy);
    
    void setEnemyInfo(EnemyInfo info);
    EnemyInfo getEnemyInfo();
    void die();
    void disappear();
    void shoot();
    void stopShoot();
    Vec2 getShowPos();
    Rect getEnemyRect(bool isHalf = false);
    
private:
    Enemy();
    virtual ~Enemy();
    virtual bool init() override;
    
    void initialize();
    
    EnemyInfo m_enemyInfo;
    Danmaku* m_danmaku;
    Sprite* _sp;
    Size m_enemySize;
    
    void setSprite();
    void setEnemyBehavior();
    void setDanmaku();
    void removeFromPool();
    void runW3ScriptActions(std::string w3s);
};

#endif /* defined(__DanmakuExorcism__Enemy__) */