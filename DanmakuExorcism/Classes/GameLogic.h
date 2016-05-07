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
#include "Enemy.h"

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
    static void addBullet(Bullet* blt);
    static void addPlayerBullet(Bullet* bullet);
    static void addEnemyBullet(Bullet* bullet);
    static void defaultBltInfo(BulletInfo &bltInfo);
    static void setGameRect(Rect vRect);
    static void clearDanmakuContainer();
    static float getLineAngle(Vec2 p1, Vec2 p2);
    static float getAngleToPlayer(Vec2 p);
    static Bullet* setBullet(BulletGeneratorType type,
                             BulletType bID,
                             Vec2 pos,
                             float v,
                             float a,
                             float vl = 0,
                             float al = 0,
                             float voff = 0,
                             float aoff = 0,
                             float vex = 0,
                             float aex = 0);
    
    void createEnemy(float time);
    void autoMove(Sprite* sp1, Sprite* sp2, float speed);
    Vector<Sequence*> getW3Actions(std::string w3Script, Enemy* target);
    
private:
    GameLogic();
    virtual ~GameLogic();
    
    std::vector<EnemyInfo> m_vDupEnemyInfos;
    void addEnemy(EnemyInfo ef);
    Action* getAction(std::string w3sBlock, Enemy* target);
    float getPosArgWithOffset(std::string w3sBlock, bool isX, int showCount);
};

#endif /* defined(__DanmakuExorcism__GameLogic__) */
