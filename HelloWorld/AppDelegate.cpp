#include "AppDelegate.h"
#include "win32/IntroScene.h"
#include "win32/Stage1Scene.h"

bool AppDelegate::applicationDidFinishLaunching()
{
	if (!(m_pMainWnd = new CCXEGLView()) || ! m_pMainWnd->Create(L"GameSchool", 1024, 768)){
			delete m_pMainWnd;
			return false;
	}


	CCDirector::sharedDirector()->setOpenGLView			( m_pMainWnd );
	CCDirector::sharedDirector()->setDeviceOrientation	( kCCDeviceOrientationPortrait );
	CCDirector::sharedDirector()->setDisplayFPS			( true );
	CCDirector::sharedDirector()->setAnimationInterval	( 1.0 / 60 );
	CCDirector::sharedDirector()->runWithScene			( IntroScene::create() );


	return true;
}