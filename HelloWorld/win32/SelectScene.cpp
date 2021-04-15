#include "SelectScene.h"
#include "Stage1Scene.h"
#include "Object_Texture.h"
#include "st.h"

CCScene* SelectScene::create()
{
	CCScene*		pScene = new CCScene;
	pScene->init();

	SelectScene*	pLayer = new SelectScene;
	pLayer->init();

	pScene->addChild( pLayer );

	return pScene;
}
bool SelectScene::init()
{
	if( !CCLayer::init() ) return false;

	//st::call()->SM.play( SND_Select );

	fFrameDelay = 0.f;
	fIDLEDelay	= 0.f;
	fP1Delay	= 0.f;
	nFrame		= 0;
	nPrevFrame	= 0;
	nUHeroFrame = 0;
	nDHeroFrame = 0;
	iKeyNum		= 5;
	bStopFlag	= false;
	bPushEnter	= false;
	bDoorPlus	= false;
	bFadeFlag	= false;
	bGetKey		= false;
	bOKSound	= false;

	pSelect	 = new CCSprite;
	pSelect	-> init();
	this	-> addChild( pSelect );

	pBGA = CCSprite::spriteWithFile( "resource/SOLDIER_SELECT_0.png" );
	pBGA-> setAnchorPoint( ccp(0.f, 0.f) );
	pBGA-> setPosition	 ( ccp(0.f, 0.f) );
	pBGA-> setScale		 ( 3.36f );
	this-> addChild		 ( pBGA, 8 );

	pScreen = new CCSprite;
	pScreen-> init();
	pScreen-> setAnchorPoint( ccp(0.f, 0.f) );
	pScreen-> setPosition	( ccp(0.f, 0.f) );
	pScreen-> setScale		( 3.4f );
	this   -> addChild		( pScreen, 9 );


	pScreen-> addAnimation( st::call()->makeAnimation("resource/P1_Screen_", "P1_Screen", 8) );

	for( int i = 0; i < 4; i++ )
	{
		pDoor[i] = CCSprite::spriteWithFile( "resource/M2_0.png" );
		pDoor[i]-> setAnchorPoint( ccp(0.f, 0.f) );
		pDoor[i]-> setScale		 ( 3.4f );
		this	-> addChild		 ( pDoor[i], 4+i );
	}
 
	pDoor[0]->setPosition( ccp(60.f	, 92.f) );
	pDoor[1]->setPosition( ccp(287.f, 92.f) );
	pDoor[2]->setPosition( ccp(516.f, 92.f) );
	pDoor[3]->setPosition( ccp(745.f, 92.f) ); // max_up = 540.f, min_down = 92.f

	pCScreen = new CCSprite;
	pCScreen-> init();
	pCScreen-> setAnchorPoint( ccp(0.f, 0.f) );
	pCScreen-> setPosition	 ( ccp(8.f, 31.f) );
	pCScreen-> addAnimation	 ( st::call()->makeAnimation("resource/Char_Screen_", "Char_Screen", 1) );

	pUHero =  new CCSprite;
	pUHero->  init();
	pUHero->  setAnchorPoint( ccp(0.f, 0.f) );
	pUHero->  setPosition	( ccp(-28.f, -10.f) );
	pUHero->  addAnimation	( st::call()->makeAnimation("resource/STAND_BODY_HG_", "HG_STAND", 4) );
	pCScreen->addChild		( pUHero, 1 );

	
	pDHero = new CCSprite;
	pDHero->  init();
	pDHero->  setAnchorPoint( ccp(0.f, 0.f) );
	pDHero->  setPosition	( ccp(-28.f, -10.f) );
	pDHero->  addAnimation	( st::call()->makeAnimation("resource/STAND_LEG_", "S_LEG", 1) );
	pCScreen->addChild		( pDHero, 0 );

	for( int i = 0; i < 4; i++ )
	{
		pChar[i] = new CCSprite;
		pChar[i]-> init();
		pChar[i]-> setAnchorPoint( ccp(0.f, 0.f) );
		pChar[i]-> setPosition	 ( ccp(0.f, 0.f) );
		pChar[i]-> setScale		 ( 3.6f );
		this	-> addChild		 ( pChar[i], i );
	}

	pChar[0]-> addAnimation( st::call()->makeAnimation( "resource/Marco_"	, "Marco"	, 3) );
	pChar[1]-> addAnimation( st::call()->makeAnimation( "resource/Eri_"		, "Eri"		, 3) );
	pChar[2]-> addAnimation( st::call()->makeAnimation( "resource/Tarma_"	, "Tarma"	, 3) );
	pChar[3]-> addAnimation( st::call()->makeAnimation( "resource/Fio_"		, "Fio"		, 3) );

	pChar[0]-> setPosition	 ( ccp(45.f				, 92.f) );
	pChar[1]-> setPosition	 ( ccp(45.f + 67.f*3.6f	, 92.f) );
	pChar[2]-> setPosition	 ( ccp(25.f + 67.f*7.2f	, 92.f) );
	pChar[3]-> setPosition	 ( ccp(10.f + 67.f*10.8f, 92.f) );

	Object_Texture* pTTF = st::call()->TM.getChildByType( TEX_COIN );
	pTTF->setPosition( ccp( 605.f, 8.f) );
	pTTF->setScale( 3.45f );
	this->addChild( pTTF, 10 );

	schedule( schedule_selector(SelectScene::update) );

	return true;
}
void SelectScene::update( float dt )
{
	if( bStopFlag == false )
	{
		CGPoint pos1 = pDoor[0]->getPosition();
		CGPoint pos2 = pDoor[1]->getPosition();
		CGPoint pos3 = pDoor[2]->getPosition();
		CGPoint pos4 = pDoor[3]->getPosition();

		pos1.y += rand()%20;
		pos2.y += rand()%20;
		pos3.y += rand()%20;
		pos4.y += rand()%20;

		if( pos1.y >= 540.f ) pos1.y = 540.f;
		if( pos2.y >= 540.f ) pos2.y = 540.f;
		if( pos3.y >= 540.f ) pos3.y = 540.f;
		if( pos4.y >= 540.f ) pos4.y = 540.f;

		pDoor[0]->setPosition( pos1 );
		pDoor[1]->setPosition( pos2 );
		pDoor[2]->setPosition( pos3 );
		pDoor[3]->setPosition( pos4 );

		if( pos1.y >= 540.f &&
			pos2.y >= 540.f &&
			pos3.y >= 540.f &&
			pos4.y >= 540.f )
			bStopFlag = true;
		
		pChar[0]->setDisplayFrame( "Marco"	, 0 );
		pChar[1]->setDisplayFrame( "Eri"	, 0 );
		pChar[2]->setDisplayFrame( "Tarma"	, 0 );
		pChar[3]->setDisplayFrame( "Fio"	, 0 );

		return;
	}

	if( bPushEnter == false ) 
	{
		if( (GetAsyncKeyState(VK_LEFT) & 0x8001) == 0x8001 )
		{
			iKeyNum = KEY_LEFT;
			bGetKey = true;
		}
		else if( (GetAsyncKeyState(VK_RIGHT) & 0x8001) == 0x8001 )
		{
			iKeyNum = KEY_RIGHT;
			bGetKey = true;

		}
		else if( bGetKey == true )
		{
			bGetKey = false;

			st::call()->SM.play( SND_SelectM );

			if( iKeyNum == KEY_LEFT  ) nFrame--;
			if( iKeyNum == KEY_RIGHT ) nFrame++;
		}

		if( nFrame < 0 ) nFrame = 3;
		if( nFrame > 3 ) nFrame = 0;
	}

	if( nFrame != nPrevFrame )
	{
		nPrevFrame	= nFrame;
		fP1Delay	= 0.f;
	}

	switch( nFrame )
	{
	case 0:
		{
			pChar[0]->setDisplayFrame( "Marco"		, 1 );
			pChar[1]->setDisplayFrame( "Eri"		, 0 );
			pChar[2]->setDisplayFrame( "Tarma"		, 0 );
			pChar[3]->setDisplayFrame( "Fio"		, 0 );

			fP1Delay += dt;
			pScreen ->setPosition( ccp(84.f, 514.f) );

			if( fP1Delay > 0.1f ) 
			{
				if( (int)(fP1Delay*10) % 2 == 0 )
					pScreen ->setDisplayFrame( "P1_Screen"	, 1 );
				else
					pScreen ->setDisplayFrame( "P1_Screen"	, 0 );
			}
			else if( fP1Delay < 0.1f )
				pScreen ->setDisplayFrame( "P1_Screen"	, 0 );
			

			if( GetAsyncKeyState(VK_RETURN) || bPushEnter == true ) 
			{
				if( bOKSound == false )
				{
					bOKSound = true;
					st::call()->SM.play(SND_OK);
				}
				bPushEnter = true;
				pChar[0]->setDisplayFrame( "Marco", 2 );

				fFrameDelay += dt;
				fIDLEDelay	+= dt;

				if( fFrameDelay > 0.6f ) 
				{
					CGPoint pos = pDoor[0]->getPosition();
					pos.y -= 20;
					if( pos.y <= 92.f ) pos.y = 92.f;
					pDoor[0]->setPosition( pos );
				}

				if( fIDLEDelay > 0.1f )
				{
					fIDLEDelay = 0.f;
					nUHeroFrame++;
					nDHeroFrame++;

					if( nUHeroFrame >= 4 ) nUHeroFrame = 0;
					if( nDHeroFrame >= 1 ) nDHeroFrame = 0;
				}

				if( bDoorPlus == false )
				{
					pDoor[0]->addChild( pCScreen );
					bDoorPlus = true;
				} 
				pCScreen->setDisplayFrame( "Char_Screen", 0			  );
				pUHero	->setDisplayFrame( "HG_STAND"	, nUHeroFrame );
				pDHero	->setDisplayFrame( "S_LEG"		, nDHeroFrame );

				if( fFrameDelay > 2.5f ) 
				{
					st::call()->SM.stopSound( SND_Select );

					this->removeAllChildrenWithCleanup( true );
					CCDirector::sharedDirector()->replaceScene( Stage1Scene::create() );
				}

				return;
			}
			break;
		}
	case 1:
		{
			pChar[0]->setDisplayFrame( "Marco"	, 0 );
			pChar[1]->setDisplayFrame( "Eri"	, 1 );
			pChar[2]->setDisplayFrame( "Tarma"	, 0 );
			pChar[3]->setDisplayFrame( "Fio"	, 0 );

			fP1Delay += dt;
			pScreen ->setPosition( ccp(299.f, 514.f) );
			if( fP1Delay > 0.1f ) 
			{
				if( (int)(fP1Delay*10) % 2 == 0 )
					pScreen ->setDisplayFrame( "P1_Screen"	, 3 );
				else
					pScreen ->setDisplayFrame( "P1_Screen"	, 2 );
			}
			else if( fP1Delay < 0.1f )
				pScreen ->setDisplayFrame( "P1_Screen"	, 2 );


			if( GetAsyncKeyState(VK_RETURN) || bPushEnter == true ) 
			{
				bPushEnter = true;
				pChar[1]->setDisplayFrame( "Eri", 2 );

				fFrameDelay += dt;

				if( fFrameDelay > 0.6f ) 
				{
					CGPoint pos = pDoor[1]->getPosition();
					pos.y -= 20;
					if( pos.y <= 92.f ) pos.y = 92.f;
					pDoor[1]->setPosition( pos );
				}

				if( bDoorPlus == false )
				{
					pDoor[1]->addChild( pCScreen );
					bDoorPlus = true;
				}
				pCScreen->setDisplayFrame( "Char_Screen", 0 );

				return;
			}
			break;
		}
	case 2:
		{
			pChar[0]->setDisplayFrame( "Marco"	, 0 );
			pChar[1]->setDisplayFrame( "Eri"	, 0 );
			pChar[2]->setDisplayFrame( "Tarma"	, 1 );
			pChar[3]->setDisplayFrame( "Fio"	, 0 );

			fP1Delay += dt;
			pScreen ->setPosition( ccp(566.f, 514.f) );
			if( fP1Delay > 0.1f ) 
			{
				if( (int)(fP1Delay*10) % 2 == 0 )
					pScreen ->setDisplayFrame( "P1_Screen"	, 5 );
				else
					pScreen ->setDisplayFrame( "P1_Screen"	, 4 );
			}
			else if( fP1Delay < 0.1f )
				pScreen ->setDisplayFrame( "P1_Screen"	, 4 );

			if( GetAsyncKeyState(VK_RETURN) || bPushEnter == true ) 
			{
				bPushEnter = true;
				pChar[2]->setDisplayFrame( "Tarma", 2 );

				fFrameDelay += dt;

				if( fFrameDelay > 0.6f ) 
				{
					CGPoint pos = pDoor[2]->getPosition();
					pos.y -= 20;
					if( pos.y <= 92.f ) pos.y = 92.f;
					pDoor[2]->setPosition( pos );
				}

				if( bDoorPlus == false )
				{
					pDoor[2]->addChild( pCScreen );
					bDoorPlus = true;
				}
				pCScreen->setDisplayFrame( "Char_Screen", 0 );

				return;
			}
			break;
		}
	case 3:
		{
			pChar[0]->setDisplayFrame( "Marco"	, 0 );
			pChar[1]->setDisplayFrame( "Eri"	, 0 );
			pChar[2]->setDisplayFrame( "Tarma"	, 0 );
			pChar[3]->setDisplayFrame( "Fio"	, 1 );

			fP1Delay += dt;
			pScreen ->setPosition( ccp(783.f, 513.f) );
			if( fP1Delay > 0.1f ) 
			{
				if( (int)(fP1Delay*10) % 2 == 0 )
					pScreen ->setDisplayFrame( "P1_Screen"	, 7 );
				else
					pScreen ->setDisplayFrame( "P1_Screen"	, 6 );
			}
			else if( fP1Delay < 0.1f )
				pScreen ->setDisplayFrame( "P1_Screen"	, 6 );

			if( GetAsyncKeyState(VK_RETURN) || bPushEnter == true ) 
			{
				bPushEnter = true;
				pChar[3]->setDisplayFrame( "Fio", 2 );

				fFrameDelay += dt;

				if( fFrameDelay > 0.6f ) 
				{
					CGPoint pos = pDoor[3]->getPosition();
					pos.y -= 20;
					if( pos.y <= 92.f ) pos.y = 92.f;
					pDoor[3]->setPosition( pos );
				}

				if( bDoorPlus == false )
				{
					pDoor[3]->addChild( pCScreen );
					bDoorPlus = true;
				}
				pCScreen->setDisplayFrame( "Char_Screen", 0 );

				return;
			}
			break;
		}
	}
}