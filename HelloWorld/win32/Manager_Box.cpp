#define CRT_SECURE_NO_WARNINGS
#include "Manager_Box.h"
#include "st.h"

BoxManager::BoxManager()
{
	memset( pBox, NULL, sizeof(pBox) );
}

void BoxManager::addBox( CGPoint _start, CGPoint _end, CCNode* _ground, BOXTYPE _bType )
{
	if( _start.x > _end.x )
	{
		float sw  = _start.x;
		_start.x = _end.x;
		_end.x   = sw;
	}
	if( _start.y > _end.y )
	{
		float sw  = _start.y;
		_start.y = _end.y;
		_end.y   = sw;
	}

	for( int i = 0; i < MAX_BOX; i++ )
	{
		if( pBox[i] != NULL && pBox[i]->getUseFlag() == true  ) continue;
		if( pBox[i] != NULL && pBox[i]->getUseFlag() == false )
		{
			if( pBox[i]->getParent() != NULL )
				pBox[i]->getParent()->removeChild( pBox[i], true );
			pBox[i]->release();
		}
		pBox[i] = new Object_Box;
		CGSize size = CGSizeMake( _end.x - _start.x, _end.y - _start.y );
		pBox[i]->initWithRect( size    );
		pBox[i]->setPosition ( _start  );
		pBox[i]->setBoxType	 ( _bType  );
		pBox[i]->setUseFlag	 ( true	   );
		_ground->addChild	 ( pBox[i] );
		saveData( );
		return;
	}
}
void BoxManager::addBox( CGPoint _start, CGPoint _end, CCNode* _ground, BOXTYPE _bType, int _tag )
{
	if( _start.x > _end.x )
	{
		float sw  = _start.x;
		_start.x = _end.x;
		_end.x   = sw;
	}
	if( _start.y > _end.y )
	{
		float sw  = _start.y;
		_start.y = _end.y;
		_end.y   = sw;
	}

	for( int i = 0; i < MAX_BOX; i++ )
	{
		if( pBox[i] != NULL && pBox[i]->getUseFlag() == true  ) continue;
		if( pBox[i] != NULL && pBox[i]->getUseFlag() == false )
		{
			if( pBox[i]->getParent() != NULL )
				pBox[i]->getParent()->removeChild( pBox[i], true );
			pBox[i]->release();
		}
		pBox[i] = new Object_Box;
		CGSize size = CGSizeMake( _end.x - _start.x, _end.y - _start.y );
		pBox[i]->initWithRect( size   );
		pBox[i]->setPosition ( _start );
		pBox[i]->setBoxType	 ( _bType );
		pBox[i]->setUseFlag	 ( true	  );
		_ground->addChild	 ( pBox[i], 0, _tag );
		saveData( );
		return;
	}
}
void BoxManager::addBox( CGPoint _start, CGPoint _end, CCNode* _ground, BOXTYPE _bType, int _tag, int _zOrder )
{
	
	if( _start.x > _end.x )
	{
		float sw  = _start.x;
		_start.x = _end.x;
		_end.x   = sw;
	}
	if( _start.y > _end.y )
	{
		float sw  = _start.y;
		_start.y = _end.y;
		_end.y   = sw;
	}

	for( int i = 0; i < MAX_BOX; i++ )
	{
		if( pBox[i] != NULL && pBox[i]->getUseFlag() == true  ) continue;
		if( pBox[i] != NULL && pBox[i]->getUseFlag() == false )
		{
			if( pBox[i]->getParent() != NULL )
				pBox[i]->getParent()->removeChild( pBox[i], true );
			pBox[i]->release();
		}
		pBox[i] = new Object_Box;
		CGSize size = CGSizeMake( _end.x - _start.x, _end.y - _start.y );
		pBox[i]->initWithRect( size   );
		pBox[i]->setPosition ( _start );
		pBox[i]->setBoxType	 ( _bType );
		pBox[i]->setUseFlag	 ( true	  );
		_ground->addChild	 ( pBox[i], _zOrder, _tag );
		saveData( );
		return;
	}
}

