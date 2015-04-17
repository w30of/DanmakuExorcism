//
//  LySelectPlayer.h
//  DanmakuExorcism
//
//  Created by Wan Thirty on 15/1/6.
//
//

#ifndef __DanmakuExorcism__LySelectPlayer__
#define __DanmakuExorcism__LySelectPlayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"
#include "Player.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class LySelectPlayer : public Layer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public NodeLoaderListener,
public cocos2d::extension::TableViewDataSource,
public cocos2d::extension::TableViewDelegate
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LySelectPlayer, create);
    LySelectPlayer();
    virtual ~LySelectPlayer();
    
    // CCB Bindings...
    virtual void onNodeLoaded(cocos2d::Node * pNode, NodeLoader * pNodeLoader);
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    
    // Table view...
    virtual void scrollViewDidScroll(ScrollView* view) {};
    virtual void scrollViewDidZoom(ScrollView* view) {}
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual void tableCellHighlight(TableView* table, TableViewCell* cell);
    virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    void playAnime(const char* aniName, cocos2d::SEL_CallFunc callfunc = nullptr);
    
private:
    // inner funcs...
    void prepare();
    void switchPlayer(int idxOff);
    void protectIdx();
    
    bool zoneTouchBegan(Touch* touch, Event  *event);
    void zoneTouchMoved(Touch* touch, Event  *event);
    void zoneTouchEnded(Touch* touch, Event  *event);
    
    // members...
    CCBAnimationManager *m_AnimationManager;    // For player animate
    std::vector<PlayerInfo> m_vPlayerInfo;      // Player info container
    std::map<int, bool> m_selectedMap;
    int m_idx;                                  // Now selected index
    int m_piMaxSize;                            // Max size of player info container
    bool m_isSelectingPlayer;
    
    Rect m_touchZoneRect;
    Vec2 m_spPlayerOriginPos;
    
    Player* m_player;
    
    // ccb bindings...
    Sprite* spPlayer;
    Layer* lyTouchZone;
    LayerColor* lyTreasures;
    
    ControlButton* btnBack;
    ControlButton* btnOK;
    ControlButton* btnLeft;
    ControlButton* btnRight;
    void onBack(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent);
    void onOK(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent);
    void onLeft(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent);
    void onRight(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent);
};

class TreasureCell : public cocos2d::extension::TableViewCell
{
public:
    TreasureCell();
    virtual ~TreasureCell();
    
    void setTreasureInfo(TreasureInfo ti);
    bool select();
    void setHighlight(bool isHighlight);
    
private:
    
    void prepare();
    
    bool m_hasInit;
    bool m_isSelected;
    TreasureInfo m_ti;
    Sprite* m_spIcon;
    Label* m_lbName;
    Label* m_lbDesc;
    LayerColor* m_lycBackground;
};


#endif /* defined(__DanmakuExorcism__LySelectPlayer__) */
