//
//  DataAdapter.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-8-6.
//
//

#ifndef __DanmakuExorcism__DataAdapter__
#define __DanmakuExorcism__DataAdapter__

#include "cocos2d.h"
#include "Protocol.h"
#include "cocostudio/CocoStudio.h"

class DataAdapter
{
public:
    static DataAdapter *getInstance();
    
    bool LoadStageList();
    bool LoadEnemyList(int stageID);
    
    std::vector<StageInfo> v_stageList;
    std::vector<EnemyInfo> v_EnemyList;
    
    std::vector<std::string> split(std::string str,std::string pattern);
    
private:
    DataAdapter();
    virtual ~DataAdapter();
    
    bool _isJsonValid(rapidjson::Document doc, const char* eleName);
};

#endif /* defined(__DanmakuExorcism__DataAdapter__) */
