//
//  LyHome.h
//  1024cpp
//
//  Created by WanThirty on 9/10/14.
//
//

#ifndef ___DanmakuExorcism__LyHome__
#define ___DanmakuExorcism__LyHome__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"
#include "LayerManager.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class LyHome : public Layer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public NodeLoaderListener
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LyHome, create);
    LyHome();
    virtual ~LyHome();
    
    virtual void onNodeLoaded(cocos2d::Node * pNode, NodeLoader * pNodeLoader);
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    
    void playAnime(const char*);
    
private:
    
    CCBAnimationManager *m_AnimationManager;
    
    // ccb bindings...
    ControlButton* btnStart;
    ControlButton* btnSetting;
    ControlButton* btnGallery;
    ControlButton* btnLeaders;
    
    
    void onStart(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent);
    void onSetting(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent);
    void onGallery(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent);
    void onLeaders(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent);
};

#endif /* defined(___024cpp__LyHome__) */
