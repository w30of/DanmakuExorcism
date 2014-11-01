//
//  Danmaku.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-16.
//
//

#include "Danmaku.h"

Danmaku::Danmaku()
{
    
}

Danmaku::~Danmaku()
{
    
}

bool Danmaku::init()
{
    if (Node::init())
    {
        initialize();
        return true;
    }
    return false;
}

void Danmaku::setDanmakuOwner(cocos2d::Node *pOwner)
{
    m_pOwner = pOwner;
}

void Danmaku::initialize()
{
    
}