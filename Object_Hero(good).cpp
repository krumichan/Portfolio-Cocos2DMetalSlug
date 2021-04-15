#include "Object_Hero.h"
#include "st.h"

Object_Hero* Object_Hero::create()
{
	Object_Hero* p = new Object_Hero;
	p->init();
	return p;
}
bool Object_Hero::init()
{
	if( !CCSprite::init() ) return false;

	fMoveSec			= 100.f;
	iUPstate			= IDLE;
	iUPprev				= IDLE;
	iDWstate			= IDLE;
	iDWprev				= IDLE;
	fDelay				= 0.f;
	fZ					= 0.f;
	fVelocity			= VELOCITY;
	bInvincible			= true;
	bInvincibleSetLeg	= true;
	bMoveHold			= false;
	bFired				= false;
	bReFired			= false;
	bSitFired			= false;
	bReSitFired			= false;
	bUpStay				= false;


	this->addChild( pLeg  = LEG ::create() );
	this->addChild( pBody = BODY::create() );

	schedule( schedule_selector(Object_Hero::update) );
	return true;
}

void Object_Hero::update( float dt )
{

	// Invincible
	if( bInvincible == true )
	{
		if( bInvincibleSetLeg == true )
		{
			bMoveHold = true;
			pLeg->setAnchorPoint( ccp(0.4f, 0.31f) );
			pLeg->setValue( INVINCIBLE, 0.03f );
			bInvincibleSetLeg = false;
		}

		if( pLeg->getUseFlag() == false )
		{
			bMoveHold	= false;
			bInvincible = false;
			pLeg->setAnchorPoint( ccp(0.4f, 0.f) );
		}
		else return;
	}

	this->action	( dt );
	this->animation	( dt );
}

void Object_Hero::action( float dt )
{
	CGPoint pos = this->getPosition();


	// IDLE
	if( iDWstate != IDLE_JUMP && iDWstate != WALK_JUMP && iDWstate != DROP )
	{
		iUPstate = IDLE;
		iDWstate = IDLE;
	}

	// LEFT
	if( GetAsyncKeyState(VK_LEFT) )
	{
		pos.x -= fMoveSec * dt;
		this->setScaleX( -1.f );

		if( iDWstate != IDLE_JUMP && iDWstate != WALK_JUMP && iDWstate != DROP )
		{	
			iUPstate = WALK;
			iDWstate = WALK;
		}
		
	}





	// RIGHT
	if( GetAsyncKeyState(VK_RIGHT) )
	{
		pos.x += fMoveSec * dt;
		this->setScaleX( 1.f );

		if( iDWstate != IDLE_JUMP && iDWstate != WALK_JUMP && iDWstate != DROP )
		{	
			iUPstate = WALK;
			iDWstate = WALK;
		}
	}



	// DOWN
	if( iDWstate != IDLE_JUMP && iDWstate != WALK_JUMP && iDWstate != DROP )
	{	
		if( GetAsyncKeyState(VK_DOWN) )
		{
			iUPstate = IDLE_SIT;
			iDWstate = IDLE_SIT;

			if( GetAsyncKeyState(VK_RIGHT) )
			{
				iUPstate = WALK_SIT;
				iDWstate = WALK_SIT;
			}

			if( GetAsyncKeyState(VK_LEFT) )
			{
				iUPstate = WALK_SIT;
				iDWstate = WALK_SIT;
			}
		}
	}


	// JUMP
	if( iDWstate != IDLE_JUMP && iDWstate != WALK_JUMP && iDWstate != DROP )
	{	
		if( GetAsyncKeyState('S') )
		{
			if( iDWstate == IDLE )
			{
				iUPstate = IDLE_JUMP;
				iDWstate = IDLE_JUMP;
			}
			else if( iDWstate == WALK )
			{
				iUPstate = WALK_JUMP;
				iDWstate = WALK_JUMP;
			}
		}
	}
	


	// UP
	if( iUPstate != HGU_READY )
	{
		if( GetAsyncKeyState(VK_UP) )
		{
			if( bUpStay )
				iUPstate = UP_READY;
			else
				iUPstate = UP_LOOK;
		}
	}


	if( GetAsyncKeyState('A') )
		st::call()->BM.addBullet( ccp(pos.x+10.f, pos.y+27.f), RIGHT, MACHINEGUN, st::call()->worldNode );
	


















	if( st::call()->makeWorldX( pos, st::call()->worldNode->getScale() ) < 50.f ||
		st::call()->makeWorldX( pos, st::call()->worldNode->getScale() ) > 974.f )
		bMoveHold = true;
	else bMoveHold = false;

	if( st::call()->boxM.CollisionCheck(ccp(pos.x, pos.y+20.f), TEXTURE) != NULL )
		bMoveHold = true;

	if( bMoveHold != true )
		this->setPosition( pos );
}

