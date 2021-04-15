#include "Manager_Effect.h"

EffectManager::EffectManager()
{
	memset( pEffect, NULL, sizeof(pEffect) );
}
void EffectManager::addEffect( CGPoint _pos, EFFECTTYPE _type, CCNode* _ground )
{
	for( int i = 0; i < MAX_EFFECT; i++ )
	{
 		if( pEffect[i] != NULL && pEffect[i]->getIsVisible() == true  ) continue;
 		if( pEffect[i] != NULL && pEffect[i]->getIsVisible() == false )
 		{
			if( pEffect[i]->getParent() != NULL )
				pEffect[i]->getParent()->removeChild( pEffect[i], true );
 			delete pEffect[i];
 		}

		pEffect[i] = new Object_Effect;
		pEffect[i]->init		( _type		 );
		pEffect[i]->setPosition	( _pos		 );
		_ground   ->addChild	( pEffect[i] );
		return;
	}
}
void EffectManager::addEffect( CGPoint _pos, EFFECTTYPE _type, CCNode* _ground, int _tag )
{
	for( int i = 0; i < MAX_EFFECT; i++ )
	{
		if( pEffect[i] != NULL && pEffect[i]->getIsVisible() == true  ) continue;
		if( pEffect[i] != NULL && pEffect[i]->getIsVisible() == false )
		{
			if( pEffect[i]->getParent() != NULL )
				pEffect[i]->getParent()->removeChild( pEffect[i], true );
			delete pEffect[i];
		}

		pEffect[i] = new Object_Effect;
		pEffect[i]->init		( _type		 );
		pEffect[i]->setPosition	( _pos		 );
		_ground   ->addChild	( pEffect[i], 0, _tag );
		return;
	}
}
void EffectManager::addEffect( CGPoint _pos, EFFECTTYPE _type, CCNode* _ground, int _zOrder, int _tag )
{
	for( int i = 0; i < MAX_EFFECT; i++ )
	{
		if( pEffect[i] != NULL && pEffect[i]->getIsVisible() == true  ) continue;
		if( pEffect[i] != NULL && pEffect[i]->getIsVisible() == false )
		{
			if( pEffect[i]->getParent() != NULL )
				pEffect[i]->getParent()->removeChild( pEffect[i], true );
			delete pEffect[i];
		}

		pEffect[i] = new Object_Effect;
		pEffect[i]->init		( _type		 );
		pEffect[i]->setPosition	( _pos		 );
		_ground   ->addChild	( pEffect[i] ,_zOrder, _tag );
		return;
	}
}
