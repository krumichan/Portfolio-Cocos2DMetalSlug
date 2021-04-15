#pragma once
#include "Header.h"

#include "Object_Leg.h"
#include "Object_Body.h"

class Object_Hero : public CCSprite
{
protected:
			LEG*	pLeg;
			BODY*	pBody;

			float	fMoveSec;

			STATE	state;
			STATE	prevState;
			STATE	shot;
			STATE	prevShot;

			// JUMP Value
			float	fDealy;
			float	fZ;
			float	fVelocity;

			bool	bInvincible;
			bool	bInvincibleSetLeg;
			
			// General Value
			bool	bMoveHold;

			// shot Value
			bool	bFired;
			bool	bReFired;
			bool	bSitFired;
			bool	bReSitFired;
			


public:
	static	Object_Hero* create();
	virtual bool		 init();
	virtual void		 update( float dt );
	virtual void		 action( float dt );
	virtual void		 animation( float dt );
};

#define GRAVITY	200
#define VELOCITY 400