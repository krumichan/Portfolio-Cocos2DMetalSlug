#include "Object_Effect.h"
#include "st.h"

bool Object_Effect::init( EFFECTTYPE _type )
{
	if( !CCSprite::init() ) return false;
	fDelay	= 0.f;
	nFrame	= 0;
	iType	= _type;

	switch( iType )
	{
	case TURRET_EFFECT:
		{
			CCSprite* pTurret = new CCSprite;
			pTurret->init();
			pTurret->setAnchorPoint	( ccp(0.f, 0.f) );
			pTurret->setPosition	( ccp(0.f, 0.f) );
			this->addChild			( pTurret, 0, 0 );

			pTurret->addAnimation( st::call()->makeAnimation("resource/EF_HUGE_EXPLOSION_", "TURRET_EFFECT", 24) );
			nMaxFrame = pTurret->animationByName(getEffectString())->getFrames()->count();

			st::call()->boxM.addBox( ccp(30.f, 30.f), ccp(120.f, 120.f), this, BOX_ENEMYATTACK, 1 );

			break;
		}
	case HG_EFFECT:
		{
			CCSprite* pHG = new CCSprite;
			pHG->init			( );
			pHG->setAnchorPoint	( ccp(0.f, 0.f) );
			pHG->setPosition	( ccp(0.f, 0.f) );
			this->addChild		( pHG, 0, 0		);
			this->setRotation	( -90.f			);

			pHG->addAnimation( st::call()->makeAnimation("resource/BULLET_EF_", "HG_EFFECT", 9) );

			nMaxFrame = pHG->animationByName(getEffectString())->getFrames()->count();
			break;
		}
	case S1WALL_DESTROY:
		{
			CCSprite* pDes0 = new CCSprite;
			pDes0->init				( );
			pDes0->setAnchorPoint	( ccp(0.f, 0.f ) );
			pDes0->setPosition		( ccp(0.f, 30.f) );
			pDes0->addAnimation		( st::call()->makeAnimation("resource/EF_BRICK_", "S1WALL_DESTROY", 6) );

			CCSprite* pDes1 = new CCSprite;
			pDes1->init				( );
			pDes1->setAnchorPoint	( ccp(0.f , 0.f ) );
			pDes1->setPosition		( ccp(40.f, 30.f) );
			pDes1->addAnimation		( st::call()->makeAnimation("resource/EF_BRICK_", "S1WALL_DESTROY", 6) );

			CCSprite* pDes2 = new CCSprite;
			pDes2->init				( );
			pDes2->setAnchorPoint	( ccp(0.f, 0.f ) );
			pDes2->setPosition		( ccp(0.f, 60.f) );
			pDes2->addAnimation		( st::call()->makeAnimation("resource/EF_BRICK_", "S1WALL_DESTROY", 6) );

			CCSprite* pDes3 = new CCSprite;
			pDes3->init				( );
			pDes3->setAnchorPoint	( ccp(0.f , 0.f ) );
			pDes3->setPosition		( ccp(40.f, 60.f) );
			pDes3->addAnimation		( st::call()->makeAnimation("resource/EF_BRICK_", "S1WALL_DESTROY", 6) );

			CCSprite* pDes4 = new CCSprite;
			pDes4->init				( );
			pDes4->setAnchorPoint	( ccp(0.f, 0.f ) );
			pDes4->setPosition		( ccp(0.f, 80.f) );
			pDes4->addAnimation		( st::call()->makeAnimation("resource/EF_BRICK_", "S1WALL_DESTROY", 6) );

			CCSprite* pDes5 = new CCSprite;
			pDes5->init				( );
			pDes5->setAnchorPoint	( ccp(0.f , 0.f ) );
			pDes5->setPosition		( ccp(40.f, 80.f) );
			pDes5->addAnimation		( st::call()->makeAnimation("resource/EF_BRICK_", "S1WALL_DESTROY", 6) );

			CCSprite* pDes6 = new CCSprite;
			pDes6->init				( );
			pDes6->setAnchorPoint	( ccp(0.f, 0.f  ) );
			pDes6->setPosition		( ccp(0.f, 100.f) );
			pDes6->addAnimation		( st::call()->makeAnimation("resource/EF_BRICK_", "S1WALL_DESTROY", 6) );

			CCSprite* pDes7 = new CCSprite;
			pDes7->init				( );
			pDes7->setAnchorPoint	( ccp(0.f , 0.f  ) );
			pDes7->setPosition		( ccp(40.f, 100.f) );
			pDes7->addAnimation		( st::call()->makeAnimation("resource/EF_BRICK_", "S1WALL_DESTROY", 6) );

			this->addChild( pDes0, 0, 0 );
			this->addChild( pDes1, 0, 1 );
			this->addChild( pDes2, 0, 2 );
			this->addChild( pDes3, 0, 3 );
			this->addChild( pDes4, 0, 4 );
			this->addChild( pDes5, 0, 5 );
			this->addChild( pDes6, 0, 6 );
			this->addChild( pDes7, 0, 7 );

			nMaxFrame = pDes0->animationByName(getEffectString())->getFrames()->count();

			break;
		}
	case GRENADE_EFFECT:
		{
			CCSprite* pGrenade = new CCSprite;
			pGrenade->init			( );
			pGrenade->setAnchorPoint( ccp(0.f, 0.f)  );
			pGrenade->setPosition	( ccp(0.f, 0.f)  );
			pGrenade->addAnimation	( st::call()->makeAnimation("resource/EF_GRENADE_", "GRENADE_EFFECT", 29) );
			this	->addChild		( pGrenade, 0, 0 );

			st::call()->boxM.addBox( ccp(95.f, 35.f), ccp(155.f, 190.f), this, BOX_HEROGRENADE, 1 );
			nMaxFrame = pGrenade->animationByName(getEffectString())->getFrames()->count();

			break;
		}
	case S1BOSSENGINE_EFFECT:
		{
			CCSprite* pLeftEngine = new CCSprite;
			pLeftEngine->init			( );
			pLeftEngine->setAnchorPoint	( ccp(0.f, 0.f) );
			pLeftEngine->setPosition	( ccp(0.f, 0.f) );
			pLeftEngine->addAnimation	( st::call()->makeAnimation("resource/EF_BOSS_ENGINE_", "LEFT_ENGINE", 4) );
			this	   ->addChild		( pLeftEngine, 0, 0 );

			CCSprite* pRightEngine = new CCSprite;
			pRightEngine->init			( );
			pRightEngine->setAnchorPoint( ccp(0.f  , 0.f) );
			pRightEngine->setPosition	( ccp(215.f, 0.f) );
			pRightEngine->addAnimation	( st::call()->makeAnimation("resource/EF_BOSS_ENGINE_R_", "RIGHT_ENGINE", 4) );
			this	    ->addChild		( pRightEngine, 0, 1 );

			nMaxFrame = pLeftEngine->animationByName("LEFT_ENGINE")->getFrames()->count();

			break;
		}
	case S1BOSSATTACKREADY_EFFECT:
		{
			CCSprite* pLeftReady = new CCSprite;
			pLeftReady->init			( );
			pLeftReady->setAnchorPoint	( ccp(0.f, 0.f) );
			pLeftReady->setPosition		( ccp(0.f, 0.f) );
			pLeftReady->addAnimation	( st::call()->makeAnimation("resource/EF_BOSS_L_AT_READY_", "LEFT_READY", 9) );
			this	   ->addChild		( pLeftReady, 0, 0 );

			CCSprite* pRightReady = new CCSprite;
			pRightReady->init			( );
			pRightReady->setAnchorPoint ( ccp(0.f  , 0.f) );
			pRightReady->setPosition	( ccp(205.f, 0.f) );
			pRightReady->addAnimation	( st::call()->makeAnimation("resource/EF_BOSS_AT_READY_", "RIGHT_READY", 9) );
			this	    ->addChild		( pRightReady, 0, 1 );

			nMaxFrame = pLeftReady->animationByName("LEFT_READY")->getFrames()->count();

			break;
		}
	case S1BOSSATTACK_EFFECT:
		{
			CCSprite* pLeftAttack = new CCSprite;
			pLeftAttack->init			( );
			pLeftAttack->setAnchorPoint	( ccp(0.f, 0.f) );
			pLeftAttack->setPosition	( ccp(0.f, 0.f) );
			pLeftAttack->addAnimation	( st::call()->makeAnimation("resource/EFFECT_BOSS_ATTACK_L_", "LEFT_ATTACK", 6) );
			this	   ->addChild		( pLeftAttack, 0, 0 );

			CCSprite* pRightAttack = new CCSprite;
			pRightAttack->init			 ( );
			pRightAttack->setAnchorPoint ( ccp(0.f  , 0.f) );
			pRightAttack->setPosition	 ( ccp(205.f, 0.f) );
			pRightAttack->addAnimation	 ( st::call()->makeAnimation("resource/EFFECT_BOSS_ATTACK_R_", "RIGHT_ATTACK", 6) );
			this	    ->addChild		 ( pRightAttack, 0, 1 );

			nMaxFrame = pLeftAttack->animationByName("LEFT_ATTACK")->getFrames()->count();

			break;
		}
	case S1BOSSATTACKEND_EFFECT:
		{
			CCSprite* pLeftEnd = new CCSprite;
			pLeftEnd->init				( );
			pLeftEnd->setAnchorPoint	( ccp(0.f, 0.f) );
			pLeftEnd->setPosition		( ccp(0.f, 0.f) );
			pLeftEnd->addAnimation		( st::call()->makeAnimation("resource/EFFECT_BOSS_DELAY_L_", "LEFT_END", 15) );
			this	->addChild			( pLeftEnd, 0, 0 );

			CCSprite* pRightEnd = new CCSprite;
			pRightEnd->init				( );
			pRightEnd->setAnchorPoint	( ccp(0.f  , 0.f) );
			pRightEnd->setPosition		( ccp(205.f, 0.f) );
			pRightEnd->addAnimation		( st::call()->makeAnimation("resource/EFFECT_BOSS_DELAY_R_", "RIGHT_END", 15) );
			this	 ->addChild			( pRightEnd, 0, 1 );

			nMaxFrame = pLeftEnd->animationByName("LEFT_END")->getFrames()->count();

			break;
		}
	}

	schedule( schedule_selector(Object_Effect::update) );
	return true;
}