void Object_Hero::animation( float dt )
{
	if( iUPstate != iUPprev )
	{
		pBody->setUseFlag( false );
		iUPprev = iUPstate;
	}
	if( iDWstate != iDWprev )
	{
		pLeg->setUseFlag( false );
		iDWprev = iDWstate;
	}

	if( bUpStay == true )
	{
		if( iUPstate != UP_READY && iUPstate != UP_LOOK && iUPstate != IDLE_SIT && iUPstate != WALK_SIT )
			iUPstate = DOWN_LOOK;
		else if( iUPstate == IDLE_SIT || iUPstate == WALK_SIT )
			bUpStay = false;
	}

	switch( iUPstate )
	{
	case IDLE:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HG_STAND );

			break;
		}
	case WALK:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HG_RUN );

			break;
		}
	case IDLE_SIT:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HGD_NULL );

			break;	
		}
	case WALK_SIT:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HGD_NULL );

			break;
		}
	case UP_LOOK:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HG_LOOKUP );

			if( pBody->getFrame() >= 2 )
				bUpStay = true;

			break;
		}
	case UP_READY:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HGU_READY );

			break;
		}
	case DOWN_LOOK:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HG_LOOKDOWN );

			if( pBody->getFrame() >= 2 )
				bUpStay = false;

			break;
		}
	case IDLE_JUMP:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HGS_JUMP );

			break;
		}
	case WALK_JUMP:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HGR_JUMP );

			break;
		}
	}

	switch( iDWstate )
	{
	case IDLE:
		{
			if( pLeg->getUseFlag() == false )
				pLeg->setValue( S_LEG );

			break;
		}
	case WALK:
		{
			if( pLeg->getUseFlag() == false )
				pLeg->setValue( R_LEG );

			break;
		}
	case IDLE_SIT:
		{
			if( pLeg->getUseFlag() == false )
				pLeg->setValue( HG_DOWN );

			break;
		}
	case WALK_SIT:
		{
			if( pLeg->getUseFlag() == false )
				pLeg->setValue( HGW_DOWN );

			break;
		}
	case IDLE_JUMP:
		{
			fVelocity -= GRAVITY   * 2*dt;
			fZ		  += fVelocity * dt;

			CGPoint pos = this->getPosition();
			pos.y += fVelocity * dt;
			this->setPosition( pos );
			
			if( fVelocity < 0.f )
				iDWstate = DROP;

			if( pLeg->getUseFlag() == false )
				pLeg->setValue( SJ_LEG );

			break;
		}
	case WALK_JUMP:
		{
			fVelocity	-= GRAVITY	 * 2*dt;
			fZ			+= fVelocity * dt;

			CGPoint pos  = this->getPosition();
			pos.y += fVelocity * dt;
			this->setPosition( pos );

			if( fVelocity < 0.f )
				iDWstate = DROP;

			if( pLeg->getUseFlag() == false )
				pLeg->setValue( JR_LEG );

			break;
		}
	case DROP:
		{
			fVelocity	+= GRAVITY	 * 2*dt;
			fZ			-= fVelocity * dt;

			CGPoint pos  = this->getPosition();
			pos.y -= fVelocity * dt;
			this->setPosition( pos );

			if( fZ <= 0.f )
			{
				pos.y	 -= fZ;
				fZ		  = 0.f;
				fVelocity = VELOCITY;
				iDWstate  = IDLE;
				this->setPosition( pos );
			}
			break;
		}
	}
}

/*
BODY
HGR_JUMP, HGS_JUMP, HG_RUN, HGS_STAND, HGD_NULL, INV_NULL, HG_STAND, HG_SHOT,

LEG
HG_DOWN, HGS_DOWN, HGW_DOWN, INVINCIBLE, SJ_LEG, R_LEG, S_LEG, JR_LEG
*/