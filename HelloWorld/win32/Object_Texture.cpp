#include "Object_Texture.h"
#include "st.h"

bool Object_Texture::init( TEXTURETYPE _type )
{
	if( !CCSprite::init() ) return false;

	type		= _type;
	nFrame		= 0;
	fFrameDelay	= 0.f;

	switch( type )
	{
	case TEX_COIN:
		{
			nCoin = 0;

			CCLabelTTF* pCoinText = CCLabelTTF::labelWithString( "Show Me The Money^^","±Ã¼­", 10.f );
			pCoinText->setAnchorPoint	( ccp(0.f, 0.f) );
			pCoinText->setPosition		( ccp(0.f, 0.f) );
			this->addChild( pCoinText, 0, 0 );

			bSpace = false;

			break;
		}
	case TEX_S1WALL:
		{
			CCSprite* pWallBase = CCSprite::spriteWithFile( "resource/S1_BGATEX_0.png" );
			pWallBase->setAnchorPoint( ccp(0.f, 0.f) );
			pWallBase->setPosition	 ( ccp(0.f, 0.f) );

			CCSprite* pWall = new CCSprite;
			pWall->init();
			pWall->setAnchorPoint( ccp(0.f, 0.f) );
			pWall->setPosition	 ( ccp(0.f, 0.f) );
			pWall->addAnimation	 ( st::call()->makeAnimation("resource/S1_WALL_", "S1WALL", 3) );

			this->addChild( pWallBase, 0, 0 );
			this->addChild( pWall	 , 1, 1 );

			st::call()->boxM.addBox(ccp(30.f, 20.f), ccp(50.f, 130.f), 30, this, BOX_TEXTURE, 2, 2 );

			break;
		}
	case TEX_S1ROOM:
		{
			CCSprite* pRoom = new CCSprite;
			pRoom->init();
			pRoom->setAnchorPoint( ccp(0.f, 0.f) );
			pRoom->setPosition	 ( ccp(0.f, 0.f) );
			pRoom->addAnimation	 ( st::call()->makeAnimation("resource/S1_BOSSROOM_", "S1ROOM", 4) );

			this->addChild( pRoom, 0, 0 );

			break;
		}
	case TEX_S1GENERAL:
		{
			CCSprite* pGeneral = new CCSprite;
			pGeneral->init			( );
			pGeneral->setAnchorPoint( ccp(0.f, 0.f) );
			pGeneral->setPosition	( ccp(0.f, 0.f) );
			pGeneral->addAnimation	( st::call()->makeAnimation("resource/GENERAL_FORWARD_", "S1GENERAL", 14) );

			this->addChild( pGeneral, 0, 0 );
			break;
		}
	}

	schedule( schedule_selector(Object_Texture::update) );
	return true;
}
void Object_Texture::update( float dt )
{
	switch( type )
	{
	case TEX_COIN:
		{
			if( GetAsyncKeyState(VK_SPACE) )
				bSpace = true;
			else if( bSpace == true )
			{
				st::call()->SM.play(SND_InCoin);

				bSpace = false;
				nCoin++;
			}

			if( nCoin > 0 ) 
			{
				if( nCoin >= 99 ) nCoin = 99;

				char szStr[64] = { 0 };
				sprintf_s( szStr, "CREDITS : %02d", nCoin );

				CCLabelTTF* pTTF = (CCLabelTTF*)this->getChildByTag( 0 );
				pTTF->setString  ( szStr );
				pTTF->setPosition( ccp(50.f, 0.8f) );
			}
			else
			{
				char szStr[64] = { 0 };
				sprintf_s( szStr, "Show Me The Money^^" );

				CCLabelTTF* pTTF = (CCLabelTTF*)this->getChildByTag( 0 );
				pTTF->setString  ( szStr );
				pTTF->setPosition( ccp(0.f, 0.8f) );
			}
			break;
		}
	case TEX_S1WALL:
		{
			Object_Texture* pWall = (Object_Texture*)this->getChildByTag( 1 );
			Object_Box*		pBox  = (Object_Box*)	 this->getChildByTag( 2 );

			if( pBox == NULL || pBox->getUseFlag() == false ) break;
			
			int nHP = pBox->getHP();

			if( nHP <= 0 )
			{
				st::call()->efM.addEffect( this->getPosition(), S1WALL_DESTROY, st::call()->worldNode );
				pBox->setUseFlag  ( false );
				this->setIsVisible( false );
			}

			if( st::call()->boxM.collisionObject(pBox, BOX_TEXTURE) )
				pBox->setHP( pBox->getHP() - 1 );

			if( nHP > 20 && nHP <= 30 )
			{
				pWall->setDisplayFrame( "S1WALL", 2 );
			}
			else if( nHP > 10 && nHP <= 20 )
			{
				if( nHP == 20 )
					st::call()->efM.addEffect( this->getPosition(), S1WALL_DESTROY, st::call()->worldNode );
				pWall->setDisplayFrame( "S1WALL", 1 );
			}
			else if( nHP > 0 && nHP <= 100 )
			{
				if( nHP == 10 )
					st::call()->efM.addEffect( this->getPosition(), S1WALL_DESTROY, st::call()->worldNode );
				pWall->setDisplayFrame( "S1WALL", 0 );
			}

			break;
		}
	case TEX_S1ROOM:
		{
			fFrameDelay += dt;

			if( fFrameDelay > 0.1f )
			{
				fFrameDelay = 0;
				nFrame++;

				if( nFrame >= 4 ) nFrame = 0;

				Object_Texture* pRoom = (Object_Texture*)this->getChildByTag( 0 );
				pRoom->setDisplayFrame( "S1ROOM", nFrame );
			}

			break;
		}
	case TEX_S1GENERAL:
		{
			fFrameDelay += dt;

			if( fFrameDelay > 0.1f )
			{
				fFrameDelay = 0.f;
				nFrame++;

				if( nFrame >= 13 ) nFrame = 0;

				Object_Texture* pGeneral = (Object_Texture*)this->getChildByTag( 0 );
				pGeneral->setDisplayFrame( "S1GENERAL", nFrame );
			}

			break;
		}
	}	
}