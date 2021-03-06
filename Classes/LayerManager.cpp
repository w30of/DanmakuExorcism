//
//  LayerManager.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-14.
//
//

#include "LayerManager.h"
#include "CCBLayerLoader.h"

static LayerManager *s_layerManager = nullptr;

LayerManager* LayerManager::getInstance()
{
    if (!s_layerManager) {
        s_layerManager = LayerManager::create();
    }
    
    return s_layerManager;
}

LayerManager::LayerManager()
{
    
}

LayerManager::~LayerManager()
{
    
}

bool LayerManager::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    prepare();
    return true;
}

void LayerManager::prepare()
{
    this->setAnchorPoint(Point::ZERO);
}
/*
 Wanna add a layer? You should:
 1. Create your layer class
 2. Add an enum variable in Protocol.h
 3. Add a loader in CCBLayerLoader.h
 4. Add a case below
 */
Node* LayerManager::getCCB(CCBClassType classType, Ref* pOwner /* = nullptr */)
{
    std::string strCCBFileName;
    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
    
    switch (classType) {
        case CCB_LY_HOME:{
            ccNodeLoaderLibrary->registerNodeLoader("LyHome", LyHomeLoader::loader());
            strCCBFileName = "ccbi/ccb/lyHome.ccbi";
        }
            break;
        case CCB_LY_SELECT_PLAYER:{
            ccNodeLoaderLibrary->registerNodeLoader("LySelectPlayer", LySelectPlayerLoader::loader());
            strCCBFileName = "ccbi/ccb/lySelectPlayer.ccbi";
        }
            break;
        default:
            return nullptr;
            break;
    }
    
    CCBReader * ccbReader = new CCBReader(ccNodeLoaderLibrary);
//    ccbReader->getAnimationManager();
    Node * node = nullptr;
    if (pOwner) {
        node = ccbReader->readNodeGraphFromFile(strCCBFileName.c_str(), pOwner);
    } else {
        node = ccbReader->readNodeGraphFromFile(strCCBFileName.c_str());
    }
    
    ccbReader->autorelease();
    
    return node;
}

void LayerManager::pushLayer(cocos2d::Node *pNode, bool shouldResetPos)
{
    if (pNode) {
        if (shouldResetPos) {
            pNode->setPosition(Vec2(0, 0) - originOffset);
        }
        addChild(pNode);
        v_layers.push_back(pNode);
    } else {
        log("pNode invalid! --LayerManager::pushLayer");
    }
}

Node* LayerManager::pushLayer(CCBClassType classType)
{
    Node* pNodeGet = getCCB(classType);
    if (pNodeGet) {
        pushLayer(pNodeGet);
        return pNodeGet;
    } else {
        CCLOG("Failed to get ccb from ccb class type");
        return nullptr;
    }
}

void LayerManager::closeLayer(int num /* = 1 */)
{
    if (v_layers.size() > num) {
        for (int i = 0; i < num; ++i) {
            Node* pNode = v_layers.back();
            pNode->removeFromParent();
            v_layers.pop_back();
        }
    } else {
        closeAll();
    }
}

void LayerManager::closeLayer(cocos2d::Node *pNode)
{
    if (pNode) {
        std::vector<Node*>::iterator end = v_layers.end();
        
        for (std::vector<Node*>::iterator iter = v_layers.begin(); iter != end; iter++) {
            Node* pItrNode = *iter;
            if (pItrNode == pNode) {
                v_layers.erase(iter);
                pItrNode->removeFromParent();
            }
        }
    } else {
        log("pNode invalid! --LayerManager::closeLayer");
    }
}

void LayerManager::closeAll()
{
    this->removeAllChildren();
    this->v_layers.clear();
}




