//
//  GamingLayer.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-6-25.
//
//

#ifndef __DanmakuExorcism__GamingLayer__
#define __DanmakuExorcism__GamingLayer__

#include "cocos2d.h"
USING_NS_CC;

class GamingLayer : public Layer
{
public:
    GamingLayer();
    virtual ~GamingLayer();
    virtual bool init();
    CREATE_FUNC(GamingLayer);
private:
    void prepare();
    
    // members
    Size m_WinSize;
};

#endif /* defined(__DanmakuExorcism__GamingLayer__) */
