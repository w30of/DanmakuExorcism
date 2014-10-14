//
//  DataAdapter.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-8-6.
//
//

#include "DataAdapter.h"
#include "cocostudio/CocoStudio.h"

static DataAdapter *s_dataApapter = nullptr;

DataAdapter* DataAdapter::getInstance()
{
    if (!s_dataApapter) {
        s_dataApapter = new DataAdapter();
    }
    
    return s_dataApapter;
}

DataAdapter::DataAdapter()
{
    
}

DataAdapter::~DataAdapter()
{
    
}

bool DataAdapter::LoadStageInfo()
{
    rapidjson::Document _doc;
    ssize_t size = 0;
    unsigned char *pBytes = nullptr;
    
    pBytes =  cocos2d::CCFileUtils::getInstance()->getFileData("Script/StageInfo.json", "r", &size);
    
    if (pBytes == nullptr || strcmp((char*)pBytes, "") == 0) {
        return false;
    }
    
    std::string load_str((const char*)pBytes, size);
    CCLOG("%s", pBytes);
    CC_SAFE_DELETE_ARRAY(pBytes);
    _doc.Parse<0>(load_str.c_str());
    
    if (_doc.HasParseError()) {
        CCLOG("\n\n---- StageInfo.json Parse Error! ----\n");
        return false;
    }
    
    //生成json文档对像
    if(!_doc.IsObject()) {
        CCLOG("\n\n---- StageInfo.json not an object! ----\n");
        return false;
    }
    
    //是否有此成员
    if(!_doc.HasMember("stageinfos")) {
        CCLOG("\n\n---- StageInfo.json do not has member 'stageinfos'! ----\n");
        return false;
    }
    
    // 通过[]取成员值,再根据需要转为array,int,double,string
    const rapidjson::Value &jsonArr = _doc["stageinfos"];
    
    //是否是数组
    if(!jsonArr.IsArray()) {
        CCLOG("\n\n---- StageInfo.json not an array! ----\n");
        return false;
    }
    
    for (rapidjson::SizeType i = 0; i < jsonArr.Size(); i++)
    {
        const rapidjson::Value &p = jsonArr[i];
        if(p.HasMember("stage"))
        {
            const rapidjson::Value &valueEnt = p["stage"];
            if(valueEnt.HasMember("stageid") &&
               valueEnt.HasMember("stagename") &&
               valueEnt.HasMember("cutin") &&
               valueEnt.HasMember("background") &&
               valueEnt.HasMember("nextstageid") &&
               valueEnt.HasMember("script") )
            {
                const rapidjson::Value &stageid = valueEnt["stageid"];
                const rapidjson::Value &stagename = valueEnt["stagename"];
                const rapidjson::Value &cutin = valueEnt["cutin"];
                const rapidjson::Value &background = valueEnt["background"];
                const rapidjson::Value &nextstageid = valueEnt["nextstageid"];
                const rapidjson::Value &script = valueEnt["script"];
                
                StageInfo stageInfo;
                stageInfo.StageID = stageid.GetInt();
                stageInfo.StageName = stagename.GetString();
                stageInfo.StageCutInPicName = cutin.GetString();
                stageInfo.StageBackgroundPicName = background.GetString();
                stageInfo.NextStageID = nextstageid.GetInt();
                stageInfo.StageScriptFileName = script.GetString();
                
                this->v_stageInfo.push_back(stageInfo);
                CCLOG("%d, %s", stageInfo.StageID, stageInfo.StageName.c_str());
            }
        }        
    }
    CCLOG("\n\n---- Load stage info successful! ----\n");
    return true;
}











