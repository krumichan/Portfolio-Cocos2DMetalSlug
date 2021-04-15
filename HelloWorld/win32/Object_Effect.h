#pragma once
#include "Header.h"


class Object_Effect : public CCSprite
{
protected:
	int			nMaxFrame;
	int			nFrame;
	float		fDelay;
	EFFECTTYPE	iType;
	
public:
	virtual bool init	( EFFECTTYPE _type );
	virtual void update	( float dt );

	virtual void setMaxFrame( int _frame )	{ nMaxFrame = _frame;	}
	virtual int	 getMaxFrame( )				{ return nMaxFrame;		}

	//function
	const char* getEffectString( );
};