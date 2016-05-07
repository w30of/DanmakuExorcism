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
    CC_SYNTHESIZE(float, _delay, Delay);
    CC_SYNTHESIZE(int, _count, Count);
    CC_SYNTHESIZE(float, _interval, Interval);
    void setDanmakuType(DanmakuType type);
    
    void run();
    void stop();
    
private:
    Danmaku();
    virtual ~Danmaku();
    /* Members */
    DanmakuType _danmakuType;
    // increment
    int _schOffset;
    short _schExtOffset;
    // for save sth
    float _floatStay;
    
    /* Private funcs */
    virtual bool init() override;
    void initialize();
    void showDanmaku();
    
    /* Danmakus */
    // Stage 1
    void danmaku_1_1(float dt);
    void danmaku_1_3(float dt);
    void danmaku_1_4(float dt);
    void danmaku_1_5(float dt);
    void danmaku_1_6(float dt);
    void danmaku_1_7(float dt);
    //    void danmaku_1_8(float dt);
    void danmaku_1_9(float dt);
    void danmaku_1_11(float dt);
    void danmaku_1_12(float dt);
    void danmaku_1_13(float dt);
};

#endif /* defined(__DanmakuExorcism__Danmaku__) */
