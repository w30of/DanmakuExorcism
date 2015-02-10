#ifndef _CCB_CCNODELOADERLISTENER_H_
#define _CCB_CCNODELOADERLISTENER_H_


namespace cocosbuilder {

class CC_DLL NodeLoaderListener {
    public:
        /**
         * @js NA
         * @lua NA
         */
        virtual ~NodeLoaderListener() {
            CC_SAFE_RELEASE_NULL(m_pAnimationManager);
        };
        /**
         * @js NA
         * @lua NA
         */
        virtual void onNodeLoaded(cocos2d::Node * pNode, NodeLoader * pNodeLoader) = 0;
    
        virtual void setAnimationManager(CCBAnimationManager *pAnimationManager){
//            CC_SAFE_RETAIN(pReader);
            m_pAnimationManager = pAnimationManager;
            CC_SAFE_RETAIN(m_pAnimationManager);
        };
        
        CCBAnimationManager *m_pAnimationManager;
};

}

#endif
