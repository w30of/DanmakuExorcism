//
//  GamingLayer.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-6-25.
//
//

#include "GamingLayer.h"

GamingLayer::GamingLayer()
{
    
}

GamingLayer::~GamingLayer()
{
    
}

bool GamingLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    prepare();
    return true;
}

void GamingLayer::prepare()
{
    this->setContentSize(Size(640, 960));
    
    m_WinSize = this->getContentSize();
    
    auto sprite = Sprite::create("HelloWorld.png");
    
    sprite->setPosition(Vec2(m_WinSize.width/2, m_WinSize.height/2));
    // to show the border of visible size
    sprite->setScale(m_WinSize.width / sprite->getContentSize().width, m_WinSize.height / sprite->getContentSize().height);
    
    this->addChild(sprite, 0);
}