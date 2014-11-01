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
#include "Protocol.h"
USING_NS_CC;

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
