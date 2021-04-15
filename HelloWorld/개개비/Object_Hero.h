#pragma once

#include "Object_Leg.h"
#include "Object_Body.h"

class Object_Hero : public CCSprite
{
protected:
			LEG*	pLeg;
			BODY*	pBody;

			float	fMoveSec;

			STATE	iUPstate;
			STATE	iUPprev;
			STATE	iDWstate;
			STATE	iDWprev;

			DIRECTION dir;

			// JUMP Value
			float	fDelay;
			float	fZ;
			float	fVelocity;

			bool	bInvincible;
			bool	bInvincibleSetLeg;
			
			// General Value
			bool	bMoveHold;

			// shot Value
			bool	bFired;
			bool	bReFired;
			bool	bMakeBullet;

			// Flag
			bool	bUpStay;
			


public:
	static	Object_Hero* create();
	virtual bool		 init();
	virtual void		 update( float dt );
	virtual void		 action( float dt );
	virtual void		 animation( float dt );

	virtual DIRECTION	 getDirection() { return dir; }
};

#define GRAVITY	600
#define VELOCITY 300