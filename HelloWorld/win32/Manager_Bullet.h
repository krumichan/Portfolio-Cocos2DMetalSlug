#pragma once

#include "Object_Bullet.h"
#define	 MAX_BULLET	20

class BulletManager
{
protected:
			Object_Bullet* pBullet[ MAX_BULLET ];
public:
			BulletManager();

	virtual void addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, CCNode* _ground );
	virtual void addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, CCNode* _ground, int _tag );
	virtual void addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, CCNode* _ground, int _tag, int _zOrder );

	virtual void addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, STATE _style, CCNode* _ground );
	virtual void addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, STATE _style, CCNode* _ground, int _tag );
	virtual void addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, STATE _style, CCNode* _ground, int _tag, int _zOrder );

	virtual void addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, STATE _style, int _angle, CCNode* _ground );
	virtual void addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, STATE _style, int _angle, CCNode* _ground, int _tag );
	virtual void addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, STATE _style, int _angle, CCNode* _ground, int _tag, int _zOrder );

	//function
};