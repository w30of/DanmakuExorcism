//
//  BulletGenerator.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-22.
//
//

#include "BulletGenerator.h"

BulletGenerator::BulletGenerator()
{
    
}

BulletGenerator::~BulletGenerator()
{
    
}

bool BulletGenerator::init()
{
    if (Node::init())
    {
        initialize();
        return true;
    }
    return false;
}

void BulletGenerator::initialize()
{
    
}