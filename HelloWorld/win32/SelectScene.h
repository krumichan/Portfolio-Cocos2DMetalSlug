#pragma once
#include "Header.h"

enum 
{
	KEY_LEFT, KEY_RIGHT
};

class SelectScene : public CCLayer
{
protected:
			CCSprite*		pSelect;
			CCSprite*		pBGA;
			CCSprite*		pChar[4];
			CCSprite*		pDoor[4];
			CCSprite*		pScreen;
			CCSprite*		pCScreen;
			CCSprite*		pUHero;
			CCSprite*		pDHero;

			float			fFrameDelay;
			float			fIDLEDelay;
			float			fP1Delay;

			int				nFrame;
			int				nPrevFrame;
			int				nUHeroFrame;
			int				nDHeroFrame;
			int				iKeyNum;

			bool			bStopFlag;
			bool			bPushEnter;
			bool			bDoorPlus;
			bool			bFadeFlag;
			bool			bGetKey;
			bool			bOKSound;

			char			szStr[128];
public:
	static	CCScene*		create();
	virtual	bool			init();
	virtual void			update( float dt );
};