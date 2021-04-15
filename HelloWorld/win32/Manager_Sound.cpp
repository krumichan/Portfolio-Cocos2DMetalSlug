#include "Manager_Sound.h"

void SoundManager::init()
{
	// Fmod System Create
	r = System_Create( &fMod );
	ErrorCheck( r );	// Error Check.

	// Fmod Initialization
	r = fMod->init( 100, FMOD_INIT_NORMAL, NULL ); // Channel Cound, set Mode ( ex. PS3 ), SoundCard Pointer
	ErrorCheck( r );
}

void SoundManager::loading()
{
	// Sound Fild Loading
	r = fMod->createSound( "sound/Opening.mp3"		, FMOD_DEFAULT		, NULL, &snd[SND_Opening] );
	ErrorCheck( r );

	r = fMod->createSound( "sound/PUSHENTER.mp3"	, FMOD_DEFAULT		, NULL, &snd[SND_InCoin] );
	ErrorCheck( r );

	r = fMod->createSound( "sound/Select.mp3"		, FMOD_LOOP_NORMAL	, NULL, &snd[SND_Select] );
	ErrorCheck( r );

	r = fMod->createSound( "sound/OK.mp3"			, FMOD_DEFAULT		, NULL, &snd[SND_OK]     );
	ErrorCheck( r );

	r = fMod->createSound( "sound/STAGE1.mp3"		, FMOD_LOOP_NORMAL	, NULL, &snd[SND_STAGE1] );
	ErrorCheck( r );

	r = fMod->createSound( "sound/Select_Move.mp3"	, FMOD_DEFAULT		, NULL, &snd[SND_SelectM] );
	ErrorCheck( r );

	r = fMod->createSound( "sound/Explosion.mp3"	, FMOD_DEFAULT		, NULL, &snd[SND_Explosion] );
	ErrorCheck( r );

	r = fMod->createSound( "sound/Turret_Shot.mp3"	, FMOD_DEFAULT		, NULL, &snd[SND_Turret_Shot] );
	ErrorCheck( r );

	r = fMod->createSound( "sound/HGBULLET.mp3"		, FMOD_DEFAULT		, NULL, &snd[SND_HGBULLET] );
	ErrorCheck( r );
}
void SoundManager::play( int _type )
{
	fMod->update();
	r = fMod->playSound( FMOD_CHANNEL_FREE, snd[_type], false, &ch[_type] );
}
void SoundManager::stopSound( int _ch )
{
	ch[ _ch ]->stop();
}
void SoundManager::ErrorCheck( FMOD_RESULT r )
{
	if( r != FMOD_OK )
	{
		TCHAR szStr[512] = { 0 };
		MultiByteToWideChar( CP_ACP, NULL, FMOD_ErrorString(r), -1, szStr, 512 );
		MessageBox( NULL, szStr, L"사운드에러", MB_OK );
	}
}
