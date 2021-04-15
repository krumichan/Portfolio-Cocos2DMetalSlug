#include "Object_Enemy.h"
#include "st.h"

bool Object_Enemy::init( ENEMYTYPE _type )
{
	if( !CCSprite::init() ) return false;
	
	iType = _type;
	this->setAnchorPoint( ccp(0.f, 0.f) );
	this->setPosition	( ccp(0.f, 0.f) );

	switch( iType )
	{
	case BOSS:
		{
			fZ					= 0.f;
			fTimer				= 0.f;
			nPattern			= 0;
			bReady				= false;
			fDelay				= 0.f;
			fAttackMoveRange	= 1.f;
			MoveDir				= RIGHT;
			bBossDie			= false;

			CCSprite* pBody = new CCSprite;
			pBody->init			 ( );
			pBody->setAnchorPoint( ccp(0.f, 0.f) );
			pBody->setPosition	 ( ccp(0.f, 0.f) );
			pBody->addAnimation	 ( st::call()->makeAnimation("resource/BOSS_BODY_D_", "BOSSBODY", 5) );
			st::call()->boxM.addBox( ccp(60.f, 20.f), ccp(190.f, 40.f), 30, this, BOX_BOSSBODY, 10, 10 );
			this->addChild		 ( pBody, 1, 0 );

			CCSprite* pLeftWing = new CCSprite;
			pLeftWing->init			 ( );
			pLeftWing->setAnchorPoint( ccp(  0.f,  0.f) );
			pLeftWing->setPosition	 ( ccp(-10.f, 30.f) );
			pLeftWing->addAnimation	 ( st::call()->makeAnimation("resource/BOSS_LEFTWING_", "LEFTWING", 3) );
			st::call()->boxM.addBox( ccp(-10.f, 40.f), ccp(60.f, 60.f), 20, this, BOX_BOSSLEFT, 9, 10 );
			this->addChild( pLeftWing , 0, 1 );

			CCSprite* pRightWing = new CCSprite;
			pRightWing->init		  ( );
			pRightWing->setAnchorPoint( ccp(  0.f,  0.f) );
			pRightWing->setPosition	  ( ccp(141.f, 29.f) );
			pRightWing->addAnimation  ( st::call()->makeAnimation("resource/BOSS_RIGHTWING_", "RIGHTWING", 3) );
			st::call()->boxM.addBox( ccp(190.f, 40.f), ccp(260.f, 60.f), 20, this, BOX_BOSSRIGHT, 8, 10 );
			this->addChild( pRightWing, 0, 2 );

			st::call()->efM.addEffect( this->getPosition(), S1BOSSENGINE_EFFECT, this, 1, 3 );

			break;
		}
	case TURRET:
		{
			nPattern		 = 0;
			nFrame			 = 0;
			fDelay			 = 0.f;

			CCSprite* pTurret = new CCSprite;
			pTurret->init			( );
			pTurret->setAnchorPoint	( ccp(0.f, 0.f) );
			pTurret->setPosition	( ccp(0.f, 0.f) );
			this->addChild			( pTurret, 0, 0 );

			pTurret->addAnimation( st::call()->makeAnimation("resource/TURRET_MOVE_AIMDOWN_", "TURRETMOVE", 8) );
			pTurret->addAnimation( st::call()->makeAnimation("resource/TURRET_AIMDOWNTOUP_", "TURRETDOWNTOUP", 9) );
			pTurret->addAnimation( st::call()->makeAnimation("resource/TURRET_IDE_", "TURRETIDLE", 2) );
			pTurret->addAnimation( st::call()->makeAnimation("resource/TURRET_SHOT_AIMUP_", "TURRETSHOT", 8) );
			pTurret->addAnimation( st::call()->makeAnimation("resource/TURRET_DESTROYED_UP_", "TURRETDESTROYED", 20) );

			st::call()->boxM.addBox( ccp(20.f, 10.f), ccp(95.f, 85.f), 30, this, BOX_TURRET, 1 );
			
			break;
		}
	}

	schedule( schedule_selector(Object_Enemy::update) );
	return true;
}
void Object_Enemy::update( float dt )
{
	switch( iType )
	{
	case BOSS:
		{
			CGPoint pos = this->getPosition();
			CCSprite* pBody  = (CCSprite*)this->getChildByTag( 0 );
			CCSprite* pLeft  = (CCSprite*)this->getChildByTag( 1 );
			CCSprite* pRight = (CCSprite*)this->getChildByTag( 2 );

			Object_Box* pBRight	= (Object_Box*)this->getChildByTag( 8  );
			Object_Box* pBLeft	= (Object_Box*)this->getChildByTag( 9  );
			Object_Box* pBBody	= (Object_Box*)this->getChildByTag( 10 );
			

			switch( nPattern )
			{
			case 0:
				{
					if( pos.y >= 110.f )
					{
						pos.y -= 30.f * dt;
						this  ->setPosition		( pos );
						pBody ->setDisplayFrame ( "BOSSBODY" , 0 );
						pLeft ->setDisplayFrame ( "LEFTWING" , 0 );
						pRight->setDisplayFrame	( "RIGHTWING", 0 );
					}
					else if( pos.y < 110.f )
						nPattern	= 1;

					break;
				}
			case 1:
				{
					fTimer += dt * 5;
					fZ = sinf( fTimer ) / 8.f;
					pos.y += fZ;
					this->setPosition( pos );

					int RightHP = pBRight->getHP();
					int LeftHP	= pBLeft ->getHP();
					int BodyHP	= pBBody ->getHP(); 

					if( st::call()->boxM.collisionObject( pBRight	, BOX_BOSSRIGHT ) )
						pBRight->setHP( pBRight->getHP() - 1 );
					if( st::call()->boxM.collisionObject( pBLeft	, BOX_BOSSLEFT  ) )
						pBLeft ->setHP( pBLeft ->getHP() - 1 );
					if( st::call()->boxM.collisionObject( pBBody	, BOX_BOSSBODY  ) )
						pBBody ->setHP( pBBody ->getHP() - 1 );
	

					if( BodyHP <= 0 && LeftHP <= 0 && RightHP <= 0 )
					{
						pRight->setIsVisible	( false );
						pLeft ->setIsVisible	( false );
						pBody ->setDisplayFrame	( "BOSSBODY", 4 );
						fDelay = 0.f;
						nFrame = 0;
						nPattern = 5;
						return;
					}
					else
					{
						if( BodyHP <= 30 && BodyHP > 20 )
							pBody->setDisplayFrame( "BOSSBODY", 0 );
						else if( BodyHP <= 20 && BodyHP > 10 )
						{
							nPattern = 2;
							pBody->setDisplayFrame( "BOSSBODY", 1 );
						}
						else if( BodyHP <= 10 && BodyHP > 0 )
							pBody->setDisplayFrame( "BOSSBODY", 2 );
						else if( BodyHP <= 0 )
							pBody->setDisplayFrame( "BOSSBODY", 3 );



						if( LeftHP <= 20 && LeftHP > 10 )
							pLeft->setDisplayFrame( "LEFTWING", 0 );
						else if( LeftHP <= 10 && LeftHP > 0 )
						{
							nPattern = 2;
							pLeft->setDisplayFrame( "LEFTWING", 1 );
						}
						else if( LeftHP <= 0 )
							pLeft->setDisplayFrame( "LEFTWING", 2 );



						if( RightHP <= 20 && RightHP > 10 )
							pRight->setDisplayFrame( "RIGHTWING", 0 );
						else if( RightHP <= 10 && RightHP > 0 )
						{
							nPattern = 2;
							pRight->setDisplayFrame( "RIGHTWING", 1 );
						}
						else if( RightHP <= 0 )
							pRight->setDisplayFrame( "RIGHTWING", 2 );
					}

					break;
				}
			case 2:
				{
					int RightHP = pBRight->getHP();
					int LeftHP	= pBLeft ->getHP();
					int BodyHP	= pBBody ->getHP(); 

					if( st::call()->boxM.collisionObject( pBRight	, BOX_BOSSRIGHT ) )
						pBRight->setHP( pBRight->getHP() - 1 );
					if( st::call()->boxM.collisionObject( pBLeft	, BOX_BOSSLEFT  ) )
						pBLeft ->setHP( pBLeft ->getHP() - 1 );
					if( st::call()->boxM.collisionObject( pBBody	, BOX_BOSSBODY  ) )
						pBBody ->setHP( pBBody ->getHP() - 1 );

					if( BodyHP <= 0 && LeftHP <= 0 && RightHP <= 0 )
					{
						pRight->setIsVisible	( false );
						pLeft ->setIsVisible	( false );
						pBody ->setDisplayFrame	( "BOSSBODY", 4 );
						fDelay = 0.f;
						nFrame = 0;
						nPattern = 5;
						return;
					}
					else
					{	
						if( BodyHP <= 30 && BodyHP > 20 )
							pBody->setDisplayFrame( "BOSSBODY", 0 );
						else if( BodyHP <= 20 && BodyHP > 10 )
							pBody->setDisplayFrame( "BOSSBODY", 1 );
						else if( BodyHP <= 10 && BodyHP > 0 )
							pBody->setDisplayFrame( "BOSSBODY", 2 );
						else if( BodyHP <= 0 )
							pBody->setDisplayFrame( "BOSSBODY", 3 );

						if( LeftHP <= 20 && LeftHP > 10 )
							pLeft->setDisplayFrame( "LEFTWING", 0 );
						else if( LeftHP <= 10 && LeftHP > 0 )
							pLeft->setDisplayFrame( "LEFTWING", 1 );
						else if( LeftHP <= 0 )
							pLeft->setDisplayFrame( "LEFTWING", 2 );

						if( RightHP <= 20 && RightHP > 10 )
							pRight->setDisplayFrame( "RIGHTWING", 0 );
						else if( RightHP <= 10 && RightHP > 0 )
							pRight->setDisplayFrame( "RIGHTWING", 1 );
						else if( RightHP <= 0 )
							pRight->setDisplayFrame( "RIGHTWING", 2 );
					}
					
					//BOSS Movement
					fDelay += dt;

					if( fDelay > 2.f )
					{
						if( bReady == false )
						{
							bReady = true;
							st::call()->efM.addEffect( ccp(-5.f, -100.f), S1BOSSATTACKREADY_EFFECT, this, 1, 4 );
						}

						CCSprite* pEngine = (CCSprite*)this->getChildByTag( 3 );
						if( pEngine != NULL && pEngine->getParent() != NULL )
							pEngine->getParent()->removeChild( pEngine, true );

						if( fDelay > 3.5f )
						{
							fDelay   = 0.f;
							nPattern = 3;

							CCSprite* pReady = (CCSprite*)this->getChildByTag( 4 );
							if( pReady != NULL && pReady->getParent() != NULL )
								pReady->getParent()->removeChild( pReady, true );
						}
					}
					break;
				}

			case 3:
				{

					int RightHP = pBRight->getHP();
					int LeftHP	= pBLeft ->getHP();
					int BodyHP	= pBBody ->getHP(); 

					if( st::call()->boxM.collisionObject( pBRight	, BOX_BOSSRIGHT ) )
						pBRight->setHP( pBRight->getHP() - 1 );
					if( st::call()->boxM.collisionObject( pBLeft	, BOX_BOSSLEFT  ) )
						pBLeft ->setHP( pBLeft ->getHP() - 1 );
					if( st::call()->boxM.collisionObject( pBBody	, BOX_BOSSBODY  ) )
						pBBody ->setHP( pBBody ->getHP() - 1 );

					if( BodyHP <= 0 && LeftHP <= 0 && RightHP <= 0 )
					{
						pRight->setIsVisible	( false );
						pLeft ->setIsVisible	( false );
						pBody ->setDisplayFrame	( "BOSSBODY", 4 );
						fDelay = 0.f;
						nFrame = 0;
						nPattern = 5;
						return;
					}
					else
					{	
						if( BodyHP <= 30 && BodyHP > 20 )
							pBody->setDisplayFrame( "BOSSBODY", 0 );
						else if( BodyHP <= 20 && BodyHP > 10 )
							pBody->setDisplayFrame( "BOSSBODY", 1 );
						else if( BodyHP <= 10 && BodyHP > 0 )
							pBody->setDisplayFrame( "BOSSBODY", 2 );
						else if( BodyHP <= 0 )
							pBody->setDisplayFrame( "BOSSBODY", 3 );

						if( LeftHP <= 20 && LeftHP > 10 )
							pLeft->setDisplayFrame( "LEFTWING", 0 );
						else if( LeftHP <= 10 && LeftHP > 0 )
							pLeft->setDisplayFrame( "LEFTWING", 1 );
						else if( LeftHP <= 0 )
							pLeft->setDisplayFrame( "LEFTWING", 2 );

						if( RightHP <= 20 && RightHP > 10 )
							pRight->setDisplayFrame( "RIGHTWING", 0 );
						else if( RightHP <= 10 && RightHP > 0 )
							pRight->setDisplayFrame( "RIGHTWING", 1 );
						else if( RightHP <= 0 )
							pRight->setDisplayFrame( "RIGHTWING", 2 );
					}


					fDelay += dt;

					if( bReady == true )
					{
						bReady = false;
						st::call()->efM.addEffect(ccp(-5.f, -100.f), S1BOSSATTACK_EFFECT, this, 1, 5 );
					}

					if( fDelay > 3.f )
					{
						float worldX = st::call()->makeWorldX( pos, 3.45f ); //74.889709

						if( MoveDir == RIGHT )
						{
							pos.x += dt * 50.f;

							float worldX = st::call()->makeWorldX( pos, 3.45f );

							if( worldX >= 400.f )
							{
								MoveDir = LEFT;
							}
							else this->setPosition( pos );
						}
						else if( MoveDir == LEFT )
						{
							pos.x -= dt * 50.f;

							float worldX = st::call()->makeWorldX( pos, 3.45f );

							if( worldX <= -220.f )
							{
								MoveDir = RIGHT;
							}
							else this->setPosition( pos );
						}
						if( fDelay > 10.f )
						{
							if( worldX >= 72.f && worldX <= 76.f )
							{
								MoveDir = RIGHT;
								fDelay = 0.f;
								nPattern = 4;

								CCSprite* pAttack = (CCSprite*)this->getChildByTag( 5 );
								if( pAttack != NULL && pAttack->getParent() != NULL )
									pAttack->getParent()->removeChild( pAttack, true );

								if( bReady == false )
								{
									bReady = true;
									st::call()->efM.addEffect( ccp(-5.f, -100.f), S1BOSSATTACKEND_EFFECT, this, 1, 6 );
								}
							}
						}
					}

					break;
				}
			case 4:
				{

					int RightHP = pBRight->getHP();
					int LeftHP	= pBLeft ->getHP();
					int BodyHP	= pBBody ->getHP(); 

					if( st::call()->boxM.collisionObject( pBRight	, BOX_BOSSRIGHT ) )
						pBRight->setHP( pBRight->getHP() - 1 );
					if( st::call()->boxM.collisionObject( pBLeft	, BOX_BOSSLEFT  ) )
						pBLeft ->setHP( pBLeft ->getHP() - 1 );
					if( st::call()->boxM.collisionObject( pBBody	, BOX_BOSSBODY  ) )
						pBBody ->setHP( pBBody ->getHP() - 1 );

					if( BodyHP <= 0 && LeftHP <= 0 && RightHP <= 0 )
					{
						pRight->setIsVisible	( false );
						pLeft ->setIsVisible	( false );
						pBody ->setDisplayFrame	( "BOSSBODY", 4 );
						fDelay = 0.f;
						nFrame = 0;
						nPattern = 5;
						return;
					}
					else
					{	
						if( BodyHP <= 30 && BodyHP > 20 )
							pBody->setDisplayFrame( "BOSSBODY", 0 );
						else if( BodyHP <= 20 && BodyHP > 10 )
							pBody->setDisplayFrame( "BOSSBODY", 1 );
						else if( BodyHP <= 10 && BodyHP > 0 )
							pBody->setDisplayFrame( "BOSSBODY", 2 );
						else if( BodyHP <= 0 )
							pBody->setDisplayFrame( "BOSSBODY", 3 );

						if( LeftHP <= 20 && LeftHP > 10 )
							pLeft->setDisplayFrame( "LEFTWING", 0 );
						else if( LeftHP <= 10 && LeftHP > 0 )
							pLeft->setDisplayFrame( "LEFTWING", 1 );
						else if( LeftHP <= 0 )
							pLeft->setDisplayFrame( "LEFTWING", 2 );

						if( RightHP <= 20 && RightHP > 10 )
							pRight->setDisplayFrame( "RIGHTWING", 0 );
						else if( RightHP <= 10 && RightHP > 0 )
							pRight->setDisplayFrame( "RIGHTWING", 1 );
						else if( RightHP <= 0 )
							pRight->setDisplayFrame( "RIGHTWING", 2 );
					}


					fDelay += dt;

					if( fDelay >= 1.f )
					{
						bReady	 = false;
						fDelay	 = 0.f;
						nPattern = 2;
						MoveDir  = RIGHT;

						CCSprite* pEnd = (CCSprite*)this->getChildByTag( 6 );
						if( pEnd != NULL && pEnd->getParent() != NULL )
							pEnd->getParent()->removeChild( pEnd, true );

						st::call()->efM.addEffect( ccp(0.f, 0.f), S1BOSSENGINE_EFFECT, this, 1, 3 );
					}
					break;
				}
			case 5:
				{
					CCSprite* pEngine = (CCSprite*)this->getChildByTag( 3 );
					if( pEngine != NULL && pEngine->getParent() != NULL )
						pEngine->getParent()->removeChild( pEngine, true );

					CCSprite* pReady = (CCSprite*)this->getChildByTag( 4 );
					if( pReady != NULL && pReady->getParent() != NULL )
						pReady->getParent()->removeChild( pReady, true );

					CCSprite* pAttack = (CCSprite*)this->getChildByTag( 5 );
					if( pAttack != NULL && pAttack->getParent() != NULL )
						pAttack->getParent()->removeChild( pAttack, true );

					CCSprite* pEnd = (CCSprite*)this->getChildByTag( 6 );
					if( pEnd != NULL && pEnd->getParent() != NULL )
						pEnd->getParent()->removeChild( pEnd, true );


					CGPoint pos = this->getPosition();
					pos.y -= 20*dt;

					if( pos.y < 30.f )
					{
						bBossDie = true;
						return;
					}

					fDelay += dt;

					if( fDelay > 0.1f )
					{
						fDelay = 0.f;
						nFrame++;
					}
					if( nFrame % 20 < 10 )
						pos.x += 100.f * dt;
					else 
						pos.x -= 100.f * dt;

					this->setPosition( pos );
					break;
				}
			}
			break;			
		}

	case TURRET:
		{
			switch( nPattern )
			{
			case 0:
				{
					
					CGPoint pos = this->getPosition();
					fDelay += dt;


					if( pos.x >= 300.f )
					{
						pos.x -= 20.f * dt;
						this->setPosition( pos );	

						if( fDelay > 0.07f )
						{
							fDelay = 0.f;
							nFrame++;

							if( nFrame >= 8 ) nFrame = 0;

							Object_Enemy* pTurret = (Object_Enemy*)this->getChildByTag( 0 );
							pTurret->setDisplayFrame( "TURRETMOVE", nFrame );
						}
					}
					else
					{
						if( fDelay > 1.5f )
						{
							fDelay   = 0.f;
							nFrame   = 0;
							nPattern = 1;
						}
					}			
	
					break;
				}
			case 1:
				{
					fDelay += dt;

					if( fDelay > 0.2f && nFrame < 9 )
					{
						Object_Enemy* pTurret = (Object_Enemy*)this->getChildByTag( 0 );
						pTurret->setDisplayFrame( "TURRETDOWNTOUP", nFrame );

						fDelay = 0.f;
						nFrame++;
					}

					else if( fDelay > 1.5f && nFrame >= 9 ) 
					{
						fDelay   = 0.f;
						nFrame   = 0;
						nPattern = 2;
					}

					break;
				}
			case 2:
				{
					fDelay += dt;

					Object_Enemy* pTurret = (Object_Enemy*)this->getChildByTag( 0 );

					if( (int)(fDelay*1000) % 2 == 0 )
						pTurret->setDisplayFrame( "TURRETIDLE", 0 );
					else 
						pTurret->setDisplayFrame( "TURRETIDLE", 1 );

					if( fDelay > 1.5f )
					{
						fDelay   = 0.f;
						nFrame   = 0;
						nPattern = 3;
					}

					break;
				}
			case 3:
				{
					fDelay += dt;

					Object_Box* pBox = (Object_Box*)this->getChildByTag(1);

					if( st::call()->boxM.collisionObject(pBox, BOX_TURRET) == true )
						pBox->setHP( pBox->getHP() - 1 );

						if( pBox->getHP() <= 0 )
						{
							fDelay	 = 0.f;
							nFrame	 = 0;
							nPattern = 4;
						}


					if( fDelay > 0.07f )
					{
						fDelay = 0.f;
						nFrame++;

						if( nFrame >= 8 ) 
						{
							CGPoint pos = this->getPosition();
							pos.y += 100.f;
							st::call()->SM.play( SND_Turret_Shot );
							st::call()->BM.addBullet( pos, LEFT, TURRET_BULLET, st::call()->worldNode );
							nFrame = 0;
						}

						Object_Enemy* pTurret = (Object_Enemy*)this->getChildByTag( 0 );
						pTurret->setDisplayFrame( "TURRETSHOT", nFrame );
					}
					

					break;
				}
			case 4:
				{
					fDelay += dt;

					if( fDelay > 0.07f )
					{
						fDelay = 0.f;
						nFrame++;

						if( nFrame >= 20 )
						{
							Object_Box* pBox = (Object_Box*)this->getChildByTag(1);
							
							if( pBox == NULL || pBox->getUseFlag() == false ) return;

							pBox->setUseFlag  ( false );
							this->setIsVisible( false );
							break;
						}
						Object_Enemy* pTurret = (Object_Enemy*) this->getChildByTag( 0 );
						pTurret->setDisplayFrame( "TURRETDESTROYED", nFrame );
					}
					break;
				}
			}
			break;
		}
	}
}