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
	dir					= RIGHT;
	fDelay				= 0.f;
	fZ					= 0.f;
	fVelocity			= VELOCITY;
	bInvincible			= true;
	bInvincibleSetLeg	= true;
	bMoveHold			= false;
	bFired				= false;
	bReFired			= false;
	bUpStay				= false;
	bMakeBullet			= false;


	this->addChild( pLeg  = LEG ::create() );
	this->addChild( pBody = BODY::create() );
	
	st::call()->boxM.addBox( ccp(-10.f, 15.f), ccp(10.f, 50.f), 1, this, BOX_HERO, 0 );

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
			pLeg->setValue		( INVINCIBLE, 0.03f );
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
		if( iUPstate != SHOT && iUPstate != GOUP_SHOT && iUPstate != UP_SHOT && iUPstate != GODW_SHOT && iUPstate != GRENADE )
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
			if( iUPstate != SHOT && iUPstate != GOUP_SHOT && iUPstate != UP_SHOT && iUPstate != GODW_SHOT && iUPstate != GRENADE )
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
			if( iUPstate != SHOT && iUPstate != GOUP_SHOT && iUPstate != UP_SHOT && iUPstate != GODW_SHOT && iUPstate != GRENADE )
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

	// Sit Shot and Sit Grenade motion stop control
	if( pLeg->getUseFlag() == true && pLeg->getNowState() == HGS_DOWN )
	{
		if( iDWstate == IDLE_SIT || iDWstate == WALK_SIT )
			iDWstate  = SIT_SHOT;
	}
	else if( pLeg->getUseFlag() == true && pLeg->getNowState() == DW_GRENADE )
	{
		if( iDWstate == IDLE_SIT || iDWstate == WALK_SIT )
			iDWstate  = SIT_GRENADE;
	}



	// JUMP
	if( iDWstate != IDLE_JUMP && iDWstate != WALK_JUMP && iDWstate != DROP )
	{	
		if( GetAsyncKeyState('S') )
		{
			if( iDWstate == IDLE )
			{
				if( iUPstate != SHOT && iUPstate != GOUP_SHOT && iUPstate != UP_SHOT && iUPstate != GODW_SHOT && iUPstate != GRENADE )
					iUPstate = IDLE_JUMP;

				iDWstate = IDLE_JUMP;
			}
			else if( iDWstate == WALK )
			{
				if( iUPstate != SHOT && iUPstate != GOUP_SHOT && iUPstate != UP_SHOT && iUPstate != GODW_SHOT && iUPstate != GRENADE )
					iUPstate = WALK_JUMP;

				iDWstate = WALK_JUMP;
			}
		}
	}
	


	// UP
	if( iUPstate != HGU_READY && iUPstate != SHOT && iUPstate != UP_SHOT && iUPstate != GOUP_SHOT && iUPstate != GODW_SHOT && iUPstate != GRENADE )
	{
		if( GetAsyncKeyState(VK_UP) )
		{
			if( bUpStay )
				iUPstate = UP_READY;
			else
				iUPstate = UP_LOOK;
		}
	}


	// ATTACK
	if( GetAsyncKeyState('A') )
	{

		if( iUPstate != GOUP_SHOT && iUPstate != GODW_SHOT )
			bReFired = true;

		if( iUPstate == IDLE || iUPstate == WALK || iUPstate == IDLE_JUMP || iUPstate == WALK_JUMP )
		{
			iUPstate = SHOT;
		}

		else if( iUPstate == IDLE_SIT || iUPstate == WALK_SIT )
		{
			iUPstate = NULL_STATE;
			iDWstate = SIT_SHOT;
		}

		else if( iUPstate == UP_READY )
		{
			iUPstate = UP_SHOT;
		}

		else if( iUPstate == UP_LOOK )
		{
			iUPstate = GOUP_SHOT;
		}
	}

	if( iUPstate == SHOT )
	{
		if( GetAsyncKeyState(VK_UP) )
		{
			iUPstate = GOUP_SHOT;
		}
	}


	// GOUP Shot and GODW Shot
	if( bUpStay == true )
	{
		if( pBody->getNowState() == HGU_SHOT && !GetAsyncKeyState(VK_UP) )
		{
			pBody->setUseFlag( false );
			iUPstate = GODW_SHOT;
		}

		if( iUPstate != UP_READY && iUPstate != UP_LOOK  &&
			iUPstate != IDLE_SIT && iUPstate != WALK_SIT &&
			iUPstate != GOUP_SHOT&& iUPstate != UP_SHOT  && 
			iUPstate != GODW_SHOT&& iUPstate != GRENADE )
		{
			iUPstate = DOWN_LOOK;

			if( GetAsyncKeyState('A') )
			{
				iUPstate = GODW_SHOT;
			}
		}
		else if( iUPstate == IDLE_SIT || iUPstate == WALK_SIT )
			bUpStay = false;
	}


	if( GetAsyncKeyState('D') )
	{
		if( iUPstate != GRENADE )
			iUPstate = GRENADE;

		if( iDWstate != SIT_GRENADE )
		{
			if( iDWstate == WALK_SIT || iDWstate == IDLE_SIT || iDWstate == SIT_SHOT )
				iDWstate  = SIT_GRENADE;
		}
	}
	

	// Direction
	if( this->getScaleX() == 1.f )
		dir = RIGHT;
	else if( this->getScaleX() == -1.f )
		dir = LEFT;
		





	if( st::call()->makeWorldX( pos, st::call()->worldNode->getScale() ) < 50.f ||
		st::call()->makeWorldX( pos, st::call()->worldNode->getScale() ) > st::call()->winSize.width - 50.f )
		bMoveHold = true;
	else bMoveHold = false;

	if( st::call()->boxM.collisionObject((Object_Box*)this->getChildByTag(0), BOX_HERO) == true )
		bMoveHold = true;

	if( iDWstate == SIT_SHOT || iDWstate == SIT_GRENADE )
		bMoveHold = true;

	if( bMoveHold != true )
		this->setPosition( pos );
}

