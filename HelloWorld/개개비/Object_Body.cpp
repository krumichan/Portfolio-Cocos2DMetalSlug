#include "Object_Body.h"
#include "st.h"

BODY* BODY::create( )
{
	BODY* p = new BODY;
	p->init();
	return p;
}
bool BODY::init()
{
	if( !CCSprite::init() ) return false;

	bUseFlag = false;


	this->setAnchorPoint( ccp(0.4f, 0.f) );
	this->setPosition	( ccp(0.f , 0.f) );

	this->addAnimation( st::call()->makeAnimation("resource/JUMP_RUN_BODY_HG_"	, "HGR_JUMP" , 6)  );
	this->addAnimation( st::call()->makeAnimation("resource/JUMP_STAND_HG_"		, "HGS_JUMP" , 8)  );
	this->addAnimation( st::call()->makeAnimation("resource/RUN_BODY_HG_"		, "HG_RUN"	 , 12) );
	this->addAnimation( st::call()->makeAnimation("resource/STAND_BODY_HG_"		, "HGS_STAND", 4)  );
	this->addAnimation( st::call()->makeAnimation("resource/NULL_DOWN_"			, "HGD_NULL" , 1)  );
	this->addAnimation( st::call()->makeAnimation("resource/NULL_INVINCIBLE_"	, "INV_NULL" , 1)  );
	this->addAnimation( st::call()->makeAnimation("resource/STAND_BODY_HG_"		, "HG_STAND" , 4)  );
	this->addAnimation( st::call()->makeAnimation("resource/SHOT_BODY_HG_"		, "HG_SHOT"	 , 9)  );
	this->addAnimation( st::call()->makeAnimation("resource/SHOT_UP_READY_HG_"  , "HGU_READY", 8)  );
	this->addAnimation( st::call()->makeAnimation("resource/SHOT_UP_HG_"		, "HGU_SHOT" , 7)  );
	this->addAnimation( st::call()->makeAnimation("resource/SHOT_GOUP_HG_"		, "SHOT_GOUP", 6)  );
	this->addAnimation( st::call()->makeAnimation("resource/SHOT_GODOWN_HG_"	, "SHOT_GODW", 5)  );
	this->addAnimation( st::call()->makeAnimation("resource/SHOT_GRENADE_HG_"	, "HG_GRENADE", 6) );

	this->addAnimation( st::call()->makeAnimation("resource/HG_GODW_"			, "HG_LOOKDOWN", 3) );
	this->addAnimation( st::call()->makeAnimation("resource/HG_GOUP_"			, "HG_LOOKUP"  , 3) );
	return true;
}

const char* BODY::getStateString()
{
	switch( iState )
	{
	case HGR_JUMP:	 return "HGR_JUMP";
	case HGS_JUMP:	 return "HGS_JUMP";
	case HG_RUN:	 return "HG_RUN";
	case HGS_STAND:  return "HGS_STAND";
	case HGD_NULL:	 return "HGD_NULL";
	case INV_NULL:	 return "INV_NULL";
	case HG_STAND:	 return "HG_STAND";
	case HG_SHOT:	 return "HG_SHOT";
	case HGU_READY:	 return "HGU_READY";
	case HG_LOOKDOWN:return "HG_LOOKDOWN";
	case HG_LOOKUP:	 return "HG_LOOKUP";
	case HGU_SHOT:	 return "HGU_SHOT";
	case SHOT_GOUP:  return "SHOT_GOUP";
	case SHOT_GODW:  return "SHOT_GODW";
	case HG_GRENADE: return "HG_GRENADE";
	}	 
}		 
void BODY::setValue( int _state )
{
	bUseFlag = true;

	iState		= _state;
	nFrame		= 0;
	fDelay		= 0;
	flimitDelay	= 0.1f;
	nlimitFrame = this->animationByName(getStateString())->getFrames()->count();
	schedule( schedule_selector(BODY::animation) );
}

void BODY::setValue( int _state, float _delay )
{
	bUseFlag = true;

	iState		= _state;
	nFrame		= 0;
	fDelay		= 0;
	flimitDelay	= _delay;
	nlimitFrame = this->animationByName(getStateString())->getFrames()->count();
	schedule( schedule_selector(BODY::animation) );
}

void BODY::animation( float dt )
{
	fDelay += dt;

	if( fDelay > flimitDelay )
	{
		fDelay = 0.f;
		nFrame++;

		if( nFrame >= nlimitFrame )
		{
			bUseFlag = false;
			unschedule( schedule_selector(BODY::animation) );
			return;
		}
	}
	
	this->setDisplayFrame( this->getStateString(), nFrame );
}