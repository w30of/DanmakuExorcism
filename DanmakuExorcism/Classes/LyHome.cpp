//
//  LyHome.cpp
//  1024cpp
//
//  Created by WanThirty on 9/10/14.
//
//

#include "LyHome.h"
#include "CCBLayerLoader.h"
#include "GameLogic.h"
#include "GamingLayer.h"

LyHome::LyHome()
: m_AnimationManager(nullptr)
, btnStart(nullptr)
, btnSetting(nullptr)
, btnGallery(nullptr)
, btnLeaders(nullptr)
{
    
}

LyHome::~LyHome()
{
    
}

/* ---------- CCB Bindings ---------- */
void LyHome::onNodeLoaded(cocos2d::Node *pNode, cocosbuilder::NodeLoader *pNodeLoader)
{
}

bool LyHome::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "btnStart", ControlButton*, this->btnStart);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "btnSetting", ControlButton*, this->btnSetting);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "btnGallery", ControlButton*, this->btnGallery);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "btnLeaders", ControlButton*, this->btnLeaders);
    return true;
}

SEL_MenuHandler LyHome::onResolveCCBCCMenuItemSelector(cocos2d::Ref *pTarget, const char *pSelectorName)
{
    return NULL;
}

Control::Handler LyHome::onResolveCCBCCControlSelector(cocos2d::Ref *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onStart", LyHome::onStart);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSetting", LyHome::onSetting);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onGallery", LyHome::onGallery);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onLeaders", LyHome::onLeaders);
    return NULL;
}
/* ---------- CCB Bindings End ---------- */


// control button callback...
void LyHome::onStart(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
//    GamingLayer* layer = GamingLayer::create();
//    layer->setPlayerType(PLAYER_DAOSHI);
//    
//    LayerManager::getInstance()->closeAll();
//    LayerManager::getInstance()->pushLayer(layer);
    LayerManager::getInstance()->closeAll();
    LayerManager::getInstance()->pushLayer(CCB_LY_SELECT_PLAYER);
}

void LyHome::onSetting(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    
}

void LyHome::onGallery(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    
}

void LyHome::onLeaders(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    
}





void LyHome::playAnime(const char * aniName)
{
    if (m_AnimationManager == nullptr) {
//        m_AnimationManager = m_pReader->getAnimationManager();
    }
    
    m_AnimationManager->runAnimationsForSequenceNamed(aniName);
}