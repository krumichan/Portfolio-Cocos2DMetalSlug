#include "IntroScene.h"
#include "SelectScene.h"
#include "Object_Texture.h"
#include "st.h"

CCScene* IntroScene::create()
{
	CCScene* pScene = new CCScene;
	pScene->init();

	IntroScene* pLayer = new IntroScene;
	pLayer->init();

	pScene->addChild( pLayer );

	return pScene;
}
bool IntroScene::init()
{
	if( !CCLayer::init() ) return false;

	fFrameDelay		= 0.f;
	nFrame			= 0;
	nCoin			= 0;
	bGetEnter		= false;
	bGetSpace		= false;
	bOpeningSound	= false;
	bOpening		= false;

	pIntro = new CCSprite;
	pIntro->init();
	pIntro->setAnchorPoint	( ccp(0.f, 0.f) );
	pIntro->setPosition		( ccp(0.f, 0.f) );
	pIntro->addAnimation	( st::call()->makeAnimation( "resource/Opening_"	, "Opening"		, 103) );
	this  ->addChild		( pIntro );

	pStart = new CCSprite;
	pStart->init();
	pStart->setAnchorPoint	( ccp(0.f , 0.f ) );
	pStart->setPosition		( ccp(83.f, 19.f) );
	pStart->addAnimation	( st::call()->makeAnimation( "resource/PRESSSTART_"	, "PressStart"	, 2  ) );
	this  ->addChild		( pStart );

	this->setScale		( 3.45f );
	this->setPosition	( ccp(0.f, 0.f) );
	this->setAnchorPoint( ccp(0.f, 0.f) );

	st::call()->SM.init		( );
	st::call()->SM.loading	( );

	schedule( schedule_selector(IntroScene::update) );
	return true;
}
void IntroScene::update( float dt )
{
	fFrameDelay += dt;

	if( fFrameDelay > 0.0313f && bOpening == false )
	{
		if( bOpeningSound == false )
		{
			bOpeningSound = true;
			st::call()->SM.play( SND_Opening );
		}
		fFrameDelay = 0.f;
		nFrame++;
		
		if( nFrame >= 103 ) 
		{
			fFrameDelay = 0.f;
			nFrame		= 0;
			bOpening	= true;

			st::call()->TM.addTexture( ccp(175.f, 2.f), TEX_COIN, this, 1 );

			return;
		}
		pIntro->setDisplayFrame( "Opening", nFrame );
	}

	if( bOpening == true )
	{
		if( fFrameDelay > 0.2f )
		{
			fFrameDelay = 0.f;
			nFrame++;

			if( nFrame >= 2 ) nFrame = 0;
			pStart->setDisplayFrame( "PressStart", nFrame );
		}
	
		Object_Texture* pCoin = (Object_Texture*)this->getChildByTag( 1 );
		if( bGetEnter == false )
		{
			if ( GetAsyncKeyState(VK_RETURN) )
				bGetEnter = true;
		}
		else if( bGetEnter == true && pCoin->GetCoin() > 0 )
		{
			pCoin->SetCoin( pCoin->GetCoin() - 1 );

			this->removeChild( this->getChildByTag(1), false );
			this->removeAllChildrenWithCleanup( true );
			
			st::call()->SM.stopSound( SND_Opening );
			CCDirector::sharedDirector()->replaceScene( SelectScene::create() );
		}
	}
}
