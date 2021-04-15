#include "Manager_Bullet.h"
#include "Object_Box.h"
#include "st.h"

BulletManager::BulletManager()
{
	memset( pBullet, NULL, sizeof(pBullet) );
}

void BulletManager::addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, CCNode* _ground )
{
	for( int i = 0; i < MAX_BULLET; i++ )
	{
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == true ) continue;
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == false )
		{
			if( pBullet[i]->getParent() != NULL )
				pBullet[i]->getParent()->removeChild( pBullet[i], true );
			pBullet[i]->release();
		}
		
		pBullet[i] = new Object_Bullet;
		pBullet[i]->init		( _type		 );
		pBullet[i]->setPosition	( _pos		 );
		pBullet[i]->setDirection( _dir		 );
		_ground	  ->addChild	( pBullet[i] );
		return;
	}
}
void BulletManager::addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, CCNode* _ground, int _tag )
{
	for( int i = 0; i < MAX_BULLET; i++ )
	{
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == true ) continue;
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == false )
		{
			if( pBullet[i]->getParent() != NULL )
				pBullet[i]->getParent()->removeChild( pBullet[i], true );
			pBullet[i]->release();
		}

		pBullet[i] = new Object_Bullet;
		pBullet[i]->init		( _type					);
		pBullet[i]->setPosition	( _pos					);
		pBullet[i]->setDirection( _dir					);
		_ground   ->addChild	( pBullet[i], 0, _tag	);
		return;
	}
}
void BulletManager::addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, CCNode* _ground, int _tag, int _zOrder )
{
	for( int i = 0; i < MAX_BULLET; i++ ) 
	{
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == true ) continue;
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == false )
		{
			if( pBullet[i]->getParent() != NULL )
				pBullet[i]->getParent()->removeChild( pBullet[i], true );
			pBullet[i]->release();
		}

		pBullet[i] = new Object_Bullet;
		pBullet[i]->init		( _type						);
		pBullet[i]->setPosition	( _pos						);
		pBullet[i]->setDirection( _dir						);
		_ground   ->addChild	( pBullet[i], _zOrder, _tag );
		return;
	}
}

void BulletManager::addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, STATE _style, CCNode* _ground )
{
	for( int i = 0; i < MAX_BULLET; i++ ) 
	{
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == true ) continue;
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == false )
		{
			if( pBullet[i]->getParent() != NULL )
				pBullet[i]->getParent()->removeChild( pBullet[i], true );
			pBullet[i]->release();
		}

		pBullet[i] = new Object_Bullet;
		pBullet[i]->init			( _type			);
		pBullet[i]->setPosition		( _pos			);
		pBullet[i]->setDirection	( _dir			);
		pBullet[i]->setgunMoveStyle	( _style		);
		_ground   ->addChild		( pBullet[i]	);
		return;
	}
}
void BulletManager::addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, STATE _style, CCNode* _ground, int _tag )
{
	for( int i = 0; i < MAX_BULLET; i++ )
	{
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == true ) continue;
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == false )
		{
			if( pBullet[i]->getParent() != NULL )
				pBullet[i]->getParent()->removeChild( pBullet[i], true );
			pBullet[i]->release();
		}

		pBullet[i] = new Object_Bullet;
		pBullet[i]->init			( _type					);
		pBullet[i]->setPosition		( _pos					);
		pBullet[i]->setDirection	( _dir					);
		pBullet[i]->setgunMoveStyle	( _style				);
		_ground   ->addChild		( pBullet[i], 0, _tag	);
		return;
	}
}
void BulletManager::addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, STATE _style, CCNode* _ground, int _tag, int _zOrder )
{
	for( int i = 0; i < MAX_BULLET; i++ ) 
	{
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == true ) continue;
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == false )
		{
			if( pBullet[i]->getParent() != NULL )
				pBullet[i]->getParent()->removeChild( pBullet[i], true );
			pBullet[i]->release();
		}

		pBullet[i] = new Object_Bullet;
		pBullet[i]->init			( _type						);
		pBullet[i]->setPosition		( _pos						);
		pBullet[i]->setDirection	( _dir						);
		pBullet[i]->setgunMoveStyle	( _style					);
		_ground   ->addChild		( pBullet[i], _zOrder, _tag );
		return;
	}
}

void BulletManager::addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, STATE _style, int _angle, CCNode* _ground )
{
	for( int i = 0; i < MAX_BULLET; i++ ) 
	{
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == true ) continue;
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == false )
		{
			if( pBullet[i]->getParent() != NULL )
				pBullet[i]->getParent()->removeChild( pBullet[i], true );
			pBullet[i]->release();
		}

		pBullet[i] = new Object_Bullet;
		pBullet[i]->init			( _type			);
		pBullet[i]->setPosition		( _pos			);
		pBullet[i]->setDirection	( _dir			);
		pBullet[i]->setgunMoveStyle	( _style		);
		pBullet[i]->setBulletAngle	( _angle		);
		_ground   ->addChild		( pBullet[i]	);
		return;
	}
}
void BulletManager::addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, STATE _style, int _angle, CCNode* _ground, int _tag )
{
	for( int i = 0; i < MAX_BULLET; i++ ) 
	{
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == true ) continue;
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == false )
		{
			if( pBullet[i]->getParent() != NULL )
				pBullet[i]->getParent()->removeChild( pBullet[i], true );
			pBullet[i]->release();
		}

		pBullet[i] = new Object_Bullet;
		pBullet[i]->init			( _type					);
		pBullet[i]->setPosition		( _pos					);
		pBullet[i]->setDirection	( _dir					);
		pBullet[i]->setgunMoveStyle	( _style				);
		pBullet[i]->setBulletAngle	( _angle				);
		_ground   ->addChild		( pBullet[i], 0, _tag	);
		return;
	}
}
void BulletManager::addBullet( CGPoint _pos, DIRECTION _dir, WEAPON _type, STATE _style, int _angle, CCNode* _ground, int _tag, int _zOrder )
{
	for( int i = 0; i < MAX_BULLET; i++ ) 
	{
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == true ) continue;
		if( pBullet[i] != NULL && pBullet[i]->getIsVisible() == false )
		{
			if( pBullet[i]->getParent() != NULL )
				pBullet[i]->getParent()->removeChild( pBullet[i], true );
			pBullet[i]->release();
		}

		pBullet[i] = new Object_Bullet;
		pBullet[i]->init			( _type						);
		pBullet[i]->setPosition		( _pos						);
		pBullet[i]->setDirection	( _dir						);
		pBullet[i]->setgunMoveStyle	( _style					);
		pBullet[i]->setBulletAngle	( _angle					);
		_ground   ->addChild		( pBullet[i], _zOrder, _tag );
		return;
	}
}