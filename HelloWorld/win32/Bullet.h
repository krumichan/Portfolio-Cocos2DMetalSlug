#pragma once
#include "Header.h"

class Bullet : public CCSprite
{
protected:
			DIRECTION	m_Dir;
			float		fFrameDelay;
			float		nFrame;
			bool		bActive;


public:
	virtual bool		init		( );
	virtual void		initData	( );
	virtual void		update		( float dt );
	virtual void		action		( float dt ) = 0;
	virtual void		animation	( float dt ) = 0;


public:
			DIRECTION	getDirection( )					{ return m_Dir;		}
			void		setDirection( DIRECTION _dir )	{ m_Dir = _dir;		}
			bool		getActive	( )					{ return bActive;	}
			void		setActive	( bool _act )		{ bActive = _act;	}


public:
	virtual void		setIsVisible( bool _visible );
};