//
//  BulletGenerator.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-22.
//
//

#ifndef __DanmakuExorcism__BulletGenerator__
#define __DanmakuExorcism__BulletGenerator__

#include "cocos2d.h"
USING_NS_CC;

typedef enum
{
    PLAYER_BULLET   = 0,
    ENEMY_BULLET   = 1,
    ENEMY    = 2,
    PLAYER   = 3
    
}BulletGeneratorType;

typedef enum
{
    BULLET_DAOSHI_A = 0,
    BULLET_BLUE = 1,
}BulletType;


class BulletGenerator : public Node
{
public:
    CREATE_FUNC(BulletGenerator);
    
protected:
    BulletGenerator();
    virtual ~BulletGenerator();
    virtual bool init() override;
    
private:
    void initialize();
    
    CC_SYNTHESIZE(BulletGeneratorType, _bulletGeneratorType, BulletGeneratorType);
    CC_SYNTHESIZE(BulletType, _bulletType, BulletType);
};

#endif /* defined(__DanmakuExorcism__BulletGenerator__) */
