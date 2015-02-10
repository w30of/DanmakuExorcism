//
//  GameLogic.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-28.
//
//

#ifndef __DanmakuExorcism__GameLogic__
#define __DanmakuExorcism__GameLogic__

#include "cocos2d.h"
#include "Protocol.h"
#include "GamingLayer.h"
#include "Bullet.h"

class GameLogic
{
public:
    static GameLogic *getInstance();
    // public property
    Layer *gLayer;    // The layer now showing
    Player* gPlayer;
    Size winSize;
    Rect gameRect;
    Size gameSize;
    
    // function
    static void addPlayerBullet(Bullet* bullet);
    static void addEnemyBullet(Bullet* bullet);
    static void defaultBltInfo(BulletInfo &bltInfo);
    static void setGameRect(Rect vRect);
    
    void createEnemy(float time);
    void autoMove(Sprite* sp1, Sprite* sp2, float speed);
    
private:
    GameLogic();
    virtual ~GameLogic();
    
    std::vector<EnemyInfo> m_vDupEnemyInfos;
    void addEnemy(EnemyInfo ef);
};

#endif /* defined(__DanmakuExorcism__GameLogic__) */
