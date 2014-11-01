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
    void setDanmaku(Danmaku* danmaku);
    
private:
    Enemy();
    virtual ~Enemy();
    virtual bool init() override;
    
    void initialize();
    
    EnemyInfo m_enemyInfo;
    Danmaku* m_danmaku;
    
    void setSprite();
    void setEnemyBehavior();
};

#endif /* defined(__DanmakuExorcism__Enemy__) */