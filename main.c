#include <stdio.h>

#include "Platform_Types.h"
#include "UserInterface.h"
#include "WorkTimer.h"
#include "WorkHistory.h"



int main()
{

	int cmd=0;
	tWorkTimer workTimer;
	tDayWorkTime workDay;
	tWorkHistory workHistory;

	WorkHistory_Init(&workHistory);
	WorkTimer_Init(&workTimer);

	WorkHistory_ReadFromFile(&workHistory);


	UserInterface_Init();
	UserInterface_RefreshHistory(&workHistory);

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
			if(0==WorkTimer_End(&workTimer))
			{
				workDay = WorkTimer_GetWorkDayData(&workTimer);
				WorkHistory_AddItem(&workHistory, workDay);
				UserInterface_RefreshHistory(&workHistory);
			}
		}

		if(0!=cmd)
		{
			//printf("%d", cmd);

		}

		if(75 == cmd)
		{
			WorkHistory_PrevMonth(&workHistory);
			UserInterface_RefreshHistory(&workHistory);

		}
		if(77 == cmd)
		{
			WorkHistory_NextMonth(&workHistory);
			UserInterface_RefreshHistory(&workHistory);

		}

		UserInterface_Refresh(&workTimer);
	}


	WorkHistory_SaveToFile(&workHistory);
	UserInterface_Finish();

	return 0;
}
