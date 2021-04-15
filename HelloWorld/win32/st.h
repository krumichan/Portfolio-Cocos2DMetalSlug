#pragma once
#include "Header.h"

#include "Manager_Sound.h"
#include "Manager_Texture.h"
#include "Manager_Box.h"
#include "Manager_Bullet.h"
#include "Manager_Enemy.h"
#include "Manager_Effect.h"

class st
{
protected:
	st() 
	{ 
		winSize = CCDirector::sharedDirector()->getWinSize();
	}

public:
	static st* instance;
	static st* call() 
	{
		if( instance == NULL ) instance = new st;
		return instance;
	}


// WinFrame
	CGSize winSize;


// Manager
public: 
	SoundManager	SM;
	TextureManager	TM;
	BulletManager	BM;
	BoxManager		boxM;
	EnemyManager	EM;
	EffectManager	efM;


// Animation
public:
	CCAnimation*	makeAnimation( const char* _filename, const char* _aniname, int _count );


// World Point
public:
	CCNode*	worldNode;
	float	makeWorldX( CGPoint _pos, float _scale = 0.f );
	float	makeWorldY( CGPoint _pos, float _scale = 0.f );
	void	InterpolateMoving( CCNode* _worldNode, CCNode* _node, float _max );
	float	convertRadianToDegree( float _Radian );


//function
public:
	VectorInformation Distance( CGPoint _end, CGPoint _start );	
};



#define RTOD(__X) convertRadianToDegree(__X);