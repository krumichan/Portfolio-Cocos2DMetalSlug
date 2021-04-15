#include "st.h"

CCAnimation* st::makeAnimation( const char* _filename, const char* _aniname, int _count )
{
	CCAnimation* pAni = new CCAnimation;
	pAni->initWithName( _aniname );

	char szStr[256] = { 0 };
	for( int i = 0; i < _count; i++ )
	{
		sprintf_s( szStr, "%s%d.png", _filename, i );
		pAni->addFrameWithFileName( szStr );
	}

	return pAni;
}

float st::makeWorldX( CGPoint _pos, float _scale )
{
	CGPoint mapPos = worldNode->getPosition();

	float	worldX = mapPos.x + _pos.x * _scale;

	return	worldX;
}

float st::makeWorldY( CGPoint _pos, float _scale )
{
	CGPoint mapPos = worldNode->getPosition();

	float	worldY = mapPos.y + _pos.y * _scale;

	return worldY;
}

void st::InterpolateMoving( CCNode* _worldNode, CCNode* _node, float _max )
{
	float WorldX = st::call()->makeWorldX( _node->getPosition(), _worldNode->getScale() );

	if( WorldX < _max ) return;

	CGSize winSize = CCDirector::sharedDirector()->getWinSize();
	float gap	= WorldX - _max;

	gap /= 16.f;

	if( gap < 0.001f ) return;

	CGPoint pos = _worldNode->getPosition();
	pos.x -= gap;
	_worldNode->setPosition( pos );
}

VectorInformation st::Distance( CGPoint _end, CGPoint _start )
{
	VectorInformation VI;

	VI.vec		= ccp( _end.x - _start.x, _end.y - _start.y );
	VI.distance	= sqrtf( VI.vec.x*VI.vec.x + VI.vec.y*VI.vec.y );

	if( VI.distance )
	{
		VI.vec.x /= VI.distance;
		VI.vec.y /= VI.distance;
	}

	return VI;
}

float st::convertRadianToDegree( float _Radian )
{
	return ( _Radian * (3.141592) ) / 180.f;
}