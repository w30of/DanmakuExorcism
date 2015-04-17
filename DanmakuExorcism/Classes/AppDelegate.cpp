#include "AppDelegate.h"
#include "GamingScene.h"
#include "LayerManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    // Adjust screen, keep layer in the center of screen
    Size s = Size(768, 1136);
    Size deviceSize = Director::getInstance()->getVisibleSize();
    float width = 768;
    float height = 1136;
    
    if (deviceSize.width <= s.width) {
        if (deviceSize.height > s.height) {
            // There`s a border up on top and bottom, fill them
            width = floorf(s.height * (deviceSize.width / deviceSize.height));
        } else {
            width = deviceSize.width;
            height = deviceSize.height;
        }
    } else {
        float scaleRate = deviceSize.width / s.width;
        if (s.height * scaleRate < deviceSize.height) {
            // There`s a border up on top and bottom, fill them
            scaleRate = s.height / deviceSize.height;
            width = floorf(width * scaleRate);
        } else {
            height = floorf(height / scaleRate);
        }
        
        float deviceHeightScaled = s.width / (deviceSize.width / deviceSize.height);
        height = floorf(deviceHeightScaled);
    }
    LayerManager::getInstance()->originOffset = Vec2((768 - width)/2, (1136 - height)/2);
    LayerManager::getInstance()->setContentSize(Size(width, height));

    glview->setDesignResolutionSize(width, height, ResolutionPolicy::SHOW_ALL);
    
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = GamingScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
