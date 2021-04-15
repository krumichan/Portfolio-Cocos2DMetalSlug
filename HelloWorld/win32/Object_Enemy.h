#pragma once
#include "Header.h"

class Object_Enemy : public CCSprite
{
protected:
	ENEMYTYPE iType;

public:
	virtual bool init( ENEMYTYPE _type );
	virtual void update( float dt );

// BOSS Function and Value
protected:
	bool bReady;


public:


// TURRET Function and Value
protected:
	int  nPattern;
	int  nHP;
	int  nFrame;
	float fDelay;
	float fTimer;
	float fZ;
	float fAttackMoveRange;
	DIRECTION MoveDir;

	bool bBossDie;

public:
	virtual void setHP( int _hp ) { nHP = _hp;		 }
	virtual int  getHP( )		  { return nHP;		 }
	virtual bool getDie()		  { return bBossDie; }
};