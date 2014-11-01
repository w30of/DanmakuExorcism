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
    void setDanmakuOwner(Node* pOwner);
    
private:
    Danmaku();
    virtual ~Danmaku();
    virtual bool init() override;
    
    void initialize();
    
    Node* m_pOwner;
};

#endif /* defined(__DanmakuExorcism__Danmaku__) */
