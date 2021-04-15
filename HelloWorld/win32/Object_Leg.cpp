#include "Object_Leg.h"
#include "st.h"

LEG* LEG::create( )
{
	LEG* p = new LEG;
	p->init();
	return p;
}
bool LEG::init()
{
	if( !CCSprite::init() ) return false;
	
	bUseFlag = false;
		
	this->setAnchorPoint( ccp(0.4f, 0.f) );
	this->setPosition	( ccp(0.f , 0.f) );

	this->addAnimation( st::call()->makeAnimation("resource/DOWN_HG_"			, "HG_DOWN"	  , 4) );
	this->addAnimation( st::call()->makeAnimation("resource/DOWN_SHOT_HG_"		, "HGS_DOWN"  , 8) );
	this->addAnimation( st::call()->makeAnimation("resource/DOWN_WALK_HG_"		, "HGW_DOWN"  , 7) );
	this->addAnimation( st::call()->makeAnimation("resource/HERO_INVINCIBLE_"	, "INVINCIBLE", 6) );
	this->addAnimation( st::call()->makeAnimation("resource/JUMP_STAND_LEG_"	, "SJ_LEG"	  , 8) );
	this->addAnimation( st::call()->makeAnimation("resource/RUN_LEG_"			, "R_LEG"	  , 11));
	this->addAnimation( st::call()->makeAnimation("resource/STAND_LEG_"			, "S_LEG"	  , 1) );
	this->addAnimation( st::call()->makeAnimation("resource/JUMP_RUN_LEG_"		, "JR_LEG"	  , 6) );
	this->addAnimation( st::call()->makeAnimation("resource/DOWN_GRENADE_HG_"	, "DW_GRENADE", 5) );

	return true;
}

const char* LEG::getStateString()
{
	switch( iState )
	{
	case HG_DOWN:	 return "HG_DOWN";
	case HGS_DOWN:	 return "HGS_DOWN";
	case HGW_DOWN:	 return "HGW_DOWN";
	case INVINCIBLE: return "INVINCIBLE";
	case SJ_LEG:	 return "SJ_LEG";
	case R_LEG:		 return "R_LEG";
	case S_LEG:		 return "S_LEG";
	case JR_LEG:	 return "JR_LEG";
	case DW_GRENADE: return "DW_GRENADE";
	}
}
void LEG::setValue( int _state )
{
	bUseFlag = true;

	iState		= _state;
	nFrame		= 0;
	fDelay		= 0;
	flimitDelay	= 0.1f;
	nlimitFrame = this->animationByName(getStateString())->getFrames()->count();
	schedule( schedule_selector(LEG::animation) );
}

void LEG::setValue( int _state, float _delay )
{
	bUseFlag = true;

	iState		= _state;
	nFrame		= 0;
	fDelay		= 0;
	flimitDelay	= _delay;
	nlimitFrame = this->animationByName(getStateString())->getFrames()->count();
	schedule( schedule_selector(LEG::animation) );
}


void LEG::animation( float dt )
{
	fDelay += dt;

	if( fDelay > flimitDelay )
	{
		fDelay = 0.f;
		nFrame++;

		if( nFrame >= nlimitFrame )
		{
			bUseFlag = false;
			unschedule( schedule_selector(LEG::animation) );
			return;
		}
	}
	this->setDisplayFrame( this->getStateString(), nFrame );
}