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
void GameLogic::addBullet(Bullet *blt)
{
    if (blt->getBulletGeneratorType() == ENEMY_BULLET) {
        GameLogic::getInstance()->gLayer->addChild(blt, ZORDER_ENEMY_BULLET);
    } else if (blt->getBulletGeneratorType() == PLAYER_BULLET) {
        GameLogic::getInstance()->gLayer->addChild(blt, ZORDER_PLAYER_BULLET);
    }
}

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
    DataAdapter* data = DataAdapter::getInstance();
    
    if (!data->logoHasShown && time >= data->logoShowTime) {
        if (gLayer) {
            ((GamingLayer*)gLayer)->showLogo(data->playingStageID);
            data->logoHasShown = true;
        }
    }
    
    if (data->v_EnemyInfoList.size() == 0 && m_vDupEnemyInfos.size() == 0) {
        return;
    }
    
    // Create enemy in enemy list of stage.
    if (data->v_EnemyInfoList.size() > 0) {
        EnemyInfo ef = data->v_EnemyInfoList.back();
        if (time >= ef.ShowTime)
        {
            addEnemy(ef);
            if (ef.ShowCount > 1) {
                ef.ShowTime += ef.ShowInterval;
                ef.ShowPos += ef.ShowPosOff;
                --ef.ShowCount;
                m_vDupEnemyInfos.push_back(ef);
            }
            data->v_EnemyInfoList.pop_back();
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

void GameLogic::clearDanmakuContainer()
{
    if (GameLogic::getInstance()->gLayer) {
        GameLogic::getInstance()->gLayer->removeAllChildren();
        GameLogic::getInstance()->gLayer = nullptr;
    }
}

float GameLogic::getLineAngle(cocos2d::Vec2 p1, cocos2d::Vec2 p2)
{
    Vec2 dir = p1 - p2;
    float a = dir.getAngle();
    return a;
}

float GameLogic::getAngleToPlayer(cocos2d::Vec2 p)
{
    if (GameLogic::getInstance()->gPlayer) {
        float angle = getLineAngle(GameLogic::getInstance()->gPlayer->getPosition(), p);
        angle = CC_RADIANS_TO_DEGREES(angle);
        return angle;
    } else {
        return 0;
    }
}

Bullet* GameLogic::setBullet(BulletGeneratorType type,
                             BulletType bID,
                             Vec2 pos,
                             float v,
                             float a,
                             float vl/* = 0*/,
                             float al/* = 0*/,
                             float voff/* = 0*/,
                             float aoff/* = 0*/,
                             float vex/* = 0*/,
                             float aex/* = 0*/)
{
    Bullet* blt = Bullet::create();
    blt->setPosition(pos);
    blt->setBulletGeneratorType(type);
    BulletInfo bi;
    GameLogic::defaultBltInfo(bi);
    bi.BulletID = bID;
    bi.v = v;
    //    bi.a = CC_RADIANS_TO_DEGREES(a);
    bi.a = a;
    bi.vLimit = vl;
    bi.aLimit = al;
    bi.vOff = voff;
    bi.aOff = aoff;
    bi.vExOff = vex;
    bi.aExOff = aex;
    blt->setBulletInfo(bi);
    blt->bulletEnable();
    
    GameLogic::addBullet(blt);
    
    return blt;
}



// private functions...
void GameLogic::addEnemy(EnemyInfo ef)
{
    Enemy *enemy = Enemy::create();
    enemy->setEnemyInfo(ef);
    GameLogic::getInstance()->gLayer->addChild(enemy, ZORDER_ENEMY);
}




