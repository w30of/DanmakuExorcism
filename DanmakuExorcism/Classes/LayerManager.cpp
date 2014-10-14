//
//  LayerManager.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-14.
//
//

#include "LayerManager.h"

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
    this->setContentSize(Size(640,960));
    this->setAnchorPoint(Point::ZERO);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (visibleSize.width / visibleSize.height > this->getContentSize().width / this->getContentSize().height)
    {
        this->setScale(visibleSize.height / this->getContentSize().height);
        float sclRate = visibleSize.height / this->getContentSize().height;
        this->setPosition((visibleSize.width - this->getContentSize().width * sclRate) / 2, 0);
    } else {
        this->setScale(visibleSize.width / this->getContentSize().width);
        float sclRate = visibleSize.width / this->getContentSize().width;
        this->setPosition(0, (visibleSize.height - this->getContentSize().height * sclRate) / 2);
    }
}

void LayerManager::pushLayer(cocos2d::Node *pNode)
{
    if (pNode) {
        addChild(pNode);
        v_layers.push_back(pNode);
    } else {
        log("pNode invalid! --LayerManager::pushLayer");
    }
}

void LayerManager::closeLayer(int num /*= 1*/)
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




