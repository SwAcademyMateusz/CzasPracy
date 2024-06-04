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


	tDayWorkTime workTime[4] = {
			{0, 5*3600, 3*3600},
			{1716152618, 1716152628, 60},
			{1716152618+3600, 1716152628+7200, 600},
			{1716152618+7800, 1716152628+9800, 300}};



	WorkHistory_AddItem(&WorkHistory, workTime[0]);
	WorkHistory_AddItem(&WorkHistory, workTime[1]);
	WorkHistory_AddItem(&WorkHistory, workTime[2]);
	WorkHistory_AddItem(&WorkHistory, workTime[3]);




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


	UserInterface_Finish();

	return 0;
}
