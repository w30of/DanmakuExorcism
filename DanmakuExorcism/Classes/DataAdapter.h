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

class DataAdapter
{
public:
    static DataAdapter *getInstance();
    
    bool LoadStageInfo();
    
    std::vector<StageInfo> v_stageInfo;
    
private:
    DataAdapter();
    virtual ~DataAdapter();
};

#endif /* defined(__DanmakuExorcism__DataAdapter__) */
