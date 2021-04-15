#pragma once
#include "Header.h"

class Debug : public CCLayer
{
protected:
			CGPoint	startPoint;
public:
	static	Debug*	create		( );
	virtual bool	init		( );
			void	update		( float dt );
			void	controller	( );

public:
	virtual	void	ccTouchesBegan( NSSet *pTouches, UIEvent *pEvent );
	virtual	void	ccTouchesMoved( NSSet *pTouches, UIEvent *pEvent );
	virtual	void	ccTouchesEnded( NSSet *pTouches, UIEvent *pEvent );

public:
			void	Line();
			void	Inform();
			void	BoxVisible( bool _visible );
};
