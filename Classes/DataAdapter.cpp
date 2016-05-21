//
//  DataAdapter.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-8-6.
//
//

#include "DataAdapter.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

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
    playingStageID = 1;
    logoShowTime = 0;
    logoHasShown = false;
}

DataAdapter::~DataAdapter()
{
    
}

void DataAdapter::init()
{
    return;
    // Init treasures info
    auto path = FileUtils::getInstance()->getWritablePath();
    path.append(FILE_TREASURE_INFO);
    if (!FileUtils::getInstance()->isFileExist(path))
    {
        // Init with treasure info template
        Data tData = FileUtils::getInstance()->getDataFromFile("Script/tis.w3t");
        
        FILE* file = fopen(path.c_str(), "wb");
        if (file)
        {
            fputs((const char*)tData.getBytes(), file);
            fclose(file);
        }
        tData.clear();
    }
    if (FileUtils::getInstance()->isFileExist(path)) {
        rapidjson::Document _doc;
        Data tiData = FileUtils::getInstance()->getDataFromFile(path);
        
        _doc.Parse<0>((const char*)tiData.getBytes());
        rapidjson::Value &tArr = _doc["treasures"];
        
        v_treasureList.clear();
        
        for (rapidjson::SizeType i = 0; i < tArr.Size(); ++i) {
            const rapidjson::Value &pObj = tArr[i];
            TreasureInfo ti;
            ti.Type = (TreasureType)pObj["type"].GetInt();
            ti.IconName = pObj["icon"].GetString();
            ti.Name = pObj["name"].GetString();
            ti.lv = pObj["lv"].GetInt();
            ti.Desc = pObj["desc"].GetString();
            
            v_treasureList.push_back(ti);
        }
        
        tiData.clear();
    } else {
        log("Error: Treasure info file does not exist");
    }
    
}

bool DataAdapter::LoadStageList()
{
    rapidjson::Document _doc;
    ssize_t size = 0;
    unsigned char *pBytes = nullptr;
    
    pBytes = cocos2d::CCFileUtils::getInstance()->getFileData(FILE_STAGE_LIST, "r", &size);
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
    this->playingStageID = stageID;
    
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
    unsigned char *pBytes = nullptr;
    
    Data data = FileUtils::getInstance()->getDataFromFile(stageFileName);
    pBytes = data.getBytes();
    if (pBytes == nullptr || strcmp((char*)pBytes, "") == 0) {
        log("\n\n---- LoadEnemyList File %s Read Error! ----\n", StringUtils::format("%s", stageFileName.c_str()).c_str());
        return nullptr;
    }
    
    std::string load_str((const char*)pBytes, data.getSize());
    log("%s", pBytes);
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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    std::vector<EnemyInfo> v_tmpEnemyInfoList;
    for (rapidjson::SizeType i = 0; i < jsonArr.Size(); i++)
    {
        const rapidjson::Value &p = jsonArr[i];
        if(p.HasMember("enemy"))
        {
            const rapidjson::Value &valueEnt = p["enemy"];
            
            const rapidjson::Value &enemyid = valueEnt["enemyid"];
            const rapidjson::Value &hp = valueEnt["hp"];
            const rapidjson::Value &txrid = valueEnt["txrid"];
            const rapidjson::Value &shootcount = valueEnt["shootcount"];
            const rapidjson::Value &shootdelay = valueEnt["shootdelay"];
            const rapidjson::Value &shootitv = valueEnt["shootitv"];
            const rapidjson::Value &dmkid = valueEnt["dmkid"];
            const rapidjson::Value &showtime = valueEnt["showtime"];
            const rapidjson::Value &showcount = valueEnt["showcount"];
            const rapidjson::Value &showitv = valueEnt["showitv"];
            const rapidjson::Value &showpos = valueEnt["showpos"];
            const rapidjson::Value &showposoff = valueEnt["showposoff"];
            const rapidjson::Value &initpos = valueEnt["initpos"];
            const rapidjson::Value &initposoff = valueEnt["initposoff"];
            const rapidjson::Value &customscript = valueEnt["customscript"];
            
            EnemyInfo enemyInfo;
            enemyInfo.EnemyID = (EnemyType)enemyid.GetInt();
            enemyInfo.TxrID = (TextureType)txrid.GetInt();
            enemyInfo.EnemyHP = hp.GetInt();
            enemyInfo.ShootCount = shootcount.GetInt();
            enemyInfo.ShootDelay = shootdelay.GetDouble();
            enemyInfo.ShootInterval = shootitv.GetDouble();
            enemyInfo.DmkID = (DanmakuType)dmkid.GetInt();
            enemyInfo.ShowTime = showtime.GetDouble();
            enemyInfo.ShowCount = 0;
            enemyInfo.MaxShowCount = showcount.GetInt();
            enemyInfo.ShowInterval = showitv.GetDouble();
            
            if (valueEnt.HasMember("pausetime")) {
                const rapidjson::Value &pausetime = valueEnt["pausetime"];
                enemyInfo.isHoldTime = pausetime.GetBool();
            } else {
                enemyInfo.isHoldTime = false;
            }
            
            std::vector<std::string> vPos = split(showpos.GetString(), ",");
            float x = floorf(atof(vPos.at(0).c_str()) * visibleSize.width);
            float y = floorf(atof(vPos.at(1).c_str()) * visibleSize.height);
            enemyInfo.ShowPos = Vec2(floorf(x), floorf(y));
            
            vPos = split(showposoff.GetString(), ",");
            enemyInfo.ShowPosOff = Vec2(atoi(vPos.at(0).c_str()), atoi(vPos.at(1).c_str()));
            
            vPos = split(initpos.GetString(), ",");
            x = floorf(atof(vPos.at(0).c_str()) * visibleSize.width);
            y = floorf(atof(vPos.at(1).c_str()) * visibleSize.height);
            enemyInfo.InitPos = Vec2(x, y);
            
            vPos = split(initposoff.GetString(), ",");
            enemyInfo.InitPosOff = Vec2(atof(vPos.at(0).c_str()), atof(vPos.at(1).c_str()));
            
            enemyInfo.CustomScript = customscript.GetString();
            
            v_tmpEnemyInfoList.push_back(enemyInfo);
            log("enemy ID : %d", enemyInfo.EnemyID);
        }
        else if (p.HasMember("stagelogo"))
        {
            const rapidjson::Value &valueEnt = p["stagelogo"];
            const rapidjson::Value &showtime = valueEnt["showtime"];
            logoShowTime = showtime.GetDouble();
            logoHasShown = false;
        }
    }
    
    for (int i = (int)v_tmpEnemyInfoList.size() - 1; i >= 0; --i) {
        v_EnemyInfoList.push_back(v_tmpEnemyInfoList.at(i));
    }
    
//    std::sort(v_EnemyInfoList.begin(), v_EnemyInfoList.end(), [](const EnemyInfo ef1,const EnemyInfo ef2){return true;});
    
    log("\n\n---- Load enemy info successful! ----\n");
    
    data.clear();
    return true;
}

std::vector<std::string> DataAdapter::split(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;
    int size = (int)str.size();
    
    for(int i = 0; i < size; i++)
    {
        pos = str.find(pattern,i);
        if(pos < size)
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = (int)(pos + pattern.size() - 1);
        }
    }
    return result;
}








