#include "Object_Machinegun.h"
#include "st.h"

bool Object_Machinegun::init()
{
	if( !CCSprite::init() ) return false;

	CCSprite* pHBullet = CCSprite::spriteWithFile( "resource/HG_BULLET.png" );
	pHBullet->setAnchorPoint( ccp(0.f, 0.f)  );
	pHBullet->setPosition	( ccp(0.f, 0.f)  );
	this	->addChild		( pHBullet, 0, 0 );
	
	return true;
}

void Object_Machinegun::initData( )
{
	Bullet::initData();
	iAngle		 = 0;
	gunMoveStyle = IDLE;
}

void Object_Machinegun::action( float dt )
{
	CGPoint pos = this->getPosition();

	float worldX = st::call()->makeWorldX( pos, st::call()->worldNode->getScale() );
	float worldY = st::call()->makeWorldY( pos, st::call()->worldNode->getScale() );

	CGSize winSize = st::call()->winSize;

	if( (worldX <= 0.f || worldX >= winSize.width ) &&
		(worldY <= 0.f || worldY >= winSize.height) )
		this->setIsVisible( false );


	switch( gunMoveStyle )
	{
	case SHOT: case SIT_SHOT:
		{
			
			m_Dir == RIGHT ? pos.x += 200.f*dt : pos.x -= 200.f*dt;

			break;
		}
	}


	this->setPosition( pos );
}
void Object_Machinegun::animation( float dt )
{
	switch( gunMoveStyle )
	{
	case SHOT: case SIT_SHOT:
		{
			m_Dir == RIGHT ? this->setScaleX( 1.f ) : this->setScaleX( -1.f );
			break;
		}
	}
}
