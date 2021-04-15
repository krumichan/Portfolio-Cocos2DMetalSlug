#pragma once
#include "Header.h"

class Object_Texture : public CCSprite
{
protected:
			TEXTURETYPE		type;

			int				nFrame;
			int				nCoin;
			int				nHP;

			float			fFrameDelay;

			bool			bSpace;
			
public:
	virtual	bool			init	( TEXTURETYPE _type );
	virtual void			update	( float dt );


	// Function
	virtual void	SetCoin ( int _coin )	{ nCoin = _coin;	}
	virtual int		GetCoin ( )				{ return nCoin;		}

	virtual void	SetHP	( int _hp )		{ nHP = _hp;  }
	virtual int		GetHP	( )				{ return nHP; }

	virtual TEXTURETYPE GetType( ) { return type; }
};