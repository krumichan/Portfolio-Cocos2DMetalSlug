#pragma once
#include "Header.h"

class IntroScene : public CCLayer
{
protected:
			CCSprite*	pIntro;
			CCSprite*	pStart;

			float		fFrameDelay;

			int			nFrame;
			int			nCoin;

			bool		bGetSpace;
			bool		bGetEnter;
			bool		bOpeningSound;
			bool		bOpening;

			char		szStr[128];
public:
	static	CCScene*	create( );
	virtual bool		init  ( );
	virtual void		update( float dt );
};