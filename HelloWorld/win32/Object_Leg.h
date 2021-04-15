#pragma once
#include "Header.h"

class LEG : public CCSprite
{
protected:
	float	fDelay;
	float	flimitDelay;

	int		nFrame;
	int		nlimitFrame;

	int		iState;

	bool	bUseFlag;
public:
	static	LEG*	create();
	virtual bool	init();
	virtual void	setValue( int _state );
	virtual void	setValue( int _state, float _delay );
	virtual void	animation( float dt );
	const	char*	getStateString();

	virtual bool	getUseFlag()			{ return bUseFlag;	}
	virtual void	setUseFlag( bool _flag ) { bUseFlag = _flag;	}

	virtual int		getFrame()				{ return nFrame;	}

	virtual int		getNowState()			{ return iState;	}
};
