#include "Bullet.h"

bool Bullet::init()
{
	if( !CCSprite::init() ) return false;
		
	this->initData		 ( );
	this->setAnchorPoint( ccp(0.f, 0.f) );
	this->setPosition	( ccp(0.f, 0.f) );

	this->setIsVisible( false );
	return true;

}
void Bullet::update( float dt )
{
	this->action	( dt );
	this->animation	( dt );
}

void Bullet::setIsVisible( bool _visible )
{
	if( _visible == true )
	{
		CCSprite::setIsVisible( true );
		schedule( schedule_selector(Bullet::update) );

		return;
	}
	else
	{
		CCSprite::setIsVisible( false );
		unschedule( schedule_selector(Bullet::update) );
		initData( );

		return;
	}
}

void Bullet::initData()
{
	m_Dir		= RIGHT;
	fFrameDelay = 0.f;
	nFrame		= 0;
	bActive		= false;
}