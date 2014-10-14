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
USING_NS_CC;

typedef enum
{
    PLAYER_DAOSHI  = 0,
    PLAYER_HESHANG = 1,
    PLAYER_JIANKE  = 2,
}PlayerType;

class Player : public BulletGenerator
{
public:
    CREATE_FUNC(Player);
    void setPlayerInfo(PlayerType type, int hp);
    void shoot(bool isShoot);
    
protected:
    Player();
    virtual ~Player();
    virtual bool init() override;
private:
    void initialize();
    
    PlayerType _playerType;
    CC_SYNTHESIZE(int, _HP, HP);
};

#endif /* defined(__DanmakuExorcism__Player__) */
