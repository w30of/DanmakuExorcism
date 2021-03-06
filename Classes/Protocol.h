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

#define FILE_STAGE_LIST "script/StageList.json"
#define MEMBER_STAGE_LIST "stageinfos"
#define MEMBER_ENEMY_LIST "enemyinfo"

#define ZORDER_PLAYER 2
#define ZORDER_PLAYER_BULLET 1
#define ZORDER_ENEMY 3
#define ZORDER_ENEMY_BULLET 4

#define PLIST_DAOSHI_ANIMATION "players/daoshi/daoshi.plist"

#define FILE_DAOSHI_FULL "texture/player_daoshi.png"
#define FILE_HESHANG_FULL "texture/player_daoshi.png"
#define FILE_JIANKE_FULL "texture/player_daoshi.png"
#define FILE_EMPTY_TEXTURE "texture/empty_block.png"

typedef enum
{
    PLAYER_BULLET   = 0,
    ENEMY_BULLET   = 1,
    ENEMY    = 2,
    PLAYER   = 3
    
}BulletGeneratorType;

typedef enum
{
    BULLET_NONE         = 0,
    BULLET_DAOSHI_A     = 1,
    BULLET_ENEMY_BLUE_1 = 2,
    BULLET_ENEMY_RED_1  = 3,
}BulletType;

typedef enum
{
    BUFFER_BULLET = 0,
}CustomBulletType;


typedef enum
{
    SHOW_AUTO_OFFSET    = 0,
    SHOW_ALL_CUNTOM     = 1,
    SHOW_RANDOM         = 2,
    SHOW_BY_L_A         = 3
}ShowType;

typedef enum
{
    DANMAKU_NONE        = 0,
    DANMAKU_ENEMY_1_1   = 1,
    DANMAKU_ENEMY_1_3   = 3,
    DANMAKU_ENEMY_1_4   = 4,
    DANMAKU_ENEMY_1_5   = 5,
    DANMAKU_ENEMY_1_6   = 6,
    DANMAKU_ENEMY_1_7   = 7,
    DANMAKU_ENEMY_1_8   = 8,
    DANMAKU_ENEMY_1_9   = 9,
    DANMAKU_ENEMY_1_11  = 11,
    DANMAKU_ENEMY_1_12  = 12,
    DANMAKU_ENEMY_1_13  = 13,
    DANMAKU_ENEMY_1_14  = 14
}DanmakuType;

typedef enum
{
    ENEMY_1_1 = 1,
    ENEMY_1_2 = 2,
    ENEMY_1_3 = 3,
    ENEMY_1_4_BOSS = 13
}EnemyType;

typedef enum
{
    TXR_BLUE_SOUL    = 0,
    TXR_RED_SOUL     = 1,
}TextureType;

typedef enum
{
    CCB_LY_HOME = 0,
    CCB_LY_SELECT_PLAYER = 1,
    
}CCBClassType;

typedef enum
{
    TREASURE_CALABASH = 0,
    TREASURE_SOUL_STONE = 1,
}TreasureType;

typedef enum
{
    DIR_NONE = 0,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN
}Direction;







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
    // Enemy Data
    EnemyType EnemyID;
    TextureType TxrID;
    int EnemyHP;
    int ShootCount;             // -1: always, 0: never shoot
    float ShootDelay;           // Start scheduler delay seconds later
    float ShootInterval;
    DanmakuType DmkID;          // For create danmaku
    
    float ShowTime;             // Timing of the appearance
    int ShowCount;              // Count of this enemy, start at 0
    int MaxShowCount;           // Max count of this enemy
    float ShowInterval;         // Interval of the appearance
    Vec2 ShowPos;               // Position of the appearance
    Vec2 ShowPosOff;            // Position offset of the appearance
    Vec2 InitPos;               // Position of the preset
    Vec2 InitPosOff;            // Position offset of the preset
    
    bool isHoldTime;            // true: play time will pause, usually is a boss
    
    // w3 script
    std::string CustomScript;
};

struct DanmakuInfo
{
    std::vector<int> v_DanmakuID;
    float ShowTimeDelay;    // Duration of
    float ShowTimeInterval;
};

struct BulletInfo
{
    BulletType BulletID;    // Custom texture and unique behavior or something special for this bullet
    float v;                // Velocity length
    float vOff;             // Change v, will added to v every update() func called
    float vExOff;           // Change vOff, will added to vOff every update() func called
    float vLimit;           // Max value of velocity
    float a;                // Angle (degree)
    float aOff;             // Change a, same like vOff
    float aExOff;           // Change aOff, same like vExOff
    float aLimit;           // Max value of angle
};

struct TreasureInfo
{
    TreasureType Type;
    std::string IconName;
    std::string Name;
    std::string Desc;
    short lv;
};

#endif









