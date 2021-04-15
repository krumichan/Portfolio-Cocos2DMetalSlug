#pragma once

#include "Object_Enemy.h"
#define MAX_ENEMY 20


class EnemyManager
{
protected:
	Object_Enemy* pEnemy[ MAX_ENEMY ];
public:
	EnemyManager();

	virtual void addEnemy( CGPoint _pos, ENEMYTYPE _type, CCNode* _node );
	virtual void addEnemy( CGPoint _pos, ENEMYTYPE _type, CCNode* _node, int _tag );
	virtual void addEnemy( CGPoint _pos, ENEMYTYPE _type, CCNode* _node, int _zOrder, int _tag );
};