#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include "Platform_Types.h"
#include "UserInterface.h"




int main()
{


	time_t timeNow, timeStart, diffTime;
	struct tm * timeinfo;
	char cmd=0;

	timeStart = time(NULL);

	UserInterface_Init();


	cmd = 0;
	while(cmd != 'q')
	{

		timeNow = time(NULL);
		diffTime = timeNow - timeStart;

		cmd =  UserInterface_GetKeyCmd();


		UserInterface_Refresh(diffTime);
	}


	UserInterface_Finish();

	return 0;
}
