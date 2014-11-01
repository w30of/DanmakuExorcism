//
//  DataAdapter.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-8-6.
//
//

#include "DataAdapter.h"

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

bool DataAdapter::LoadStageList()
{
    rapidjson::Document _doc;
    ssize_t size = 0;
    unsigned char *pBytes = nullptr;
    
    pBytes =  cocos2d::CCFileUtils::getInstance()->getFileData(FILE_STAGE_LIST, "r", &size);
    if (pBytes == nullptr || strcmp((char*)pBytes, "") == 0) {
        log("\n\n---- File %s Read Error! ----\n", FILE_STAGE_LIST);
        return nullptr;
    }
    
    std::string load_str((const char*)pBytes, size);
    log("%s", pBytes);
    CC_SAFE_DELETE_ARRAY(pBytes);
    _doc.Parse<0>(load_str.c_str());
    
    if (_doc.HasParseError()) {
        log("\n\n---- LoadStageList Document Parse Error! ----\n");
        return false;
    }
    if(!_doc.IsObject()) {
        log("\n\n---- LoadStageList Document not an object! ----\n");
        return false;
    }
    if(!_doc.HasMember(MEMBER_STAGE_LIST)) {
        log("\n\n---- LoadStageList Document do not has member '%s'! ----\n", MEMBER_STAGE_LIST);
        return false;
    }
    const rapidjson::Value &jsonArr = _doc[MEMBER_STAGE_LIST];
    if(!jsonArr.IsArray()) {
        log("\n\n---- LoadStageList Document not an array! ----\n");
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
                
                this->v_stageList.push_back(stageInfo);
                log("%d, %s", stageInfo.StageID, stageInfo.StageName.c_str());
            }
        }        
    }
    log("\n\n---- Load stage info successful! ----\n");
    return true;
}

bool DataAdapter::LoadEnemyList(int stageID)
{
    std::string stageFileName;
    for (int i = 0; i < v_stageList.size(); ++i)
    {
        StageInfo si = v_stageList.at(i);
        if (si.StageID == stageID) {
            stageFileName = si.StageScriptFileName;
        }
    }
    
    if (stageFileName.empty()) {
        return false;
    }
    
    rapidjson::Document _doc;
    ssize_t size = 0;
    unsigned char *pBytes = nullptr;
    
    pBytes =  cocos2d::CCFileUtils::getInstance()->getFileData(String::createWithFormat("Script/%s", stageFileName.c_str())->getCString(), "r", &size);
    if (pBytes == nullptr || strcmp((char*)pBytes, "") == 0) {
        log("\n\n---- LoadEnemyList File %s Read Error! ----\n", String::createWithFormat("Script/%s", stageFileName.c_str())->getCString());
        return nullptr;
    }
    
    std::string load_str((const char*)pBytes, size);
    log("%s", pBytes);
    CC_SAFE_DELETE_ARRAY(pBytes);
    _doc.Parse<0>(load_str.c_str());
    

    if (_doc.HasParseError()) {
        log("\n\n---- LoadEnemyList Document Parse Error! ----\n");
        return false;
    }
    if(!_doc.IsObject()) {
        log("\n\n---- LoadEnemyList Document not an object! ----\n");
        return false;
    }
    if(!_doc.HasMember(MEMBER_ENEMY_LIST)) {
        log("\n\n---- LoadEnemyList Document do not has member '%s'! ----\n", MEMBER_ENEMY_LIST);
        return false;
    }
    const rapidjson::Value &jsonArr = _doc[MEMBER_ENEMY_LIST];
    if(!jsonArr.IsArray()) {
        log("\n\n---- LoadEnemyList Document not an array! ----\n");
        return false;
    }
    
    for (rapidjson::SizeType i = 0; i < jsonArr.Size(); i++)
    {
        const rapidjson::Value &p = jsonArr[i];
        if(p.HasMember("enemy"))
        {
            const rapidjson::Value &valueEnt = p["enemy"];
            if (valueEnt.HasMember("enemyid") &&
                valueEnt.HasMember("txrid") &&
                valueEnt.HasMember("shootcount") &&
                valueEnt.HasMember("shootdelay") &&
                valueEnt.HasMember("shootitv") &&
                valueEnt.HasMember("dmkid") &&
                valueEnt.HasMember("showtime") &&
                valueEnt.HasMember("showpos") &&
                valueEnt.HasMember("customscript") )
            {
                const rapidjson::Value &enemyid = valueEnt["enemyid"];
                const rapidjson::Value &txrid = valueEnt["txrid"];
                const rapidjson::Value &shootcount = valueEnt["shootcount"];
                const rapidjson::Value &shootdelay = valueEnt["shootdelay"];
                const rapidjson::Value &shootitv = valueEnt["shootitv"];
                const rapidjson::Value &dmkid = valueEnt["dmkid"];
                const rapidjson::Value &showtime = valueEnt["showtime"];
                const rapidjson::Value &showpos = valueEnt["showpos"];
                const rapidjson::Value &customscript = valueEnt["customscript"];
                
                EnemyInfo enemyInfo;
                enemyInfo.EnemyID = (EnemyType)enemyid.GetInt();
                enemyInfo.TxrID = (TextureType)txrid.GetInt();
                enemyInfo.ShootCount = shootcount.GetInt();
                enemyInfo.ShootDelay = shootdelay.GetDouble();
                enemyInfo.ShootInterval = shootitv.GetDouble();
                enemyInfo.DmkID = (DanmakuType)dmkid.GetInt();
                enemyInfo.ShowTime = showtime.GetDouble();
                std::vector<std::string> vPos = split(showpos.GetString(), ",");
                enemyInfo.ShowPos = Vec2(atoi(vPos.at(0).c_str()), atoi(vPos.at(1).c_str()));
                enemyInfo.CustomScript = customscript.GetString();
                
                this->v_EnemyList.push_back(enemyInfo);
                log("enemy ID : %d", enemyInfo.EnemyID);
            }
        }
    }
    log("\n\n---- Load enemy info successful! ----\n");
    
    return true;
}

std::vector<std::string> DataAdapter::split(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;
    int size=str.size();
    
    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}








