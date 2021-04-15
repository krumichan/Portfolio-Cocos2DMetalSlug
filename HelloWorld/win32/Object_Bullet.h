#pragma once
#include "Header.h"

class Object_Bullet : public CCSprite
{
protected:
			DIRECTION	dir;
			WEAPON		weapon;

			float		fFrameDelay;
			float		fsinAngle;
			float		fconAngle;
			
			int			nFrame;
			int			iAngle;

			STATE		gunMoveStyle;

			bool		bRotation;
public:
	virtual bool init		 ( WEAPON _weapon );
	virtual void animation	 ( float dt );
	virtual void action		 ( float dt );
	virtual void update		 ( float dt );
	virtual void setDirection( DIRECTION _dir ) { dir = _dir;			 }
	virtual void setgunMoveStyle( STATE _style) { gunMoveStyle = _style; }
	virtual void setBulletAngle( int _angle )	{ iAngle = _angle;		 }
	
	
	
	virtual WEAPON getType() { return weapon; }


// TURRET_BULLET
protected:
	float fVelocity;
	float fZ;
	bool bState;

// GRENADE
protected:
	float fGreVelocity;
	float fGreZ;
	bool bGreState;
};


#define TURRET_VELOCITY	300
#define TURRET_GRAVITY	600

#define GRENADE_VELOCITY 300
#define GRENADE_GRAVITY	600