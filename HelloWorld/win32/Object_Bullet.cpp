#include "Object_Bullet.h"
#include "st.h"
#include "Object_Hero.h"

bool Object_Bullet::init( WEAPON _weapon )
{
	if( !CCSprite::init() ) return false;

	dir			= RIGHT;
	weapon		= _weapon;
	fFrameDelay = 0.f;
	nFrame		= 0;
	bRotation	= false;

	switch( _weapon )
	{
	case SHOTGUN:
		{
			CCSprite* pHBullet = new CCSprite;
			pHBullet->init();
			pHBullet->setAnchorPoint( ccp(0.f, 0.f) );
			pHBullet->setPosition	( ccp(0.f, 0.f) );
			pHBullet->addAnimation	( st::call()->makeAnimation("resource/SHOTGUN_", "SHOTGUN", 12) );
			this	->addChild		( pHBullet, 0, 0 );
			break;
		}
	case MACHINEGUN:
		{
			CCSprite* pHBullet = CCSprite::spriteWithFile( "resource/HG_BULLET.png" );
			pHBullet->setAnchorPoint( ccp(0.f, 0.f)  );
			pHBullet->setPosition	( ccp(0.f, 0.f)  );
			this	->addChild		( pHBullet, 0, 0 );

			st::call()->boxM.addBox( ccp(5.f, 5.f), ccp(30.f, 10.f), this, BOX_HEROBULLET, 1 );
			break;
		}
	case NORMALGUN:
		{
			CCSprite* pHBullet = new CCSprite;
			pHBullet->init();
			pHBullet->setAnchorPoint( ccp(0.f, 0.f) );
			pHBullet->setPosition	( ccp(0.f, 0.f) );
			pHBullet->addAnimation	( st::call()->makeAnimation("resource/Normal_Bullet_", "NORMALGUN", 2) );
			this	->addChild		( pHBullet, 0, 0 );
			break;
		}
	case TURRET_BULLET:
		{
			fVelocity = TURRET_VELOCITY;
			fZ		  = 0.f;
			bState	  = false;


			CCSprite* pTurret = CCSprite::spriteWithFile( "resource/TURRET_BULLET.png" );
			pTurret->setAnchorPoint	( ccp(0.f, 0.f) );
			pTurret->setPosition	( ccp(0.f, 0.f) );
			this   ->addChild		( pTurret, 0, 0 );
			this   ->setRotation	( 44.f			);
			break;
		}
	case W_GRENADE:
		{
			fGreVelocity = GRENADE_VELOCITY;
			fGreZ		 = 0.f;
			bGreState	 = false;

			CCSprite* pGrenade = CCSprite::spriteWithFile( "resource/GRENADE.png" );
			pGrenade->setAnchorPoint( ccp(0.5f, 0.5f)  );
			pGrenade->setPosition	( ccp(0.f, 0.f)  );
			this->addChild			( pGrenade, 0, 0 );

			break;
		}
	}

	schedule( schedule_selector(Object_Bullet::update) );
	return true;
}
void Object_Bullet::update( float dt )
{
	this->action	( dt );
	this->animation	( dt );
}

