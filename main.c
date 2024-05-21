#include <stdio.h>

#include "Platform_Types.h"
#include "UserInterface.h"
#include "WorkTimer.h"


int main()
{

	char cmd=0;
	tWorkTimer workTimer;
	WorkTimer_Init(&workTimer);

	UserInterface_Init();


	cmd = 0;
	while(cmd != 'q')
	{
		cmd =  UserInterface_GetKeyCmd();

		if('s' == cmd)
		{
			WorkTimer_StartStop(&workTimer);
		}

		UserInterface_Refresh(&workTimer);
	}


	UserInterface_Finish();

	return 0;
}
