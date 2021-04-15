#include "Object_Box.h"
#include "st.h"

bool Object_Box::initWithRect( CGSize _size )
{
	if( !CCSprite::initWithFile("resource/BOX.png") ) return false;

	this->setIsVisible( false );
	
	bUseFlag		= false;
	collisionType	= rect;
	size			= _size;

	this->setAnchorPoint( ccp(0.f, 0.f) );
	this->setScaleX		( size.width  / 100.f );
	this->setScaleY		( size.height / 100.f );

	return true;
}
bool Object_Box::initWithShape( float _radius )
{
	if( !CCSprite::initWithFile("resource/SHAPE.png") ) return false;

	collisionType	= shape;
	radius			= _radius;

	this->setAnchorPoint( ccp(0.f, 0.f) );
	this->setScale		( radius / 50.f );
}
bool Object_Box::CollisionCheck( CGPoint _pos )
{

	switch( collisionType )
	{
	case rect:
		{
			return CGRect::CGRectContainsPoint( this->GetBoundBox(), _pos );
		}
	case shape:
		{
			VectorInformation VI = st::call()->Distance( this->getPosition(), _pos );
			return VI.distance < radius;
		}
	}

	return false;
}
CGRect Object_Box::GetBoundBox()
{
	CGRect rc;
	rc.origin	= this->getPosition();
	rc.size		= size;
	return rc;
}