void Object_Bullet::action( float dt )
{
	CGPoint pos = this->getPosition();

	switch( weapon )
	{
	case SHOTGUN:
		{
			dir == RIGHT ? this->setScaleX( 1.f ) : this->setScaleX( -1.f );
			break;
		}
	case MACHINEGUN:
		{
			Object_Box* pBox = (Object_Box*)this->getChildByTag( 1 );
			if( pBox == NULL ) break;

			if( gunMoveStyle == SHOT || gunMoveStyle == SIT_SHOT )
			{
				if( st::call()->makeWorldX( pos, 3.45f ) >= st::call()->winSize.width ||
					st::call()->makeWorldX( pos, 3.45f ) <= 0.f )
				{
					pBox->setUseFlag  ( false );
					this->setIsVisible( false );
					return;
				}

				dir == RIGHT ? this->setScaleX( 1.f ) : this->setScaleX( -1.f );

				pos.x += dir == RIGHT ? 200.f*dt : -200.f*dt;
			}
			else if( gunMoveStyle == UP_SHOT )
			{
				if( st::call()->makeWorldY(pos, 3.45f) >= st::call()->winSize.height ||
					st::call()->makeWorldY(pos, 3.45f) <= 0.f )
				{
					pBox->setUseFlag  ( false );
					this->setIsVisible( false );
					return;
				}

				if( bRotation == false )
				{
					bRotation = true;
					this->setRotation( -90.f );
				}

				pos.y += 200.f * dt;
			}
			else if( gunMoveStyle == GOUP_SHOT || gunMoveStyle == GODW_SHOT )
			{
				if( (st::call()->makeWorldX(pos, 3.45f) >= st::call()->winSize.width ||
					 st::call()->makeWorldX(pos, 3.45f) <= 0.f) ||
					(st::call()->makeWorldY(pos, 3.45f) >= st::call()->winSize.height ||
					 st::call()->makeWorldY(pos, 3.45f) <= 0.f) )
				{
					pBox->setUseFlag	( false );
					this->setIsVisible	( false );
					return;
				}

				if( bRotation == false )
				{
					bRotation = true;

					switch( iAngle ) 
					{
					case 10:
						{
							dir == RIGHT ? this->setRotation( -80.f ) : this->setRotation( 80.f );
							fsinAngle = 0.17364817766f; // sin(10)
							fconAngle = 0.98480775301f; // cos(10)
							break;
						}
					case 25:
						{
							dir == RIGHT ? this->setRotation( -65.f ) : this->setRotation( 65.f );
							fsinAngle = 0.42261826174f; // sin(25)
							fconAngle = 0.90630778703f; // cos(25)
							break;
						}
					case 40:
						{
							dir == RIGHT ? this->setRotation( -50.f ) : this->setRotation( 50.f );
							fsinAngle = 0.64278760968f; // sin(40)
							fconAngle = 0.76604444311f; // cos(40)
							break;
						}
					case 55:
						{
							dir == RIGHT ? this->setRotation( -35.f ) : this->setRotation( 35.f );
							fsinAngle = 0.81915204428f; // sin(55)
							fconAngle = 0.57357643635f; // cos(55)
							break;
						}
					case 70:
						{
							dir == RIGHT ? this->setRotation( -20.f ) : this->setRotation( 20.f );
							fsinAngle = 0.93969262078f; // sin(70)
							fconAngle = 0.34202014332f; // cos(70)
							break;
						}
					case 85:
						{
							dir == RIGHT ? this->setRotation( -5.f ) : this->setRotation( 5.f );
							fsinAngle = 0.99619469809f; // sin(85)
							fconAngle = 0.08715574274f; // cos(85)
							break;
						}
					case 0:
						{
							dir == RIGHT ? this->setRotation( -90.f ) : this->setRotation( 90.f );
							fsinAngle = 0.f;			// sin(0)
							fconAngle = 1.f;			// cos(0)
							break;
						}
					case 15:
						{
							dir == RIGHT ? this->setRotation( -75.f ) : this->setRotation( 75.f );
							fsinAngle = 0.2588190451f;  // sin(15)
							fconAngle = 0.96592582628f; // cos(15)
							break;
						}
					case 30:
						{
							dir == RIGHT ? this->setRotation( -60.f ) : this->setRotation( 60.f );
							fsinAngle = 0.5f;			// sin(30)
							fconAngle = 0.86602540378f; // cos(30)
							break;
						}
					case 45:
						{
							dir == RIGHT ? this->setRotation( -45.f ) : this->setRotation( 45.f );
							fsinAngle = 0.70710678118f; // sin(45)
							fconAngle = 0.70710678118f; // cos(45)
							break;
						}
					case 60:
						{
							dir == RIGHT ? this->setRotation( -30.f ) : this->setRotation( 30.f );
							fsinAngle = 0.86602540378f; // sin(60)
							fconAngle = 0.5f;			// cos(60)
							break;
						}
					case 75:
						{
							dir == RIGHT ? this->setRotation( -15.f ) : this->setRotation( 15.f );
							fsinAngle = 0.96592582628f; // sin(75)
							fconAngle = 0.2588190451f;  // cos(75)
							break;
						}
					case 90:
						{
							this->setRotation( 0.f );
							fsinAngle = 1.f;			// sin(90)
							fconAngle = 0.f;			// cos(90)
							break;
						}
					}
				}
				
				dir == RIGHT ? this->setScaleX( 1.f ) : this->setScaleX( -1.f );

				pos.x += dir == RIGHT ? ( fsinAngle * 200.f ) * dt : ( fsinAngle * -(200.f) ) * dt;
				pos.y += ( fconAngle * 200.f ) * dt;
			}

			break;
		}
	case NORMALGUN:
		{
			if( st::call()->makeWorldX( pos, 3.45f ) >= 1024.f ||
				st::call()->makeWorldX( pos, 3.45f ) <= 0.f )
			{
				this->setIsVisible(false);
				return;
			}

			dir == RIGHT ? this->setScaleX( 1.f ) : this->setScaleX( -1.f );

			int rPos = rand() % 15;
			int rDir = rand() % 2;

			if( fFrameDelay > 0.09f ) 
				this->setRotation( rDir == 0 ? rPos : -rPos );

			pos.x += dir == RIGHT ? 200.f*dt : -200.f*dt;

			break;
		}
	case TURRET_BULLET:
		{
			if( bState == false )
			{
				fVelocity	-= TURRET_GRAVITY * dt;
				pos.x		-= 100.f		  * dt;
				pos.y		+= fVelocity	  * dt;

				if( fVelocity <= 0.f )
				{
					bState = true;
				}
			}
			else if( bState == true )
			{
				fVelocity += TURRET_GRAVITY * dt;
				pos.x	  -= 100.f			* dt;
				pos.y	  -= fVelocity		* dt;

				if( pos.y <= 10.f )
				{
					if( this->getIsVisible() == true )
					{
						st::call()->SM.play( SND_Explosion );
						st::call()->efM.addEffect( ccp(pos.x-80.f, pos.y-20.f), TURRET_EFFECT, st::call()->worldNode );
						this->setIsVisible( false );
					}
				}
			}
			break;
		}

	case W_GRENADE:
		{
			if( bGreState == false )
			{
				fGreVelocity -= GRENADE_GRAVITY * dt;
				pos.x += dir == RIGHT ? 100.f * dt : -60.f * dt;
				pos.y += fGreVelocity * dt;

				if( fGreVelocity <= 0.f )
					bGreState = true;
			}
			else if( bGreState == true )
			{
				fGreVelocity += GRENADE_GRAVITY * dt;
				pos.x += dir == RIGHT ? 100.f * dt : -60.f * dt;
				pos.y -= fGreVelocity * dt;

				if( pos.y <= 15.f )
				{
					if( this->getIsVisible() == true )
					{
						this->setIsVisible( false );
						st::call()->efM.addEffect( ccp(pos.x-125.f, pos.y-35.f) , GRENADE_EFFECT, st::call()->worldNode );
					}
				}
			}
			break;
		}
	}
	
	this->setPosition( pos );
}
void Object_Bullet::animation( float dt )
{
	fFrameDelay += dt;

	switch( weapon )
	{
	case SHOTGUN:
		{
			if( fFrameDelay > 0.05f )
			{
				fFrameDelay = 0.f;
				nFrame++;

				if( nFrame >= 12 )
				{
					this->setIsVisible( false );
					return;
				}

				CCSprite* p = (CCSprite*)this->getChildByTag( 0 );
				p->setDisplayFrame( "SHOTGUN", nFrame );
			}
			break;
		}
	case MACHINEGUN:
		{
			break;
		}
	case NORMALGUN:
		{
			if( fFrameDelay > 0.1f )
			{
				fFrameDelay = 0.f;
				nFrame++;

				if( nFrame >= 2 ) nFrame = 0;

				CCSprite* p = (CCSprite*)this->getChildByTag( 0 );
				p->setDisplayFrame( "NORMALGUN", nFrame );
			}
			break;
		}
	case TURRET_BULLET:
		{
			if( this->getIsVisible() != false )
				this->setRotation( this->getRotation() - 100.f*dt );

			break;
		}
	case W_GRENADE:
		{
			if( this->getIsVisible() != false )
				this->setRotation( this->getRotation()-800.f*dt );

			break;
		}
	}	
}
