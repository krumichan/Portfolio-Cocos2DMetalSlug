#pragma once
#include "Object_Effect.h"

#define MAX_EFFECT	20

class EffectManager 
{
protected:
	Object_Effect* pEffect[ MAX_EFFECT ];

public:
	EffectManager();

	virtual void addEffect( CGPoint _pos, EFFECTTYPE _type, CCNode* _ground );
	virtual void addEffect( CGPoint _pos, EFFECTTYPE _type, CCNode* _ground, int _tag );
	virtual void addEffect( CGPoint _pos, EFFECTTYPE _type, CCNode* _ground, int _zOrder, int _tag );
};