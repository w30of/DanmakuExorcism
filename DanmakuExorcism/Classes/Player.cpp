//
//  Player.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-24.
//
//

#include "Player.h"
#include "Bullet.h"
#include "GameLogic.h"

Player::Player()
{
    _playerType = PLAYER_DAOSHI;
    _HP = 0;
    _isShoot = true;
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
    for (int i = 0; i < 20; ++i) {
        Bullet* playerBlt = Bullet::create();
        playerBlt->setBulletInfo(BULLET_DAOSHI_A, 90, 2000);
        playerBlt->bulletDisable();
        GameLogic::addPlayerBullet(playerBlt);
    }
    schedule(schedule_selector(Player::updateBullets), 0.05f);
}

// public :

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

void Player::shoot(bool isShoot)
{
    _isShoot = isShoot;
}

// private :

void Player::updateBullets(float dt)
{
    if (_isShoot) {
        int bulletNum  = 0;
        for (auto e : DanmakuPool::getInstance()->v_playerBullet) {
            if (e) {
                if (bulletNum > 1) {
                    break;
                }
                Bullet* blt = (Bullet*)e;
                if (!blt->getBulletEnable()) {
                    blt->setPosition(this->getPosition() + Vec2(bulletNum * 20 - 10, 0));
                    blt->bulletEnable();
                    ++bulletNum;
                }
            }
        }
        for (; bulletNum < 2; ++bulletNum) {
            Bullet* playerBlt = Bullet::create();
            playerBlt->setBulletInfo(BULLET_DAOSHI_A, 90, 2000);
            playerBlt->bulletEnable();
            playerBlt->setPosition(this->getPosition() + Vec2(bulletNum * 20 - 10, 0));
            GameLogic::addPlayerBullet(playerBlt);
        }
    }
}





