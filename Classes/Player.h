//
//  Player.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-24.
//
//

#ifndef __DanmakuExorcism__Player__
#define __DanmakuExorcism__Player__

#include "BulletGenerator.h"
#include "DanmakuPool.h"
#include "Protocol.h"
USING_NS_CC;

typedef enum
{
    PLAYER_DAOSHI  = 0,
    PLAYER_HESHANG = 1,
    PLAYER_JIANKE  = 2,
}PlayerType;

struct PlayerInfo{
    PlayerType pType;
    std::string pName;
    std::string picName;
    std::string pDesc;
};

class Player : public BulletGenerator
{
public:
    CREATE_FUNC(Player);
    void setPlayerInfo(PlayerType type, int hp);
    void setContainerSize(Size s);
    void shoot(bool isShoot);
    void move(Touch* touch);
    void idle();
    void die();
    
protected:
    Player();
    virtual ~Player();
    virtual bool init() override;
private:
    void initialize();
    void updateBullets(float dt);
    void moveAnimate(Direction dir);
    void checkCollidEnemy();
    
    PlayerType _playerType;
    CC_SYNTHESIZE(int, _HP, HP);
    Sprite* _sp;
    Size _containerSize;
    bool _isShoot;
    bool _hasInit;
    Animation* _aniIdle;
    Animation* _aniSide;
    Direction _dir;
};

#endif /* defined(__DanmakuExorcism__Player__) */
