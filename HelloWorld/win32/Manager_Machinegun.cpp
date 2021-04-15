#include "Manager_Machinegun.h"

MachinegunManager::MachinegunManager()
{
	memset( pMachinegun, NULL, sizeof(pMachinegun) );
}

void MachinegunManager::init(CCNode* _ground)
{
	for( int i = 0; i < MAX_MACHINEGUN; i++ )
	{
		pMachinegun[i] = new Object_Machinegun;
		pMachinegun[i]->init		();
		pMachinegun[i]->setIsVisible( false );
		_ground		  ->addChild	( pMachinegun[i] );
	}
}
void MachinegunManager::dealloc()
{
	for( int i = 0; i < MAX_MACHINEGUN; i++ )
	{
		if( pMachinegun[i] != NULL && pMachinegun[i]->getParent() != NULL )
		{
			pMachinegun[i]->getParent()->removeChild( pMachinegun[i], true );
			pMachinegun[i]->release();
			pMachinegun[i] = NULL;
		}
	}

	memset( pMachinegun, NULL, sizeof(pMachinegun) );
}