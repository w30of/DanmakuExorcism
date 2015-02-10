//
//  Danmaku.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-16.
//
//

#ifndef __DanmakuExorcism__Danmaku__
#define __DanmakuExorcism__Danmaku__

#include "cocos2d.h"
#include "Protocol.h"
#include "BulletGenerator.h"

class Danmaku : public Node
{
public:
    CREATE_FUNC(Danmaku);
    CC_SYNTHESIZE(Node*, _pOwner, Owner);
    CC_SYNTHESIZE(DanmakuType, _danmakuType, DanmakuType);
    CC_SYNTHESIZE(float, _delay, Delay);
    CC_SYNTHESIZE(int, _count, Count);
    CC_SYNTHESIZE(float, _interval, Interval);
    
    void run();
    void stop();
    
private:
    Danmaku();
    virtual ~Danmaku();
    // Members
    int _schOffset;
    short _schExtOffset;
    
    // Private funcs...
    virtual bool init() override;
    void initialize();
    void showDanmaku();
    
    // Danmakus...
    // Stage 1
    void danmaku_1_1(float dt);
};

#endif /* defined(__DanmakuExorcism__Danmaku__) */
