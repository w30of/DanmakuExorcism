//
//  GameLogic.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-28.
//
//

#include "GameLogic.h"
#include "DataAdapter.h"
#include "Enemy.h"

static GameLogic *s_logicInstance = nullptr;

GameLogic* GameLogic::getInstance()
{
    if (!s_logicInstance) {
        s_logicInstance = new GameLogic();
    }
    
    return s_logicInstance;
}

GameLogic::GameLogic()
{
    gLayer = nullptr;
}

GameLogic::~GameLogic()
{
    
}

// functions...
void GameLogic::addPlayerBullet(Bullet *bullet)
{
    GameLogic::getInstance()->gLayer->addChild(bullet, ZORDER_PLAYER_BULLET);
}

void GameLogic::createEnemy(float time)
{
    if (DataAdapter::getInstance()->v_EnemyList.size() == 0) {
        return;
    }
    EnemyInfo ef = DataAdapter::getInstance()->v_EnemyList.back();
    if (time >= ef.ShowTime)
    {
        Enemy *enemy = Enemy::create();
        enemy->setEnemyInfo(ef);
//        enemy->setDanmaku();
        GameLogic::getInstance()->gLayer->addChild(enemy, ZORDER_ENEMY);
    }
}




