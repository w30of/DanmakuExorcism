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

#define FILE_STAGE_LIST "Script/StageList.json"
#define MEMBER_STAGE_LIST "stageinfos"

#define MEMBER_ENEMY_LIST "enemyinfo"
#define ZORDER_PLAYER 1
#define ZORDER_ENEMY 2
#define ZORDER_ENEMY_BULLET 3
#define ZORDER_PLAYER_BULLET 4

typedef enum
{
    PLAYER_BULLET   = 0,
    ENEMY_BULLET   = 1,
    ENEMY    = 2,
    PLAYER   = 3
    
}BulletGeneratorType;

typedef enum
{
    BULLET_DAOSHI_A = 0,
    BULLET_BLUE = 1,
}BulletType;

typedef enum
{
    SHOW_AUTO_OFFSET    = 0,
    SHOW_ALL_CUNTOM     = 1,
    SHOW_RANDOM         = 2,
    SHOW_BY_L_A         = 3
}ShowType;

typedef enum
{
    DANMAKU_ENEMY_01    = 0,
    DANMAKU_ENEMY_02     = 1,
}DanmakuType;

typedef enum
{
    ENEMY_01    = 0,
    ENEMY_02     = 1,
}EnemyType;

typedef enum
{
    TXR_BLUE_SOUL    = 0,
    TXR_RED_SOUL     = 1,
}TextureType;

// Struct

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
    EnemyType EnemyID;
    TextureType TxrID;
    int ShootCount;             // -1: always, 0: never shoot
    float ShootDelay;           // Start scheduler delay seconds later
    float ShootInterval;
    DanmakuType DmkID;          // For create danmaku
    
    float ShowTime;             // The timing of the appearance
    Vec2 ShowPos;               // The position of the appearance
    
    // w3 script
    std::string CustomScript;
};

struct DanmakuInfo
{
    std::vector<int> v_DanmakuID;
};

struct BulletInfo
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









