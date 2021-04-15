#pragma once
#include "Header.h"

#include "Object_Hero.h"

class Stage1Scene : public CCLayer
{
protected:
			Object_Hero*	pHero;

			CCSprite*		pBGA;

			float			fFrameDelay;
			float			fmax;

			int				nFrame;

			bool			bGetBox;
public:
	static	CCScene*		create();
	virtual	bool			init();
	virtual void			update( float dt );
};
