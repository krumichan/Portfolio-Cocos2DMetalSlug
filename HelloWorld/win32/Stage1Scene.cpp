#include "Stage1Scene.h"
#include "Object_Texture.h"
#include "Debug.h"
#include "st.h"

CCScene* Stage1Scene::create()
{
	CCScene*	 pScene = new CCScene;
	Stage1Scene* pLayer = new Stage1Scene;

	pScene->init();
	pLayer->init();
	pScene->addChild( pLayer );

	return pScene;
}
bool Stage1Scene::init()
{
	if( !CCLayer::init() ) return false;

	st::call()->SM.init();
	st::call()->SM.loading();
	st::call()->SM.play( SND_STAGE1 );

	fFrameDelay	= 0.f;
	fmax		= 0.f;
	nFrame		= 0;
	bGetBox		= false;

	fmax = st::call()->winSize.width * 0.5f;

	pBGA = CCSprite::spriteWithFile( "resource/S1_BGA.png" );
	pBGA-> setAnchorPoint( ccp(0.f, 0.f) );
	pBGA-> setPosition	 ( ccp(0.f, 0.f) );
	pBGA-> setScale		 ( 3.45f );
	this-> addChild		 ( pBGA, 0, S1_BGA );
	
	st::call()->TM.addTexture( ccp(318.f , 0.f ), TEX_S1WALL, pBGA, S1_WALL );
	st::call()->TM.addTexture( ccp(1312.f, 32.f), TEX_S1ROOM, pBGA, S1_ROOM );
	st::call()->boxM.addBox( ccp(600.f, 110.f) , ccp(1000.f, 130.f), pBGA, WALL );

	st::call()->worldNode = pBGA;

	pBGA->addChild( pHero = Object_Hero::create(), 1, S1_HERO );
	pHero->setPosition( ccp(50.f, 10.f) );

	this->addChild( Debug::create() );

	st::call()->boxM.loadData( pBGA );
	
	schedule( schedule_selector(Stage1Scene::update) );

	return true;
}
void Stage1Scene::update( float dt )
{
	Object_Texture* pWall = (Object_Texture*)pBGA->getChildByTag( S1_WALL );
	Object_Texture* pRoom = (Object_Texture*)pBGA->getChildByTag( S1_ROOM );

	// Wall

	if( pWall->getIsVisible() == true )
	{
		if (st::call()->makeWorldX(pWall->getPosition(), pBGA->getScale()) > 724.f )
			st::call()->InterpolateMoving( pBGA, pHero, fmax );

		return;
	}
	else if( pWall->getIsVisible() == false && pBGA->getChildByTag( 5 ) == NULL )
		st::call()->EM.addEnemy(ccp(400.f, 15.f), TURRET, pBGA, 5);

	// Wall Enemy
	Object_Enemy* pTurret = (Object_Enemy*)pBGA->getChildByTag( 5 );

	if( pTurret->getIsVisible() == true )
	{
		if (st::call()->makeWorldX(pWall->getPosition(), pBGA->getScale()) > 724.f )
			st::call()->InterpolateMoving( pBGA, pHero, fmax );
	}

	// BossRoom
	else
	{
		if( st::call()->makeWorldX(pRoom->getPosition(), pBGA->getScale()) > 0.f )
			st::call()->InterpolateMoving( pBGA, pHero, fmax );

		else
		{
			fFrameDelay += dt;

			if( fFrameDelay <= 2.f )
			{
				CGPoint pos = this->getPosition();
				pos.y -= 25.f * dt;
				this->setPosition( pos );
			}
			else
			{
				if( pBGA->getChildByTag(10) == NULL )
					st::call()->EM.addEnemy( ccp(1335.f, 300.f), BOSS, pBGA, 10 );
			}
		}

		if( pBGA->getChildByTag(25) == NULL )
			st::call()->TM.addTexture( ccp(1525.f, 25.f ), TEX_S1GENERAL, pBGA, 25 );
	}
}

