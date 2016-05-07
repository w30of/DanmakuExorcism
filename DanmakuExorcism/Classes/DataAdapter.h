//
//  DataAdapter.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-8-6.
//
//

#ifndef __DanmakuExorcism__DataAdapter__
#define __DanmakuExorcism__DataAdapter__

#define FILE_TREASURE_INFO "tis.w3t"

#include "cocos2d.h"
#include "Protocol.h"
#include "cocostudio/CocoStudio.h"

class DataAdapter
{
public:
    static DataAdapter *getInstance();
    
    void init();
    bool LoadStageList();
    bool LoadEnemyList(int stageID);
    
    static std::vector<std::string> split(std::string str,std::string pattern);
    
    std::vector<StageInfo> v_stageList;
    std::vector<EnemyInfo> v_EnemyInfoList;
    std::vector<TreasureInfo> v_treasureList;
    
    int playingStageID;
    float logoShowTime;
    bool logoHasShown;
    
private:
    DataAdapter();
    virtual ~DataAdapter();
    
    bool _isJsonValid(rapidjson::Document doc, const char* eleName);
};

#endif /* defined(__DanmakuExorcism__DataAdapter__) */
