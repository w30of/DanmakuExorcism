//
//  Enemy.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-16.
//
//

#include "Enemy.h"
#include "DanmakuPool.h"
#include "GameLogic.h"

Enemy::Enemy()
: m_danmaku(nullptr)
{
    
}

Enemy::~Enemy()
{
    
}

bool Enemy::init()
{
    if (BulletGenerator::init())
    {
        initialize();
        return true;
    }
    return false;
}

void Enemy::initialize()
{
    m_danmaku = Danmaku::create();
    m_danmaku->setOwner(this);
    this->addChild(m_danmaku);
    setBulletGeneratorType(BulletGeneratorType::ENEMY);
}

// public func...
void Enemy::setEnemyInfo(EnemyInfo info)
{
    m_enemyInfo = info;
    // Init texture
    setSprite();
    // Show danmaku of enemy
    setDanmaku();
    // Enemy behavior hard code
    setEnemyBehavior();
    DanmakuPool::getInstance()->push(this);
}

EnemyInfo Enemy::getEnemyInfo()
{
    return m_enemyInfo;
}

void Enemy::shoot()
{
    this->m_danmaku->run();
}

void Enemy::stopShoot()
{
    m_danmaku->stop();
}

Vec2 Enemy::getShowPos()
{
    return m_enemyInfo.ShowPos;
}

Rect Enemy::getEnemyRect(bool isHalf /*= false*/)
{
    if (isHalf) {
        return Rect(this->getPosition().x - m_enemySize.width/3,
                    this->getPosition().y - m_enemySize.height/3,
                    m_enemySize.width/1.5f,
                    m_enemySize.height/1.5f);
    } else {
        return Rect(this->getPosition().x - m_enemySize.width/2,
                    this->getPosition().y - m_enemySize.height/2,
                    m_enemySize.width,
                    m_enemySize.height);
    }
}

void Enemy::setDanmaku()
{
    m_danmaku->setDanmakuType(m_enemyInfo.DmkID);
    m_danmaku->setDelay(m_enemyInfo.ShootDelay);
    m_danmaku->setCount(m_enemyInfo.ShootCount);
    m_danmaku->setInterval(m_enemyInfo.ShootInterval);
}

void Enemy::die()
{
    m_danmaku->stop();
    DanmakuPool::getInstance()->eraseEnemy(this);
    this->removeFromParent();
}

void Enemy::disappear()
{
    this->removeFromParent();
}


// private func...
void Enemy::setSprite()
{
    // Set texture
    TextureType txrType = m_enemyInfo.TxrID;
    if (txrType == TXR_BLUE_SOUL) {
        _sp = Sprite::create("texture/playertest.png");
    }
    this->addChild(_sp, 0);
    this->setContentSize(_sp->getContentSize());
    m_enemySize = Size(_sp->getContentSize().width + 10, _sp->getContentSize().height + 10);
}

void Enemy::removeFromPool()
{
    
}

void Enemy::runW3ScriptActions(std::string w3s)
{
    Vector<Sequence*> v_seqs = GameLogic::getInstance()->getW3Actions(w3s, this);
    size_t len = v_seqs.size();
    for (int i = 0; i < len; ++i) {
        Sequence* seq = v_seqs.at(i);
        this->runAction(seq);
     }
}

void Enemy::setEnemyBehavior()
{
    // These will help you...
    Size contentSize = this->getContentSize();
    Size winSize = GameLogic::getInstance()->winSize;
    Action *shoot = CallFunc::create([=](){  this->shoot();  });
    Action *remove = CallFunc::create([=](){  this->die();  });
    
    // Now, enemy will trying to kill you...
    /* Stage 1: initShot */
    if (m_enemyInfo.EnemyID == ENEMY_1_1 || m_enemyInfo.EnemyID == ENEMY_1_2)
    {
//        this->setPosition(m_enemyInfo.InitPos);
//        this->runW3ScriptActions(m_enemyInfo.CustomScript);
//        // Prepare...
        Vec2 startPos;
        if (m_enemyInfo.EnemyID == ENEMY_1_1) {
            startPos = Vec2(winSize.width + contentSize.width, winSize.height * 0.875);
        } else {
            startPos = Vec2(-contentSize.width, winSize.height * 0.875);
        }
        
        this->setPosition(startPos);
        
        Vec2 bcEndPos = m_enemyInfo.ShowPos;
        ccBezierConfig bc;
        bc.controlPoint_1 = Vec2(startPos.x - (startPos.x - bcEndPos.x)/2, startPos.y);
        bc.controlPoint_2 = Vec2(bcEndPos.x, (startPos.y - bcEndPos.y)/2 + bcEndPos.y);
        bc.endPosition = bcEndPos;
        
        int endPosX = m_enemyInfo.ShowPos.x;;
        if (m_enemyInfo.EnemyID == ENEMY_1_1) {
            endPosX -= 30*(3-m_enemyInfo.ShowCount);
        } else {
            endPosX += 30*(3-m_enemyInfo.ShowCount);
        }
        
        // Show...
        this->runAction(Sequence::create(EaseSineOut::create(BezierTo::create(1, bc)),
                                         shoot,
                                         MoveBy::create(1, Vec2(0, -50)),
                                         EaseSineIn::create(MoveTo::create(2, Vec2(endPosX, -contentSize.height))),
                                         remove,
                                         NULL));
    }
    else if (m_enemyInfo.EnemyID == ENEMY_1_3)
    {
        // Prepare...
        Vec2 startPos = Vec2(winSize.width/2, contentSize.height + winSize.height);
        Vec2 endPos = Vec2(winSize.width/2, -contentSize.height);
        
        this->setPosition(startPos);
        
        // Show...
        this->runAction(Sequence::create(EaseSineOut::create(MoveTo::create(1, m_enemyInfo.ShowPos)),
                                         shoot,
                                         DelayTime::create(1),
                                         EaseSineIn::create(MoveTo::create(2, endPos)),
                                         remove,
                                         NULL));
    }
    else if (m_enemyInfo.EnemyID == ENEMY_1_4_BOSS) {
        // Prepare...
        // Kill all enemies!
        DanmakuPool::getInstance()->clearOneThing(ENEMY, true);
        DanmakuPool::getInstance()->clearOneThing(ENEMY_BULLET, true);
        
        
        this->setPosition(m_enemyInfo.InitPos);
        this->setVisible(false);
        this->shoot();
        this->runAction(Sequence::create(DelayTime::create(3),
                                         Show::create(),
                                         NULL));
    }
    else
    {
        this->setPosition(m_enemyInfo.InitPos);
        this->runW3ScriptActions(m_enemyInfo.CustomScript);
    }
    
    /* Stage 1: watchDog */
    /* Stage 1: dangerClose */
    /* Stage 1: BOSS */
    
    GameLogic::getInstance()->gLayer->addChild(this, ZORDER_ENEMY);
}