void BoxManager::addBox( CGPoint _start, CGPoint _end, int _hp, CCNode* _ground, BOXTYPE _bType )
{
	if( _start.x > _end.x )
	{
		float sw  = _start.x;
		_start.x = _end.x;
		_end.x   = sw;
	}
	if( _start.y > _end.y )
	{
		float sw  = _start.y;
		_start.y = _end.y;
		_end.y   = sw;
	}

	for( int i = 0; i < MAX_BOX; i++ )
	{
		if( pBox[i] != NULL && pBox[i]->getUseFlag() == true  ) continue;
		if( pBox[i] != NULL && pBox[i]->getUseFlag() == false )
		{
			if( pBox[i]->getParent() != NULL )
				pBox[i]->getParent()->removeChild( pBox[i], true );
			pBox[i]->release();
		}
		pBox[i] = new Object_Box;
		CGSize size = CGSizeMake( _end.x - _start.x, _end.y - _start.y );
		pBox[i]->initWithRect( size   );
		pBox[i]->setPosition ( _start );
		pBox[i]->setBoxType	 ( _bType );
		pBox[i]->setHP		 ( _hp	  );
		pBox[i]->setUseFlag	 ( true	  );
		_ground->addChild	 ( pBox[i] );
		saveData( );
		return;
	}
}
void BoxManager::addBox( CGPoint _start, CGPoint _end, int _hp, CCNode* _ground, BOXTYPE _bType, int _tag )
{
	if( _start.x > _end.x )
	{
		float sw  = _start.x;
		_start.x = _end.x;
		_end.x   = sw;
	}
	if( _start.y > _end.y )
	{
		float sw  = _start.y;
		_start.y = _end.y;
		_end.y   = sw;
	}

	for( int i = 0; i < MAX_BOX; i++ )
	{
		if( pBox[i] != NULL && pBox[i]->getUseFlag() == true  ) continue;
		if( pBox[i] != NULL && pBox[i]->getUseFlag() == false )
		{
			if( pBox[i]->getParent() != NULL )
				pBox[i]->getParent()->removeChild( pBox[i], true );
			pBox[i]->release();
		}
		pBox[i] = new Object_Box;
		CGSize size = CGSizeMake( _end.x - _start.x, _end.y - _start.y );
		pBox[i]->initWithRect( size   );
		pBox[i]->setPosition ( _start );
		pBox[i]->setBoxType	 ( _bType );
		pBox[i]->setHP		 ( _hp	  );
		pBox[i]->setUseFlag	 ( true	  );
		_ground->addChild	 ( pBox[i], 0, _tag );
		saveData( );
		return;
	}
}
void BoxManager::addBox( CGPoint _start, CGPoint _end, int _hp, CCNode* _ground, BOXTYPE _bType, int _tag, int _zOrder )
{
	if( _start.x > _end.x )
	{
		float sw  = _start.x;
		_start.x = _end.x;
		_end.x   = sw;
	}
	if( _start.y > _end.y )
	{
		float sw  = _start.y;
		_start.y = _end.y;
		_end.y   = sw;
	}

	for( int i = 0; i < MAX_BOX; i++ )
	{
		if( pBox[i] != NULL && pBox[i]->getUseFlag() == true  ) continue;
		if( pBox[i] != NULL && pBox[i]->getUseFlag() == false )
		{
			if( pBox[i]->getParent() != NULL )
				pBox[i]->getParent()->removeChild( pBox[i], true );
			pBox[i]->release();
		}
		pBox[i] = new Object_Box;
		CGSize size = CGSizeMake( _end.x - _start.x, _end.y - _start.y );
		pBox[i]->initWithRect( size   );
		pBox[i]->setPosition ( _start );
		pBox[i]->setBoxType	 ( _bType );
		pBox[i]->setHP		 ( _hp	  );
		pBox[i]->setUseFlag	 ( true	  );
		_ground->addChild	 ( pBox[i], _zOrder, _tag );
		saveData( );
		return;
	}
}


void BoxManager::addShape( CGPoint _start, float _radius, CCNode* _ground )
{
	for( int i = 0; i < MAX_BOX; i++ )
	{
		if( pBox[i] != NULL ) continue;
		pBox[i] = new Object_Box;
		pBox[i]->initWithShape( _radius );
		pBox[i]->setPosition  ( _start  );
		_ground->addChild	  ( pBox[i] );
		return;
	}
}
void BoxManager::addShape( CGPoint _start, float _radius, CCNode* _ground, int _tag )
{
	for( int i = 0; i < MAX_BOX; i++ )
	{
		if( pBox[i] != NULL ) continue;
		pBox[i] = new Object_Box;
		pBox[i]->initWithShape( _radius );
		pBox[i]->setPosition  ( _start  );
		_ground->addChild	  ( pBox[i], 0, _tag );
		return;
	}
}
void BoxManager::addShape( CGPoint _start, float _radius, CCNode* _ground, int _tag, int _zOrder )
{
	for( int i = 0; i < MAX_BOX; i++ ) 
	{
		if( pBox[i] != NULL ) continue;
		pBox[i] = new Object_Box;
		pBox[i]->initWithShape( _radius );
		pBox[i]->setPosition  ( _start  );
		_ground->addChild	  ( pBox[i], _zOrder, _tag );
		return;
	}
}
Object_Box*	BoxManager::CollisionCheck( CGPoint _pos )
{
	for( int i = 0 ; i < MAX_BOX; i++ )
	{
		if( pBox[i] == NULL ) continue;

		if( pBox[i]->CollisionCheck(_pos) )
			return pBox[i];
	}

	return NULL;
}