const char* Object_Effect::getEffectString( )
{
	switch( iType )
	{
	case TURRET_EFFECT:				return "TURRET_EFFECT";
	case HG_EFFECT:					return "HG_EFFECT";
	case S1WALL_DESTROY:			return "S1WALL_DESTROY";
	case GRENADE_EFFECT:			return "GRENADE_EFFECT";
	case S1BOSSENGINE_EFFECT:		return "S1BOSSENGINE_EFFECT";
	case S1BOSSATTACKREADY_EFFECT:	return "S1BOSSATTACKREADY_EFFECT";
	case S1BOSSATTACK_EFFECT:		return "S1BOSSATTACK_EFFECT";
	case S1BOSSATTACKEND_EFFECT:	return "S1BOSSATTACKEND_EFFECT";
	}
}

void Object_Effect::update( float dt )
{

	if( iType == S1WALL_DESTROY )
	{
		fDelay += dt;

		if(fDelay > 0.07f )
		{
			CCSprite* pDes0 = (CCSprite*)this->getChildByTag( 0 );
			pDes0->setDisplayFrame( getEffectString(), nFrame );
			CCSprite* pDes1 = (CCSprite*)this->getChildByTag( 1 );
			pDes1->setDisplayFrame( getEffectString(), nFrame );
			CCSprite* pDes2 = (CCSprite*)this->getChildByTag( 2 );
			pDes2->setDisplayFrame( getEffectString(), nFrame );
			CCSprite* pDes3 = (CCSprite*)this->getChildByTag( 3 );
			pDes3->setDisplayFrame( getEffectString(), nFrame );
			CCSprite* pDes4 = (CCSprite*)this->getChildByTag( 4 );
			pDes4->setDisplayFrame( getEffectString(), nFrame );
			CCSprite* pDes5 = (CCSprite*)this->getChildByTag( 5 );
			pDes5->setDisplayFrame( getEffectString(), nFrame );
			CCSprite* pDes6 = (CCSprite*)this->getChildByTag( 6 );
			pDes6->setDisplayFrame( getEffectString(), nFrame );
			CCSprite* pDes7 = (CCSprite*)this->getChildByTag( 7 );
			pDes7->setDisplayFrame( getEffectString(), nFrame );

			fDelay = 0.f;
			nFrame++;

			if( nFrame >= nMaxFrame )
			{
				fDelay = 0.f;
				nFrame = 0;
				this->setIsVisible( false );
			}
		}
		return;
	}

	else if( iType == S1BOSSENGINE_EFFECT )
	{
		fDelay += dt;

		if( fDelay >= 0.05f )
		{
			fDelay = 0.f;
			nFrame++;

			if( nFrame >= nMaxFrame ) nFrame = 0;
		}

		CCSprite* pLeftEngine  = (CCSprite*)this->getChildByTag( 0 );
		pLeftEngine	->setDisplayFrame( "LEFT_ENGINE", nFrame );
		CCSprite* pRightEngine = (CCSprite*)this->getChildByTag( 1 );
		pRightEngine->setDisplayFrame( "RIGHT_ENGINE", nFrame );

		return;
	}
	else if( iType == S1BOSSATTACK_EFFECT )
	{
		fDelay += dt;

		if( fDelay >= 0.05f )
		{
			fDelay = 0.f;
			nFrame++;

			if( nFrame >= nMaxFrame ) nFrame = 0;
		}

		CCSprite* pLeftAttack  = (CCSprite*)this->getChildByTag( 0 );
		pLeftAttack	->setDisplayFrame( "LEFT_ATTACK", nFrame );
		CCSprite* pRightAttack = (CCSprite*)this->getChildByTag( 1 );
		pRightAttack->setDisplayFrame( "RIGHT_ATTACK", nFrame );


		return;
	}
	else if( iType == S1BOSSATTACKEND_EFFECT )
	{
		fDelay += dt;

		if( fDelay > 0.05f )
		{
			fDelay = 0.f;
			nFrame++;

			if( nFrame >= nMaxFrame ) 
			{
				this->setIsVisible( false );
				return;
			}
		}

		if( nFrame < nMaxFrame )
		{
			CCSprite* pLeftEnd  = (CCSprite*)this->getChildByTag( 0 );
			pLeftEnd ->setDisplayFrame( "LEFT_END" , nFrame );
			CCSprite* pRightEnd = (CCSprite*)this->getChildByTag( 1 );
			pRightEnd->setDisplayFrame( "RIGHT_END", nFrame );
		}
		return;
	}
	else if( iType == S1BOSSATTACKREADY_EFFECT )
	{
		fDelay += dt;

		if( fDelay > 0.15f )
		{
			fDelay = 0.f;
			nFrame++;

			if( nFrame >= nMaxFrame ) 
			{
				this->setIsVisible( false );
				return;
			}
		}

		if( nFrame < nMaxFrame )
		{
			CCSprite* pLeftReady  = (CCSprite*)this->getChildByTag( 0 );
			pLeftReady ->setDisplayFrame( "LEFT_READY" , nFrame );
			CCSprite* pRightReady = (CCSprite*)this->getChildByTag( 1 );
			pRightReady->setDisplayFrame( "RIGHT_READY", nFrame );
		}

		return;
	}

	else
	{
		fDelay += dt;

		if( fDelay > 0.07f )
		{
			CCSprite* pAni = (CCSprite*)this->getChildByTag( 0 );
			pAni->setDisplayFrame( getEffectString(), nFrame );

			fDelay = 0.f;
			nFrame++;

			if( nFrame >= nMaxFrame ) 
			{
				fDelay = 0.f;
				nFrame = 0;

				Object_Box* pBox = (Object_Box*)this->getChildByTag( 1 );
				if( pBox != NULL && pBox->getUseFlag() != false )
					pBox->setUseFlag( false );

				this->setIsVisible( false );
			}
		}
	}
}
