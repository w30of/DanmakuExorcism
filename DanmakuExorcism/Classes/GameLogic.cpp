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

using namespace std;

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
            if (ef.ShowCount < ef.MaxShowCount && ef.MaxShowCount > 1) {
                ef.ShowTime += ef.ShowInterval;
                ef.ShowPos += ef.ShowPosOff;
                float offsetX = ef.InitPosOff.x;
                if (offsetX > -1 && offsetX < 1 && offsetX != 0) {
                    offsetX = offsetX * winSize.width;
                }
                float offsetY = ef.InitPosOff.y;
                if (offsetY > -1 && offsetY < 1 && offsetY != 0) {
                    offsetY = offsetY * winSize.height;
                }
                ef.InitPos += Vec2(offsetX, offsetY);
                ++ef.ShowCount;
                m_vDupEnemyInfos.push_back(ef);

            }
            data->v_EnemyInfoList.pop_back();
        }
    }
    
    // Create duplicated enemy
    if (m_vDupEnemyInfos.size() > 0) {
        /* vector的遍历删除方法坑，记录在印象笔记中了 */
        for(std::vector<EnemyInfo>::iterator it = m_vDupEnemyInfos.begin(); it != m_vDupEnemyInfos.end();)
        {
            if (time > (*it).ShowTime) {
                EnemyInfo efIt = *it;
                addEnemy(efIt);
                (*it).ShowPos += (*it).ShowPosOff;
                (*it).InitPos += (*it).InitPosOff;
                (*it).ShowTime += (*it).ShowInterval;
                if (++((*it).ShowCount) >= (*it).MaxShowCount) {
                    it = m_vDupEnemyInfos.erase(it);
                } else {
                    ++it;
                }
            } else {
                ++it;
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
    Bullet* blt = nullptr;
    if (type == PLAYER_BULLET) {
        blt = (Bullet*)DanmakuPool::getInstance()->getPlayerBullet();
    } else if (type == ENEMY_BULLET) {
        blt = (Bullet*)DanmakuPool::getInstance()->getEnemyBullet();
    }
    blt->setPosition(pos);
    blt->setBulletGeneratorType(type);
    BulletInfo bi;
    GameLogic::defaultBltInfo(bi);
    bi.BulletID = bID;
    bi.v = v;
    bi.a = a;
    bi.vLimit = vl;
    bi.aLimit = al;
    bi.vOff = voff;
    bi.aOff = aoff;
    bi.vExOff = vex;
    bi.aExOff = aex;
    blt->setBulletInfo(bi);
    blt->bulletEnable();
    
    return blt;
}



// private functions...
void GameLogic::addEnemy(EnemyInfo ef)
{
    Enemy *enemy = Enemy::create();
    enemy->setEnemyInfo(ef);
}

Vector<Sequence*> GameLogic::getW3Actions(std::string w3Script, Enemy* target)
{
    Vector<Sequence*> ret;
    std::vector<std::string> v_seq = DataAdapter::getInstance()->split(w3Script, "|");
    size_t seqLen = v_seq.size();
    for (int i = 0; i < seqLen; ++i) {
        std::string strSeq = v_seq.at(i);
        std::vector<std::string> v_actions = DataAdapter::getInstance()->split(strSeq, ";");
        size_t actLen = v_actions.size();
        
        Vector<FiniteTimeAction*> actions;
        for (int j = 0; j < actLen; ++j) {
            std::string strAct = v_actions.at(j);
            Action* pOneAct = this->getAction(strAct, target);
            actions.pushBack((FiniteTimeAction*)pOneAct);
        }
        ret.pushBack(Sequence::create(actions));
    }
    
    return ret;
}

Action* GameLogic::getAction(std::string w3sBlock, Enemy* target)
{
    std::vector<std::string> v_action = DataAdapter::getInstance()->split(w3sBlock, ",");
    size_t len = v_action.size();
    
    if (len < 1) {
        log("Wrong script struct.");
        return nullptr;
    }
    
    Action* ret = nullptr;
    bool w3sInvalid = false;
    
    std::string actionName = v_action.at(0);
    if (actionName.compare("MoveTo") == 0)
    {
        float dur = atof(v_action.at(1).c_str());
        float x, y;
        if (v_action.at(2).compare("showpos") == 0) {
            Vec2 pos = target->getShowPos();
            x = pos.x;
            y = pos.y;
        } else {
            x = getPosArgWithOffset(v_action.at(2), true, target->getEnemyInfo().ShowCount);
            y = getPosArgWithOffset(v_action.at(3), false, target->getEnemyInfo().ShowCount);
        }
        ret = MoveTo::create(dur, Vec2(x, y));
    }
    else if (actionName.compare("MoveBy") == 0)
    {
        float dur = atof(v_action.at(1).c_str());
        float x = atof(v_action.at(2).c_str());
        float y = atof(v_action.at(3).c_str());
        if (x > 0 && x < 1) {
            x = winSize.width * x;
        }
        if (y > 0 && y < 1) {
            y = winSize.height * y;
        }
        ret = MoveBy::create(dur, Vec2(x, y));
    }
    else if (actionName.compare("ScaleTo") == 0) {
        float dur = atof(v_action.at(1).c_str());
        float sx = atof(v_action.at(2).c_str());
        float sy = atof(v_action.at(3).c_str());
        ret = ScaleTo::create(dur, sx, sy);
    }
    else if (actionName.compare("ScaleBy") == 0) {
        float dur = atof(v_action.at(1).c_str());
        float sx = atof(v_action.at(2).c_str());
        float sy = atof(v_action.at(3).c_str());
        ret = ScaleBy::create(dur, sx, sy);
    }
    else if (actionName.compare("RotateTo") == 0) {
        float dur = atof(v_action.at(1).c_str());
        float agl = atof(v_action.at(2).c_str());
        ret = RotateTo::create(dur, agl);
    }
    else if (actionName.compare("RotateBy") == 0) {
        float dur = atof(v_action.at(1).c_str());
        float agl = atof(v_action.at(2).c_str());
        ret = RotateBy::create(dur, agl);
    }
    else if (actionName.compare("FadeTo") == 0) {
        float dur = atof(v_action.at(1).c_str());
        float o = atoi(v_action.at(2).c_str());
        ret = FadeTo::create(dur, o);
    }
    else if (actionName.compare("BezierTo") == 0) {
        float dur = atof(v_action.at(1).c_str());
        
        float cpx1 = getPosArgWithOffset(v_action.at(2), true, target->getEnemyInfo().ShowCount);
        float cpy1 = getPosArgWithOffset(v_action.at(3), false, target->getEnemyInfo().ShowCount);
        float cpx2 = getPosArgWithOffset(v_action.at(4), true, target->getEnemyInfo().ShowCount);
        float cpy2 = getPosArgWithOffset(v_action.at(5), false, target->getEnemyInfo().ShowCount);
        
        float endx, endy;
        if (v_action.at(6).compare("showpos") == 0) {
            Vec2 pos = target->getShowPos();
            endx = pos.x;
            endy = pos.y;
        } else {
            endx = getPosArgWithOffset(v_action.at(6), true, target->getEnemyInfo().ShowCount);
            endy = getPosArgWithOffset(v_action.at(7), false, target->getEnemyInfo().ShowCount);
        }
        
        ccBezierConfig bc;
        bc.controlPoint_1 = Vec2(cpx1, cpy1);
        bc.controlPoint_2 = Vec2(cpx2, cpy2);
        bc.endPosition = Vec2(endx, endy);
        ret = BezierTo::create(dur, bc);
    }
    else if (actionName.compare("remove") == 0)
    {
        ret = CallFunc::create([=](){
            target->die();
            log("enemy removed : %d",target->getEnemyInfo().EnemyID);
        });
    }
    else if (actionName.compare("shoot") == 0)
    {
        ret = CallFunc::create([=](){  target->shoot();  });
    }
    else if (actionName.compare("DelayTime") == 0)
    {
        string arg = v_action.at(1).c_str();
        vector<string> v_args = DataAdapter::split(arg, "+");
        float dur = 0;
        if (v_args.size() > 1) {
            dur = atof(v_args.at(0).c_str()) + atof(v_args.at(1).c_str()) * target->getEnemyInfo().ShowCount;
        } else {
            dur = atof(arg.c_str());
        }
        ret = DelayTime::create(dur);
    }
    
    if (ret) {
        std::string lastSelection = v_action.at(len-1);
        if (lastSelection.compare("EaseSineIn") == 0)
        {
            ret = EaseSineIn::create((ActionInterval*)ret);
        }
        else if (lastSelection.compare("EaseSineOut") == 0)
        {
            ret = EaseSineOut::create((ActionInterval*)ret);
        }
        else if (lastSelection.compare("EaseExpIn") == 0)
        {
            ret = EaseExponentialIn::create((ActionInterval*)ret);
        }
        else if (lastSelection.compare("EaseExpOut") == 0)
        {
            ret= EaseExponentialOut::create((ActionInterval*)ret);
        }
    }
    
    if (w3sInvalid) {
        log("Worng argument count of script : /n %s", w3sBlock.c_str());
    }
    
    return ret;
}


/* 将 "10+5" 格式的字符串以字符'+'分割并将前一个数换算成屏幕坐标与后一个数相加 */
float GameLogic::getPosArgWithOffset(std::string w3sBlock, bool isX, int showCount) {
    vector<string> v_args = DataAdapter::split(w3sBlock, "+");
    float len = 0;
    if (isX) {
        len = winSize.width;
    } else {
        len = winSize.height;
    }
    if (v_args.size() > 1) {
        float offset = atof(v_args.at(1).c_str());
        if (offset > -1 && offset < 1 && offset != 0) {
            offset = offset * len;
        }
        return atof(v_args.at(0).c_str()) * len + offset * showCount;
    } else {
        return atof(w3sBlock.c_str()) * len;
    }
}
























































