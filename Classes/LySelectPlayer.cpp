//
//  LySelectPlayer.cpp
//  DanmakuExorcism
//
//  Created by Wan Thirty on 15/1/6.
//
//

#include "LySelectPlayer.h"
#include "LayerManager.h"
#include "GameLogic.h"
#include "DataAdapter.h"

LySelectPlayer::LySelectPlayer()
: spPlayer(nullptr)
, lyTouchZone(nullptr)
, lyTreasures(nullptr)
, btnBack(nullptr)
, btnOK(nullptr)
, btnLeft(nullptr)
, btnRight(nullptr)
{
    m_player = nullptr;
}

LySelectPlayer::~LySelectPlayer()
{

}

/* ---------- CCB Bindings ---------- */
void LySelectPlayer::onNodeLoaded(cocos2d::Node *pNode, cocosbuilder::NodeLoader *pNodeLoader)
{
    prepare();
}

bool LySelectPlayer::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "spPlayer", Sprite*, this->spPlayer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "lyTouchZone", Layer*, this->lyTouchZone);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "lyTreasures", LayerColor*, this->lyTreasures);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "btnBack", ControlButton*, this->btnBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "btnOK", ControlButton*, this->btnOK);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "btnLeft", ControlButton*, this->btnLeft);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "btnRight", ControlButton*, this->btnRight);
    return true;
}

SEL_MenuHandler LySelectPlayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref *pTarget, const char *pSelectorName)
{
    return NULL;
}

Control::Handler LySelectPlayer::onResolveCCBCCControlSelector(cocos2d::Ref *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBack", LySelectPlayer::onBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onOK", LySelectPlayer::onOK);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onLeft", LySelectPlayer::onLeft);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRight", LySelectPlayer::onRight);
    return NULL;
}

void LySelectPlayer::onOK(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (m_isSelectingPlayer) {
        // Go to select treasures
        playAnimate("showTreasure");
        m_isSelectingPlayer = false;
        btnRight->getBackgroundSpriteForState(Control::State::NORMAL)->runAction(FadeOut::create(0.1));
        btnLeft->getBackgroundSpriteForState(Control::State::NORMAL)->runAction(FadeOut::create(0.1));
        btnRight->setEnabled(false);
        btnLeft->setEnabled(false);
    } else {
        // Go to fight!
        m_player->shoot(false);
        DanmakuPool::getInstance()->clearPool();
        LayerManager::getInstance()->closeAll();
        GamingLayer* layer = GamingLayer::create();
        layer->setPlayerType(PLAYER_DAOSHI);
        LayerManager::getInstance()->pushLayer(layer, false);
    }
}

void LySelectPlayer::onBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (m_isSelectingPlayer) {
        // Return to main layer
        DanmakuPool::getInstance()->clearPool();
        LayerManager::getInstance()->closeAll();
        LayerManager::getInstance()->pushLayer(CCB_LY_HOME);
    } else {
        // Go to select player
        playAnimate("showPlayer");
        m_isSelectingPlayer = true;
        btnRight->getBackgroundSpriteForState(Control::State::NORMAL)->runAction(FadeIn::create(0.1));
        btnLeft->getBackgroundSpriteForState(Control::State::NORMAL)->runAction(FadeIn::create(0.1));
        btnRight->setEnabled(true);
        btnLeft->setEnabled(true);
    }
}

void LySelectPlayer::onLeft(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    switchPlayer(-1);
}

void LySelectPlayer::onRight(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    switchPlayer(1);
}
/* ---------- CCB Bindings End ---------- */

