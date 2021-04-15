#pragma once
#include "Object_Machinegun.h"

#define MAX_MACHINEGUN	30

class MachinegunManager
{
private:
	Object_Machinegun*	pMachinegun[ MAX_MACHINEGUN ];

public:
	MachinegunManager();

public:
	void init	( CCNode* _ground );
	void dealloc( );
};