void Object_Hero::animation( float dt )
{
	if( iDWstate == SIT_SHOT || iDWstate == SIT_GRENADE )
		iUPstate = NULL_STATE;

	if( iUPstate != iUPprev )
	{
		fDelay		= 0.f;
		bMakeBullet	= false;

		pBody->setUseFlag( false );
		iUPprev = iUPstate;
	}
	if( iDWstate != iDWprev )
	{
		pLeg->setUseFlag( false );
		iDWprev = iDWstate;
	}

	if( iDWstate == SIT_SHOT && pLeg->getFrame() >= 4 )
	{
		if( bFired == false )
		{
			bFired   = true;
			bReFired = false;
		}

		if( bReFired == true )
		{
			bFired	 = false;
			pLeg->setUseFlag( false );
		}
	}


	else if( iUPstate != NULL_STATE )
	{
		if( iUPstate != GOUP_SHOT && iUPstate != GODW_SHOT && pBody->getFrame() >= 4 )
		{
			if( bFired == false )
			{
				bFired   = true;
				bReFired = false;
			}

			if( bReFired == true )
			{
				bFired	 = false;
				pBody->setUseFlag( false );
			}
		}
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
	case SHOT:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HG_SHOT );

			if( pBody->getFrame() == 0 && bMakeBullet == false )
			{
				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 10.f : -10.f;
				pos.y += 30.f + rand()%6 - rand()%6;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, SHOT, st::call()->worldNode, 10 );
				st::call()->SM.play(SND_HGBULLET);
				bMakeBullet = true;
			}

			if( pBody->getFrame() == 1 )
				bMakeBullet = false;

			if( pBody->getFrame() == 2 && bMakeBullet == false )
			{
				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 10.f : -10.f;
				pos.y += 30.f + rand()%6 - rand()%6;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, SHOT, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
				bMakeBullet = true;
			}

			if( pBody->getFrame() == 3 )
				bMakeBullet = false;

			if( pBody->getFrame() >= 8 )
				iUPstate = IDLE;

			break;
		}
	case NULL_STATE:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HGD_NULL );

			break;
		}
	case GOUP_SHOT:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( SHOT_GOUP );

			fDelay += dt;

			if( fDelay > 0.f && fDelay < 0.05f && bMakeBullet == false )
			{
				bMakeBullet = true;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 20.f : -24.f;
				pos.y += 30.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 90, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}
			else if( fDelay > 0.05f && fDelay < 0.1f && bMakeBullet == true )
			{
				bMakeBullet = false;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 18.f : -22.f;
				pos.y += 42.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 75, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}
			else if( fDelay > 0.1f && fDelay < 0.15f && bMakeBullet == false )
			{
				bMakeBullet = true;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 16.f : -20.f;
				pos.y += 48.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 60, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}
			else if( fDelay > 0.15f && fDelay < 0.2f && bMakeBullet == true )
			{
				bMakeBullet = false;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 14.f : -18.f;
				pos.y += 56.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 45, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}
			else if( fDelay > 0.2f && fDelay < 0.25f && bMakeBullet == false )
			{
				bMakeBullet = true;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 12.f : -16.f;
				pos.y += 64.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 30, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}
			else if( fDelay > 0.25f && fDelay < 0.3f && bMakeBullet == true )
			{
				bMakeBullet = false;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 10.f : -14.f;
				pos.y += 72.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 15, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}
			else if( fDelay > 0.3f && fDelay > 0.35f && bMakeBullet == false )
			{
				bMakeBullet = true;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 8.f : -12.f;
				pos.y += 80.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 0, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}

			if( pBody->getFrame() >= 5 )
			{
				iUPstate	= IDLE;
				bUpStay		= true;
				bMakeBullet = false;
				fDelay		= 0.f;
			}

			break;
		}
	case UP_SHOT:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HGU_SHOT );

			if( pBody->getFrame() == 0 && bMakeBullet == false )
			{
				CGPoint pos = this->getPosition();
				pos.x += 8.f;
				pos.y += 80.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, UP_SHOT, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
				bMakeBullet = true;
			}

			if( pBody->getFrame() == 1 )
			{
				bMakeBullet = false;
			}

			if( pBody->getFrame() == 2 && bMakeBullet == false )
			{
				CGPoint pos = this->getPosition();
				pos.x += 8.f;
				pos.y += 80.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, UP_SHOT, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
				bMakeBullet = true;
			}

			if( pBody->getFrame() == 3 )
			{
				bMakeBullet = false;
			}

			if( pBody->getFrame() >= 6 )
				iUPstate = IDLE;

			break;
		}
	case GODW_SHOT:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( SHOT_GODW );

			fDelay += dt;

			if( fDelay > 0.f && fDelay < 0.05f && bMakeBullet == false )
			{
				bMakeBullet = true;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 8.f : -12.f;
				pos.y += 80.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 0, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}
			else if( fDelay > 0.05f && fDelay < 0.1f && bMakeBullet == true )
			{
				bMakeBullet = false;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 10.f : -14.f;
				pos.y += 72.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 10, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}
			else if( fDelay > 0.1f && fDelay < 0.15f && bMakeBullet == false )
			{
				bMakeBullet = true;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 12.f : -16.f;
				pos.y += 64.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 25, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}
			else if( fDelay > 0.15f && fDelay < 0.2f && bMakeBullet == true )
			{
				bMakeBullet = false;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 14.f : -18.f;
				pos.y += 56.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 40, st::call()->worldNode );
			}
			else if( fDelay > 0.2f && fDelay < 0.25f && bMakeBullet == false )
			{
				bMakeBullet = true;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 16.f : -20.f;
				pos.y += 48.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 55, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}
			else if( fDelay > 0.25f && fDelay < 0.3f && bMakeBullet == true )
			{
				bMakeBullet = false;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 18.f : -22.f;
				pos.y += 42.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 70, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}
			else if( fDelay > 0.3f && fDelay < 0.35f && bMakeBullet == false )
			{
				bMakeBullet = true;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 20.f : -24.f;
				pos.y += 34.f;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, GOUP_SHOT, 85, st::call()->worldNode );
				st::call()->SM.play(SND_HGBULLET);
			}



			if( pBody->getFrame() >= 4 )
			{
				iUPstate	= IDLE;
				bUpStay		= false;
				bMakeBullet = false;
				fDelay		= 0.f;
			}

			break;
		}
	case GRENADE:
		{
			if( pBody->getUseFlag() == false )
				pBody->setValue( HG_GRENADE );

			if( bMakeBullet == false )
			{
				bMakeBullet = true;

				CGPoint pos = this->getPosition();
				pos.x += dir == RIGHT ? 5.f : -5.f;
				pos.y += 30.f;

				st::call()->BM.addBullet( pos, dir, W_GRENADE, st::call()->worldNode );
			}

			if( pBody->getFrame() >= 4 )
			{
				bMakeBullet = false;
				iUPstate	= IDLE;
				pBody->setUseFlag( false );
			}

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
	case SIT_SHOT:
		{
			if( pLeg->getUseFlag() == false )
				pLeg->setValue( HGS_DOWN );

			if( pLeg->getFrame() == 0 && bMakeBullet == false )
			{
				CGPoint pos = this->getPosition();
				if( dir == RIGHT )
					pos.x += 10.f;
				else if( dir == LEFT )
					pos.x -= 10.f;
				pos.y += 25.f + rand()%6 - rand()%6;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, SIT_SHOT, st::call()->worldNode );
				bMakeBullet = true;
			}

			if( pLeg->getFrame() == 1 )
				bMakeBullet = false;

			if( pLeg->getFrame() == 2 && bMakeBullet == false )
			{
				CGPoint pos = this->getPosition();
				if( dir == RIGHT )
					pos.x += 10.f;
				else if( dir == LEFT )
					pos.x -= 10.f;
				pos.y += 25.f + rand()%6 - rand()%6;

				st::call()->BM.addBullet( pos, dir, MACHINEGUN, SIT_SHOT, st::call()->worldNode );
				bMakeBullet = true;
			}

			if( pLeg->getFrame() == 3 )
				bMakeBullet = false;

			if( pLeg->getFrame() >= 7 )
			{
				bMakeBullet = false;
				iDWstate	= IDLE;
				pLeg->setUseFlag( false );
			}

			break;
		}
	case SIT_GRENADE:
		{
			if( pLeg->getUseFlag() == false )
				pLeg->setValue( DW_GRENADE );


			if( bMakeBullet == false )
			{
				bMakeBullet = true;

				CGPoint pos = this->getPosition();
				pos.y += 30.f;

				st::call()->BM.addBullet( pos, dir, W_GRENADE, st::call()->worldNode );
			}


			if( pLeg->getFrame() >= 3 )
			{
				bMakeBullet = false;
				iDWstate	= IDLE;
				pLeg->setUseFlag( false );
			}

			break;
		}
	}
}