void LySelectPlayer::prepare()
{
    // Player data init
    m_idx = 0; // Default is the first player
    PlayerInfo piDaoshi;
    piDaoshi.pType = PLAYER_DAOSHI;
    piDaoshi.pName = "莲";
    piDaoshi.picName = FILE_DAOSHI_FULL;
    piDaoshi.pDesc = "四海为家的云游道士，使用道符与桃木剑与鬼怪战斗。";
    
    PlayerInfo piHeShang;
    piHeShang.pType = PLAYER_HESHANG;
    piHeShang.pName = "空";
    piHeShang.picName = FILE_HESHANG_FULL;
    piHeShang.pDesc = "下山普度众生的武僧，使用佛珠配合诵念经文来退制鬼怪。";
    
    PlayerInfo piJianKe;
    piJianKe.pType = PLAYER_JIANKE;
    piJianKe.pName = "炼";
    piJianKe.picName = FILE_JIANKE_FULL;
    piJianKe.pDesc = "下山普度众生的武僧，使用佛珠配合诵念经文来退制鬼怪。";
    
    m_vPlayerInfo.push_back(piDaoshi);
    m_vPlayerInfo.push_back(piHeShang);
    m_vPlayerInfo.push_back(piHeShang);
    m_piMaxSize = (int)m_vPlayerInfo.size();

    m_spPlayerOriginPos = spPlayer->getPosition();
    
    // Player bullets need a container, init it
    GameLogic::getInstance()->gLayer = lyTouchZone;
    
    // Show cutin animate
    switchPlayer(m_idx);
    
    // Init touch zone rect
    m_touchZoneRect = Rect(lyTouchZone->getPositionX(),
                           lyTouchZone->getPositionY(),
                           lyTouchZone->getContentSize().width,
                           lyTouchZone->getContentSize().height);
    GameLogic::setGameRect(Rect(0, 0, lyTouchZone->getContentSize().width, lyTouchZone->getContentSize().height));
    
    // Register touch zone
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(LySelectPlayer::zoneTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(LySelectPlayer::zoneTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(LySelectPlayer::zoneTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, lyTouchZone);
    
    m_isSelectingPlayer = true;
    
    // Init table view...
    Size containerSize = lyTreasures->getContentSize();
    // Calc by cell count, cannot larger than lyTreasures`s height
    float tableHeight = 100*2;
    tableHeight = tableHeight > containerSize.height ? containerSize.height : tableHeight;
    
    // Then create treasures
    TableView* tableView = TableView::create(this, Size(containerSize.width, tableHeight));
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setDelegate(this);
    lyTreasures->addChild(tableView);
    tableView->setPositionY(containerSize.height - tableHeight);
    tableView->reloadData();
    tableView->setBounceable(false);
}



/* Scroll view start */
void LySelectPlayer::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    bool selected = ((TreasureCell*)cell)->select();
    m_selectedMap[(int)cell->getIdx()] = selected;
}

void LySelectPlayer::tableCellHighlight(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    ((TreasureCell*)cell)->setHighlight(true);
}

void LySelectPlayer::tableCellUnhighlight(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    ((TreasureCell*)cell)->setHighlight(false);
}

Size LySelectPlayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
    return Size(280, 100);
}

TableViewCell* LySelectPlayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TreasureCell* cell = (TreasureCell*)table->dequeueCell();
    if (!cell) {
        // Init your cell here...
        cell = new (std::nothrow) TreasureCell();
        cell->autorelease();
        TreasureInfo ti = DataAdapter::getInstance()->v_treasureList.at(idx);
        cell->setTreasureInfo(ti);
    } else {
        // refresh your cell here...
    }
    return cell;
}

ssize_t LySelectPlayer::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return DataAdapter::getInstance()->v_treasureList.size();
}
/* Scroll view end */

void LySelectPlayer::switchPlayer(int idxOff)
{
    m_idx += idxOff;
    if (m_idx >= 0 && m_idx < m_piMaxSize)
    {
        PlayerInfo pi = m_vPlayerInfo.at(m_idx);
        spPlayer->setTexture(pi.picName);
        
        if (!m_player) {
            m_player = Player::create();
            m_player->setPlayerInfo(pi.pType, 2);
            m_player->setPositionX(522);
            lyTouchZone->addChild(m_player, ZORDER_PLAYER);
        } else {
            m_player->setPlayerInfo(pi.pType, 2);
            m_player->shoot(false);
        }
        
        if (idxOff > 0) {
            playAnimate("switchLeft");
        } else {
            playAnimate("switchRight");
        }
        this->runAction(Sequence::create(DelayTime::create(0.2),
                                         CallFunc::create([=](){m_player->shoot(true);}),
                                         NULL));
        
        protectIdx();
    } else {
        protectIdx();
    }
}

