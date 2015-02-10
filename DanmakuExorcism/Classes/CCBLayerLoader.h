//
//  CCBLayerLoader.h
//  1024cpp
//
//  Created by WanThirty on 9/10/14.
//
//

#ifndef ___024cpp__CCBLayerLoader__
#define ___024cpp__CCBLayerLoader__

#include "LyHome.h"
class LyHomeLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LyHomeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LyHome);
};

#include "LySelectPlayer.h"
class LySelectPlayerLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LySelectPlayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LySelectPlayer);
};

#endif /* defined(___024cpp__CCBLayerLoader__) */





