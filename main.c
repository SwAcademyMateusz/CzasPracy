#include <stdio.h>

#include "Platform_Types.h"
#include "UserInterface.h"
#include "WorkTimer.h"
#include "WorkHistory.h"

tWorkHistory WorkHistory;


int main()
{

	int cmd=0;
	tWorkTimer workTimer;
	tDayWorkTime workDay;


	WorkHistory_Init(&WorkHistory);
	WorkTimer_Init(&workTimer);


	WorkHistory_ReadFromFile(&WorkHistory);


	UserInterface_Init();

	cmd = 0;
	while(cmd != 'q')
	{
		cmd =  UserInterface_GetKeyCmd();

		if('s' == cmd)
		{
			WorkTimer_StartStop(&workTimer);
		}

		if('k' == cmd)
		{
			WorkTimer_End(&workTimer);
			workDay = WorkTimer_GetWorkDayData(&workTimer);
			WorkHistory_AddItem(&WorkHistory, workDay);
			printStats();
		}

		if(0!=cmd)
		{
			//printf("%d", cmd);

		}

		if(75 == cmd)
		{
			WorkHistory_PrevMonth(&WorkHistory);
			printStats();

		}
		if(77 == cmd)
		{
			WorkHistory_NextMonth(&WorkHistory);
			printStats();

		}

		UserInterface_Refresh(&workTimer);
	}


	WorkHistory_SaveToFile(&WorkHistory);
	UserInterface_Finish();

	return 0;
}
