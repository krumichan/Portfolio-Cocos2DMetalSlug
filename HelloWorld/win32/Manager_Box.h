#pragma once

#include "Object_Box.h"
#define MAX_BOX	50

struct RaycastHit 
{
	Object_Box* pCollider;
	float		fDistance;
	CGPoint		point;
	
};

class BoxManager
{
protected:
			Object_Box* pBox[ MAX_BOX ];
public:
						BoxManager		( );

	virtual	void		addBox			( CGPoint _start, CGPoint _end, CCNode* _ground, BOXTYPE _bType );
	virtual	void		addBox			( CGPoint _start, CGPoint _end, CCNode* _ground, BOXTYPE _bType, int _tag );
	virtual	void		addBox			( CGPoint _start, CGPoint _end, CCNode* _ground, BOXTYPE _bType, int _tag, int _zOrder );

	virtual	void		addBox			( CGPoint _start, CGPoint _end, int _hp, CCNode* _ground, BOXTYPE _bType );
	virtual	void		addBox			( CGPoint _start, CGPoint _end, int _hp, CCNode* _ground, BOXTYPE _bType, int _tag );
	virtual	void		addBox			( CGPoint _start, CGPoint _end, int _hp, CCNode* _ground, BOXTYPE _bType, int _tag, int _zOrder );

	virtual	void		addShape		( CGPoint _start, float _radius, CCNode* _ground );
	virtual	void		addShape		( CGPoint _start, float _radius, CCNode* _ground, int _tag );
	virtual	void		addShape		( CGPoint _start, float _radius, CCNode* _ground, int _tag, int _zOrder );

// File ON, File OFF
public:
	virtual void		saveData		( );
	virtual void		loadData		( );
	virtual void		loadData		( CCNode* _ground );

// function
public:
	virtual void		setVisible			 ( bool _visible );
	virtual	Object_Box*	CollisionCheck		 ( CGPoint _pos );
	virtual	Object_Box*	CollisionCheck		 ( CGPoint _pos, BOXTYPE _type );
	virtual	bool		Raycast				 ( CGPoint _start, VectorInformation VI, RaycastHit* hit );
	virtual bool		collisionRectWithRect( Object_Box* _Anode, Object_Box* _Bnode );
	virtual bool		collisionObject		 ( Object_Box* _pBox, BOXTYPE _type );
};