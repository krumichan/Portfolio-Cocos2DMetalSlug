#pragma once
#include "Bullet.h"

class Object_Machinegun : public Bullet
{
protected:
			int		iAngle;
			STATE	gunMoveStyle;
public:
	virtual bool	init		( );
	virtual void	initData	( );
	virtual void	action		( float dt );
	virtual void	animation	( float dt );

public:
	int				getAngle	( )					{ return iAngle;			}
	STATE			getMoveStyle( )					{ return gunMoveStyle;		}

	void			setAngle	( int _angle )		{ iAngle = _angle;			}
	void			setMoveStyle( STATE _style )	{ gunMoveStyle = _style;	}

};