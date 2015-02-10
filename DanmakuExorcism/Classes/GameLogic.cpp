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
    gPlayer = nullptr;
}

GameLogic::~GameLogic()
{
    
}

// static functions...
void GameLogic::addPlayerBullet(Bullet *bullet)
{
    GameLogic::getInstance()->gLayer->addChild(bullet, ZORDER_PLAYER_BULLET);
}

void GameLogic::addEnemyBullet(Bullet *bullet)
{
    GameLogic::getInstance()->gLayer->addChild(bullet, ZORDER_ENEMY_BULLET);
}

void GameLogic::defaultBltInfo(BulletInfo &bltInfo)
{
    bltInfo.BulletID = BULLET_NONE;
    bltInfo.v = 0;
    bltInfo.vOff = 0;
    bltInfo.vExOff = 0;
    bltInfo.vLimit = 0;
    bltInfo.a = 0;
    bltInfo.aOff = 0;
    bltInfo.aExOff = 0;
    bltInfo.aLimit = 0;
}

// public functions...
void GameLogic::createEnemy(float time)
{
    // No enemy to create should pause.
    if (DataAdapter::getInstance()->v_EnemyInfoList.size() == 0 && m_vDupEnemyInfos.size() == 0) {
        return;
    }
    
    // Create enemy in enemy list of stage.
    if (DataAdapter::getInstance()->v_EnemyInfoList.size() > 0) {
        EnemyInfo ef = DataAdapter::getInstance()->v_EnemyInfoList.back();
        if (time >= ef.ShowTime)
        {
            addEnemy(ef);
            if (ef.ShowCount > 1) {
                ef.ShowTime += ef.ShowInterval;
                ef.ShowPos += ef.ShowPosOff;
                --ef.ShowCount;
                m_vDupEnemyInfos.push_back(ef);
            }
            DataAdapter::getInstance()->v_EnemyInfoList.pop_back();
        }
    }
    
    // Create duplicated enemy
    if (m_vDupEnemyInfos.size() > 0) {
        std::vector<EnemyInfo>::iterator it;
        std::vector<EnemyInfo>::iterator end = m_vDupEnemyInfos.end();
        for(it = m_vDupEnemyInfos.begin(); it != end; ++it)
        {
            if (time > (*it).ShowTime) {
                EnemyInfo efIt = *it;
                addEnemy(efIt);
                (*it).ShowPos += (*it).ShowPosOff;
                (*it).ShowTime += (*it).ShowInterval;
                if (--(*it).ShowCount == 0) {
                    m_vDupEnemyInfos.erase(it);
                }
            }
        }
    }
}

void GameLogic::autoMove(cocos2d::Sprite *sp1, cocos2d::Sprite *sp2, float speed)
{
    if (sp1) {
        sp1->setPositionY(sp1->getPositionY() + speed);
        if (sp1->getPositionY() < -winSize.height) {
            sp1->setPositionY(winSize.height);
        }
    }
    if (sp2) {
        sp2->setPositionY(sp2->getPositionY() + speed);
        if (sp2->getPositionY() < -winSize.height) {
            sp2->setPositionY(winSize.height);
        }
    }
}

void GameLogic::setGameRect(cocos2d::Rect vRect)
{
    GameLogic::getInstance()->gameRect = vRect;
    GameLogic::getInstance()->gameSize = vRect.size;
}




// private functions...
void GameLogic::addEnemy(EnemyInfo ef)
{
    Enemy *enemy = Enemy::create();
    enemy->setEnemyInfo(ef);
    GameLogic::getInstance()->gLayer->addChild(enemy, ZORDER_ENEMY);
}