Object_Box*	BoxManager::CollisionCheck( CGPoint _pos, BOXTYPE _type )
{
	for( int i = 0 ; i < MAX_BOX; i++ )
	{
		if( pBox[i] == NULL ) continue;
		if( pBox[i]->getBoxType() != _type ) continue;

		if( pBox[i]->CollisionCheck(_pos) )
			return pBox[i];
	}

	return NULL;
}


bool BoxManager::Raycast( CGPoint _start, VectorInformation VI, RaycastHit* hit )
{
	hit->fDistance	= 0.f;
	hit->pCollider	= NULL;
	hit->point		= CGPointZero;

	for( ; VI.distance < hit->fDistance; hit->fDistance++ )
	{
		_start.x += VI.vec.x;
		_start.y += VI.vec.y;

		Object_Box* pCol = CollisionCheck( _start );
		
		if( pCol )
		{
			hit->pCollider	= pCol;
			hit->point		= _start;
			return true;
		}

		else if( pCol == NULL )
			break;
	}

	return false;
}

struct DATA
{
	BOXTYPE type;
	CGPoint start;
	CGPoint	end;
};

void BoxManager::saveData( )
{
	FILE* pFile = fopen( "BoxPosition.dat", "wb" );
	if( pFile == NULL ) return;

	DATA Memory[MAX_BOX];
	memset( Memory, NULL, sizeof(Memory) );

	for( int i = 0; i < MAX_BOX; i++ )
	{
		if( pBox[i] == NULL ) continue;
		CGSize	size  = pBox[i]->getSize();
		CGPoint start = pBox[i]->getPosition();
		CGPoint _end  = ccp( size.width + start.x, size.height + start.y );

		Memory[i].type	= pBox[i]->getBoxType();
		Memory[i].start = pBox[i]->getPosition();
		Memory[i].end	= _end;
	}

	fwrite( Memory, sizeof(Memory), 1, pFile );
	fclose( pFile );
}

void BoxManager::loadData( )
{
	FILE* pFile = fopen( "BoxPosition.dat", "rb" );
	if( pFile == NULL ) return;
	
	DATA Loading[MAX_BOX];
	memset( Loading, NULL, sizeof(Loading) );

	fread( Loading, sizeof(Loading), 1, pFile );
	
	for( int i = 0; i < MAX_BOX; i++ )
	{
	if( Loading[i].start.x == 0.f && Loading[i].start.y == 0.f &&
		Loading[i].end.x   == 0.f && Loading[i].end.y   == 0.f ) 
		continue;

		CGSize size = CGSizeMake( Loading[i].end.x - Loading[i].start.x, Loading[i].end.y - Loading[i].start.y );

		pBox[i] = new Object_Box;
		pBox[i]->initWithRect( size );
		pBox[i]->setBoxType( Loading[i].type );
		pBox[i]->setPosition( Loading[i].start );

		st::call()->worldNode->addChild( pBox[i], 300 );
	}

	fclose( pFile );
}

void BoxManager::loadData( CCNode* _ground )
{
	FILE* pFile = fopen( "BoxPosition.dat", "rb" );
	if( pFile == NULL ) return;

	DATA Loading[MAX_BOX];
	memset( Loading, NULL, sizeof(Loading) );

	fread( Loading, sizeof(Loading), 1, pFile );

	for( int i = 0; i < MAX_BOX; i++ )
	{
		if( Loading[i].start.x == 0.f && Loading[i].start.y == 0.f &&
			Loading[i].end.x   == 0.f && Loading[i].end.y   == 0.f ) 
			continue;

		CGSize size = CGSizeMake( Loading[i].end.x - Loading[i].start.x, Loading[i].end.y - Loading[i].start.y );

		pBox[i] = new Object_Box;
		pBox[i]->initWithRect( size );
		pBox[i]->setBoxType( Loading[i].type );
		pBox[i]->setPosition( Loading[i].start );

		_ground->addChild( pBox[i] );
	}

	fclose( pFile );
}

void BoxManager::setVisible( bool _visible )
{
	for( int i = 0; i < MAX_BOX; i++ )
	{
		if( pBox[i] == NULL ) continue;
		if( pBox[i]->getUseFlag() == false ) continue;

		pBox[i]->setIsVisible( _visible );
	}
}