void LySelectPlayer::protectIdx()
{
    if (m_idx <= 0) {
        btnLeft->setVisible(false);
        m_idx = 0;
    } else {
        btnLeft->setVisible(true);
    }
    if (m_idx >= m_piMaxSize - 1) { // -1 to get the max valid index
        btnRight->setVisible(false);
        m_idx = m_piMaxSize - 1;
    } else {
        btnRight->setVisible(true);
    }
}

// For touch zone
bool LySelectPlayer::zoneTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (!m_isSelectingPlayer) return false;
    
    Vec2 pt = touch->getLocation();
    pt = this->convertToNodeSpace(pt);
    if (m_touchZoneRect.containsPoint(pt)) {
        return true;
    } else {
        return false;
    }
}

void LySelectPlayer::zoneTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    // TODO: Move player ship
    float dtX = touch->getDelta().x;
    spPlayer->setPositionX(spPlayer->getPositionX()+dtX*0.1);
}

void LySelectPlayer::zoneTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    // Start x - End x
    spPlayer->stopAllActions();
    spPlayer->runAction(EaseExponentialOut::create(MoveTo::create(0.5f, m_spPlayerOriginPos)));
    int offX = touch->getStartLocation().x - touch->getLocation().x;
    if (offX < -50) {
        switchPlayer(-1);
    } else if (offX > 50) {
        switchPlayer(1);
    }
}


// Treasure Cell
TreasureCell::TreasureCell()
{
    m_hasInit = false;
    m_isSelected = false;
    m_spIcon = nullptr;
    m_lbName = nullptr;
    m_lbDesc = nullptr;
    m_lycBackground = nullptr;
}

TreasureCell::~TreasureCell()
{
    
}

void TreasureCell::prepare()
{
    
}

void TreasureCell::setTreasureInfo(TreasureInfo ti)
{
    m_ti = ti;
    std::string strName;
    strName.append(m_ti.Name);
    strName.append(" ");
    strName.append(StringUtils::format("Lv.%d",m_ti.lv));
    
    if (m_hasInit) {
        m_hasInit = true;
        m_spIcon->setTexture(m_ti.IconName);
        m_lbName->setString(strName.c_str());
        m_lbDesc->setString(m_ti.Desc);
    } else {
        m_lycBackground = LayerColor::create(Color4B(0, 0, 0, 0), 280, 100);
        this->addChild(m_lycBackground);
        
        m_spIcon = Sprite::create(m_ti.IconName);
        m_spIcon->setPosition(Vec2(50, 50));
        this->addChild(m_spIcon);
        
        m_lbName = Label::createWithSystemFont(strName, "Helvetica-Bold", 28);
        m_lbName->setAnchorPoint(Vec2(0, 0));
        m_lbName->setPosition(Vec2(90, 60));
        this->addChild(m_lbName);
        
        m_lbDesc = Label::createWithSystemFont(ti.Desc, "Helvetica-Bold", 22);
        m_lbDesc->setVerticalAlignment(TextVAlignment::CENTER);
        m_lbDesc->setAnchorPoint(Vec2(0, 1));
        m_lbDesc->setPosition(Vec2(85, 60));
        m_lbDesc->setDimensions(180, 56);
        this->addChild(m_lbDesc);
        
        this->setContentSize(Size(280, 100));
    }
    
}

bool TreasureCell::select()
{
    m_isSelected = !m_isSelected;
    setHighlight(m_isSelected);
    return m_isSelected;
}

void TreasureCell::setHighlight(bool isHighlight)
{
    int o = isHighlight || m_isSelected ? 255 : 0;
    m_lycBackground->setOpacity(o);
}





