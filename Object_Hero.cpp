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
	state				= IDLE;
	prevState			= IDLE;
	shot				= NONSHOT;
	prevShot			= NONSHOT;
	fDealy				= 0.f;
	fZ					= 0.f;
	fVelocity			= VELOCITY;
	bInvincible			= true;
	bInvincibleSetLeg	= true;
	bMoveHold			= false;
	bFired				= false;
	bReFired			= false;
	bSitFired			= false;
	bReSitFired			= false;


	this->addChild( pLeg  = LEG ::create() );
	this->addChild( pBody = BODY::create() );

	schedule( schedule_selector(Object_Hero::update) );
	return true;
}

void Object_Hero::update( float dt )
{
	this->action	( dt );
	this->animation	( dt );
}

void Object_Hero::action( float dt )
{
	CGPoint pos = this->getPosition();

	if( state != IDLE_JUMP && state != WALK_JUMP && state != DROP )
	{
		state = IDLE;

		if( GetAsyncKeyState(VK_DOWN) )
		{
			state = IDLE_SIT;
		}
	}

	if( GetAsyncKeyState(VK_LEFT) )
	{
		pos.x -= fMoveSec * dt;
	
		if( state != IDLE_JUMP && state != WALK_JUMP && state != DROP )
		{
			this->setScaleX( -1.f );
			state = WALK;

			if( GetAsyncKeyState(VK_DOWN) )
			{
				state = WALK_SIT;
			}
			if( GetAsyncKeyState('S') )
			{
				state = WALK_JUMP;
			}
		}	
	}
	if( GetAsyncKeyState(VK_RIGHT) )
	{
		pos.x += fMoveSec * dt;

		if( state != IDLE_JUMP && state != WALK_JUMP && state != DROP )
		{
			this->setScaleX( 1.f );
			state = WALK;

			if( GetAsyncKeyState(VK_DOWN) )
			{
				state = WALK_SIT;
			}
			if( GetAsyncKeyState('S') )
			{
				state = WALK_JUMP;
			}
		}
	}
	if( GetAsyncKeyState('A') )
	{
		shot		= SHOT;
		if( state == IDLE_SIT || state == WALK_SIT )
			bReSitFired = true;
		else
			bReFired	= true;
	}

	if( state != IDLE_JUMP && state != WALK_JUMP && state != DROP )
	{
		if( GetAsyncKeyState('S') )
		{
			state = IDLE_JUMP;
		}
	}
	if( state != IDLE_SIT || state != WALK_SIT )
	{
		if( GetAsyncKeyState(VK_UP) )
			state = HG_SHOTUP;
	}

	if( st::call()->makeWorldX( pos, st::call()->worldNode->getScale() ) < 50.f ||
		st::call()->makeWorldX( pos, st::call()->worldNode->getScale() ) > 974.f )
		bMoveHold = true;
	else
		bMoveHold = false;

	if( (state == IDLE_SIT || state == WALK_SIT) && shot == SHOT )
		bMoveHold = true;

	if( bInvincibleSetLeg != true && bMoveHold != true )
		this->setPosition( pos );
}
void Object_Hero::animation( float dt )
{
	// Hero Invincible
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
		}

		return;
	}

	pLeg->setAnchorPoint( ccp(0.4f, 0.0f) );

	//Hero Operating
	/*
	IDLE, JUMP, DROP, WALK, SIT, IDLE_JUMP, WALK_JUMP, IDLE_SIT, WALK_SIT,
	SHOT, NONSHOT
	*/
	
	// (state : sit -> stand OR state : stand -> sit) - State Initialize
	if( ((prevState == IDLE_SIT || prevState == WALK_SIT) && (state != IDLE_SIT && state != WALK_SIT)) ||
		((prevState != IDLE_SIT && prevState != WALK_SIT) && (state == IDLE_SIT || state == WALK_SIT)) )
	{
		pBody->setUseFlag( false );
		pLeg ->setUseFlag( false );
		shot	  = NONSHOT;
	}

	if( state != prevState )
	{
		// state - Stand
		if( ((prevState != IDLE_SIT && prevState != WALK_SIT) && (state != IDLE_SIT && state != WALK_SIT)) )
		{
			if( prevShot == NONSHOT && shot == SHOT )
			{
				pBody->setUseFlag( false );
				prevShot = shot;
			}
			else if( prevShot == SHOT && shot == SHOT )
			{
				if( pBody->getUseFlag() == false )
				{
					shot	 = NONSHOT;
					prevShot = NONSHOT;
				}
				pLeg ->setUseFlag( false );
			}
			else
			{
				pBody->setUseFlag( false );
				pLeg ->setUseFlag( false );
				prevShot = NONSHOT;
				shot	 = NONSHOT;
			}
		}
		// state - sit
		else if( ((prevState == IDLE_SIT || prevState == WALK_SIT) && (state == IDLE_SIT || state == WALK_SIT)) )
		{
			if( prevShot == NONSHOT && shot == SHOT )
			{
				pLeg ->setUseFlag( false );
				prevShot = shot;
			}
			else if( prevShot == SHOT && shot == SHOT )
			{
				if( pLeg->getUseFlag() == false )
				{
					shot	 = NONSHOT;
					prevShot = NONSHOT;
				}
			}
			else
			{
				pLeg ->setUseFlag( false );
				prevShot = NONSHOT;
				shot	 = NONSHOT;
			}
		}
	}

	else if( prevState == state )
	{
		if( ((prevState != IDLE_SIT && prevState != WALK_SIT) && (state != IDLE_SIT && state != WALK_SIT)) )
		{
			if( prevShot == NONSHOT && shot == SHOT )
			{
				pBody->setUseFlag( false );
				prevShot = shot;
			}
			else if( prevShot == SHOT && shot == SHOT )
			{
				if( pBody->getUseFlag() == false )
				{
					shot	 = NONSHOT;
					prevShot = NONSHOT;
				}
			}
		}	
		else if( ((prevState == IDLE_SIT || prevState == WALK_SIT) && (state == IDLE_SIT || state == WALK_SIT)) )
		{
			if( prevShot == NONSHOT && shot == SHOT )
			{
				pLeg->setUseFlag( false );
				bMoveHold = true;
				prevShot  = shot;
			}
			else if( prevShot == SHOT && shot == SHOT )
			{
				if( pLeg->getUseFlag() == false )
				{
					shot	  = NONSHOT;
					prevShot  = NONSHOT;
					bMoveHold = false;
				}
			}
		}
	}

	if( shot == SHOT )
	{
		if( pLeg->getFrame() > 3 && (state == IDLE_SIT || state == WALK_SIT) )
		{
			if( bSitFired == false )
			{
				bSitFired	= true;
				bReSitFired = false;
			}

			if( bReSitFired == true )
			{
				bSitFired = false;
				pLeg->setUseFlag( false );
			}
		}
		else
		{
			if( pBody->getFrame() > 3 )
			{
				if( bFired == false )
				{
					bFired	 = true;
					bReFired = false;
				}

				if( bReFired == true )
				{
					bFired = false;
					pBody->setUseFlag( false );
				}
			}
		}
	}



	switch( state )
	{
	case IDLE:
		{
			if( pBody->getUseFlag() == false )
			{
				if( shot == SHOT )
					pBody->setValue( HG_SHOT, 0.05f );
				else
					pBody->setValue( HG_STAND );
			}
			if( pLeg->getUseFlag() == false )
				pLeg->setValue( S_LEG );

			break;
		}
	case WALK:
		{
			if( pBody->getUseFlag() == false )
			{
				if( shot == SHOT )
					pBody->setValue( HG_SHOT, 0.05f );
				else
					pBody->setValue( HG_RUN );
			}
			if( pLeg->getUseFlag() == false )
				pLeg->setValue( R_LEG );

			break;
		}
	case IDLE_JUMP:
		{
			fVelocity -= GRAVITY * 6*dt;
			fZ += fVelocity * dt;

			CGPoint pos = this->getPosition();
			pos.y += fVelocity * dt;
			this->setPosition( pos );

			if( fVelocity < 0.f )
				state = DROP;

			if( shot == SHOT )
			{
				if( pBody->getUseFlag() == false )
					pBody->setValue( HG_SHOT, 0.05f );
			}
			if( pBody->getUseFlag() == false )
				pBody->setValue( HGS_JUMP, 0.07f );
			if( pLeg->getUseFlag() == false )
				pLeg->setValue( SJ_LEG, 0.07f );

			break;
		}
	case WALK_JUMP:
		{
			fVelocity -= GRAVITY * 6*dt;
			fZ += fVelocity * dt;

			CGPoint pos = this->getPosition();
			pos.y += fVelocity * dt;
			this->setPosition( pos );

			if( fVelocity < 0.f )
				state = DROP;

			if( shot == SHOT )
			{
				if( pBody->getUseFlag() == false )
					pBody->setValue( HG_SHOT, 0.05f );
			}
			if( pBody->getUseFlag() == false )
				pBody->setValue( HGR_JUMP );
			if( pLeg->getUseFlag() == false )
				pLeg->setValue( JR_LEG );
			break;
		}
	case DROP:
		{
			fVelocity += GRAVITY * 6*dt;
			fZ -= fVelocity * dt;

			CGPoint pos = this->getPosition();
			pos.y -= fVelocity * dt;
			this->setPosition( pos );

			if( pBody->getUseFlag() == false )
			{
				if( shot == SHOT )
					pBody->setValue( HG_SHOT, 0.05f );
			}

			if( fZ < 0.f )
			{
				// if fZ < 0 : if fZ = -2.f  -> pos.y + 2.f
				pos.y -= fZ;
				this->setPosition( pos );

				state	  = IDLE;
				fVelocity = VELOCITY;
				fZ		  = 0.f;
			}
			break;
		}
	case IDLE_SIT:
		{ 
			if( pBody->getUseFlag() == false )
				pBody->setValue( HGD_NULL );
			if( pLeg->getUseFlag() == false )
			{
				if( shot == SHOT )
					pLeg->setValue( HGS_DOWN, 0.05f );
				else
					pLeg->setValue( HG_DOWN );
			}
			break;
		}
	case WALK_SIT:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HGD_NULL );
			if( pLeg->getUseFlag() == false )
			{
				if( shot == SHOT )
					pLeg->setValue( HGS_DOWN, 0.05f );
				else
					pLeg->setValue( HGW_DOWN );
			}
			break;
		}
	}

	if( prevState != state )
	{
		prevState = state;
	}
}

/*
BODY
HGR_JUMP, HGS_JUMP, HG_RUN, HGS_STAND, HGD_NULL, INV_NULL, HG_STAND, HG_SHOT,

LEG
HG_DOWN, HGS_DOWN, HGW_DOWN, INVINCIBLE, SJ_LEG, R_LEG, S_LEG, JR_LEG
*/