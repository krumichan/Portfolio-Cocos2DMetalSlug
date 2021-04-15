#pragma once
#include "Header.h"

enum 
{
	rect, shape
};

class Object_Box : public CCSprite
{
protected:
			CGSize	size;
			float	radius;
			int		collisionType;
			BOXTYPE	boxType;
			int		nHP;
			bool	bUseFlag;

public:
	virtual bool	initWithRect  ( CGSize _size );
	virtual bool	initWithShape ( float _radius );
	virtual bool	CollisionCheck( CGPoint _pos );
	virtual CGRect	GetBoundBox	  ( );

	// Get Information
	virtual CGSize	getSize()	{ return size;	  }
	virtual BOXTYPE	getBoxType(){ return boxType; }
	virtual int		getHP()		{ return nHP;	  }
	virtual bool	getUseFlag(){ return bUseFlag;}

	// Set Information
	virtual void	setSize( CGSize _size )		{ size = _size;		}
	virtual void	setBoxType( BOXTYPE _type )	{ boxType = _type;	}
	virtual void	setHP( int _hp )			{ nHP = _hp;		}
	virtual void	setUseFlag( bool _use )		{ bUseFlag = _use;	}
};