//
//  Protocol.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-8-6.
//
//

#ifndef DanmakuExorcism_Protocol_h
#define DanmakuExorcism_Protocol_h

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

typedef enum
{
    SHOW_AUTO_OFFSET    = 0,
    SHOW_ALL_CUNTOM     = 1,
    SHOW_RANDOM         = 2,
    SHOW_BY_L_A         = 3
}ShowType;

struct StageInfo
{
    int StageID;
    std::string StageName;
    std::string StageCutInPicName;
    std::string StageBackgroundPicName;
    int NextStageID;
    std::string StageScriptFileName;
};

struct EnemyInfo
{
    // base data
    int EnemyID;
    int Count;
    int Repeat;
    float ShowTime;
    float ShowTimeDelay;
    float ShowTimeInterval;
    
    ShowType showType;
    // positon auto offset
    Vec2 ShowPos;
    Vec2 ShowPosOff;
    // position all custom
    std::vector<Vec2> v_ShowPos;
    // position random
    Vec2 Range; // need ShowPos
    
    // w3 script
    std::string CustomScript;
    std::string ActionScript;
};

struct DanmakuInfo
{
    int BulletID;
    float v;
    float vOff;
    float vExOff;
    float vLimit;
    float a;
    float aOff;
    float aExOff;
    float aLimit;
    float ShowTime;
    float ShowTimeDelay;
    float ShowTimeInterval;
    
    ShowType showType;
    // positon auto offset
    Vec2 ShowPos;
    Vec2 ShowPosOff;
    
    // position all custom
    std::vector<Vec2> v_ShowPos;
    
    // position random
    Vec2 Range; // need ShowPos, rect is ShowPos + Range
    
    // position by l&a
    float ShowA;
    float ShowAOff;
    float ShowAExOff;
    float ShowLen;
    float ShowLenOff;
    float ShowLenExOff;
    
    // w3 script
    std::string CustomScript;
    std::string ActionScript;
};

#endif









