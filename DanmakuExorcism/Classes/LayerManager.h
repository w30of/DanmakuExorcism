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

USING_NS_CC;

class LayerManager : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(LayerManager);
    
    static LayerManager *getInstance();
    
    // funcs...
    void pushLayer(Node*);
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
