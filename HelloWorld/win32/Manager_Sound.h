#pragma once
#include "Header.h"

#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment( lib, "fmodex_vc.lib" )
using namespace FMOD;

enum
{
	SND_Opening, SND_InCoin, SND_Select, SND_OK, SND_STAGE1, SND_SelectM, SND_Turret_Shot, SND_Explosion, SND_HGBULLET
};

class SoundManager
{
protected:
	System*		fMod;			
	Channel*	ch[10];			
	Sound*		snd[10];		
	FMOD_RESULT	r;

public:
	void		init		( );
	void		loading		( );
	void		play		( int _type		);
	void		stopSound	( int _ch		);
	void		ErrorCheck	( FMOD_RESULT r );
};