//
//  Player.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-24.
//
//

#include "Player.h"

Player::Player()
{
    _playerType = PLAYER_DAOSHI;
    _HP = 0;
}

Player::~Player()
{
    
}

bool Player::init()
{
    if (BulletGenerator::init())
    {
        initialize();
        return true;
    }
    return false;
}

void Player::initialize()
{
    setBulletGeneratorType(PLAYER);
}

void Player::setPlayerInfo(PlayerType type, int hp)
{
    // set type
    _playerType = type;
    _HP = hp;
    
    // set texture by type
    if (type == PLAYER_DAOSHI)
    {
        Sprite* sprPlayer = Sprite::create("playertest.png");
        this->addChild(sprPlayer, 0);
        this->setContentSize(sprPlayer->getContentSize());
    }
    else if (type == PLAYER_HESHANG)
    {
        Sprite* sprPlayer = Sprite::create("playertest.png");
        this->addChild(sprPlayer, 0);
        this->setContentSize(sprPlayer->getContentSize());
    }
    else if (type == PLAYER_JIANKE)
    {
        Sprite* sprPlayer = Sprite::create("playertest.png");
        this->addChild(sprPlayer, 0);
        this->setContentSize(sprPlayer->getContentSize());
    }
    
    DanmakuPool::getInstance()->push(this);
}