bool BoxManager::collisionRectWithRect( Object_Box* _Anode, Object_Box* _Bnode )
{
	CGPoint Apos = _Anode->getParent()->getPosition();
 	Apos.x += _Anode->getPosition().x;
 	Apos.y += _Anode->getPosition().y;

	CGPoint Bpos = _Bnode->getParent()->getPosition();
 	Bpos.x += _Bnode->getPosition().x;
 	Bpos.y += _Bnode->getPosition().y;

	VectorInformation VI = st::call()->Distance( Apos, Bpos );

	if( VI.distance > 500.f ) return false;

	CGSize Asize = _Anode->getSize();
	CGSize Bsize = _Bnode->getSize();

	bool sameX = false;

	for( int i = 0; i < Asize.width; i += 1 )
	{
		if( (Apos.x+i <= Bpos.x+Bsize.width) && (Apos.x+i >= Bpos.x) )
		{
			sameX = true;
			break;
		}
	}

	if( sameX == false ) return false;

	for( int i = 0; i < Asize.height; i += 1 )
	{
		if( (Apos.y+i <= Bpos.y+Bsize.height) && (Apos.y+i >= Bpos.y) )
			return true;
	}

	return false;
}

bool BoxManager::collisionObject( Object_Box* _pBox, BOXTYPE _type )
{
	switch( _type )
	{

	// During Collision Hero Move Holding
	case BOX_HERO:
		{
			for( int i = 0; i < MAX_BOX; i++ )
			{
				if( pBox[i] == NULL ) continue;
				if( pBox[i]->getUseFlag () == false ) continue;
				if( pBox[i]->getBoxType () == _type ) continue;

				// Exception Handling
				if( pBox[i]->getBoxType () != BOX_TEXTURE && 
					pBox[i]->getBoxType () != BOX_TURRET  )
					continue;

				// Collision Handling
				if( collisionRectWithRect( _pBox, pBox[i]) )
				{
					CGPoint pos = _pBox->getParent()->getPosition();

					// Box Type - BOX_TEXTURE  -->   Texture Collision
					if( pBox[i]->getBoxType() == BOX_TEXTURE )
						pos.x -= 0.1f;

					// Box Type - BOX_TURRET   -->   Enemy(TURRET) Collision
					else if( pBox[i]->getBoxType() == BOX_TURRET )
						pos.x -= 1.f;

					_pBox->getParent()->setPosition( pos );
					return true;
				}
			}
			return false;
		}
	case BOX_TEXTURE:
		{
			for( int i = 0; i < MAX_BOX; i++ )
			{
				if( pBox[i] == NULL ) continue;
				if( pBox[i]->getUseFlag() == false ) continue;
				if( ( pBox[i]->getBoxType() != BOX_HEROBULLET &&
					  pBox[i]->getBoxType() != BOX_HEROGRENADE ) ||
					pBox[i]->getBoxType() == _type ) continue;

				if( collisionRectWithRect(_pBox, pBox[i]) )
				{
					CGPoint pos = pBox[i]->getParent()->getPosition();

					if( pBox[i]->getBoxType() == BOX_HEROBULLET )
					{
						pos.x += 30.f;
						pos.y -= 5.f;
						st::call()->efM.addEffect( pos, HG_EFFECT, st::call()->worldNode );

						pBox[i]->getParent()->setIsVisible( false );
					}

					pBox[i]->setUseFlag( false );
					return true;
				}
			}
			return false;
		}
	case BOX_TURRET: case BOX_BOSSBODY: case BOX_BOSSLEFT: case BOX_BOSSRIGHT:
		{
			for( int i = 0; i < MAX_BOX; i++ )
			{
				if( pBox[i] == NULL ) continue;
				if( pBox[i]->getUseFlag() == false ) continue;
				if( (pBox[i]->getBoxType() != BOX_HEROBULLET   &&
					 pBox[i]->getBoxType() != BOX_HEROGRENADE) ||
					pBox[i]->getBoxType() == _type ) continue;

				if( collisionRectWithRect(_pBox, pBox[i]) )
				{
					CGPoint pos = pBox[i]->getParent()->getPosition();

					if( pBox[i]->getBoxType() == BOX_HEROBULLET )
					{
						pos.x += 30.f;
						pos.y -= 5.f;
						st::call()->efM.addEffect( pos, HG_EFFECT, st::call()->worldNode );

						pBox[i]->getParent()->setIsVisible( false );
					}

					pBox[i]->setUseFlag( false );
					return true;
				}
			}
			return false;
		}

	case BOX_ENEMYATTACK:
		{
			for( int i = 0; i < MAX_BOX; i++ )
			{
				if( pBox[i] == NULL ) continue;
				if( pBox[i]->getIsVisible() == false ) continue;
				if( pBox[i]->getBoxType  () != BOX_HERO ||
					pBox[i]->getBoxType  () == _type ) continue;

				if( collisionRectWithRect(_pBox, pBox[i]) )
					return true;
			}
			break;
		}
	}
	return false;
}