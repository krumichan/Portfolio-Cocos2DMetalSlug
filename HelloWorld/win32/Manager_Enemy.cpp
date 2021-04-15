#include "Manager_Enemy.h"
#include "st.h"


EnemyManager::EnemyManager()
{
	memset( pEnemy, NULL, sizeof(pEnemy) );
}
void EnemyManager::addEnemy( CGPoint _pos, ENEMYTYPE _type, CCNode* _node )
{
	for( int i = 0; i < MAX_ENEMY; i++ )
	{
		if( pEnemy[i] != NULL && pEnemy[i]->getIsVisible() == true  ) continue;
		if( pEnemy[i] != NULL && pEnemy[i]->getIsVisible() == false )
		{
			if( pEnemy[i]->getParent() != NULL )
				pEnemy[i]->getParent()->removeChild( pEnemy[i], true );
			pEnemy[i]->release();
		}
		
		pEnemy[i] = new Object_Enemy;
		pEnemy[i]->init( _type );
		pEnemy[i]->setPosition( _pos );
		_node->addChild( pEnemy[i] );
		return;
	}
}
void EnemyManager::addEnemy( CGPoint _pos, ENEMYTYPE _type, CCNode* _node, int _tag )
{
	for( int i = 0; i < MAX_ENEMY; i++ )
	{
		if( pEnemy[i] != NULL && pEnemy[i]->getIsVisible() == true  ) continue;
		if( pEnemy[i] != NULL && pEnemy[i]->getIsVisible() == false )
		{
			if( pEnemy[i]->getParent() != NULL )
				pEnemy[i]->getParent()->removeChild( pEnemy[i], true );
			pEnemy[i]->release();
		}

		pEnemy[i] = new Object_Enemy;
		pEnemy[i]->init( _type );
		pEnemy[i]->setPosition( _pos );
		_node->addChild( pEnemy[i], 0, _tag );
		return;
	}
}
void EnemyManager::addEnemy( CGPoint _pos, ENEMYTYPE _type, CCNode* _node, int _zOrder, int _tag )
{
	for( int i = 0; i < MAX_ENEMY; i++ )
	{
		if( pEnemy[i] != NULL && pEnemy[i]->getIsVisible() == true  ) continue;
		if( pEnemy[i] != NULL && pEnemy[i]->getIsVisible() == false )
		{
			if( pEnemy[i]->getParent() != NULL )
				pEnemy[i]->getParent()->removeChild( pEnemy[i], true );
			pEnemy[i]->release();
		}

		pEnemy[i] = new Object_Enemy;
		pEnemy[i]->init( _type );
		pEnemy[i]->setPosition( _pos );
		_node->addChild( pEnemy[i], _zOrder, _tag );
		return;
	}
}
