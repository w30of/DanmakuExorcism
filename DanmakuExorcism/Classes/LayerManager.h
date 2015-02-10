//
//  LayerManager.h
//  DanmakuExorcism
//
//  Created by WanThirty on 14-10-14.
//
//

#ifndef __DanmakuExorcism__LayerManager__
#define __DanmakuExorcism__LayerManager__

#include "cocos2d.h"
#include "Protocol.h"
#include "cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class LayerManager : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(LayerManager);
    
    static LayerManager *getInstance();
    
    // funcs...
    Node* getCCB(CCBClassType classType, Ref* pOwner = nullptr);
    // show layer
    void pushLayer(Node*);
    Node* pushLayer(CCBClassType classType);
    // close layer
    void closeLayer(int num = 1);
    void closeLayer(Node*);
    void closeAll();
    
private:
    LayerManager();
    virtual ~LayerManager();
    
    void prepare();
    
    std::vector<Node*> v_layers;
};

#endif /* defined(__DanmakuExorcism__LayerManager__) */
