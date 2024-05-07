#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

int main()
{
	time_t timeNow, timeStart, diffTime;
	struct tm * timeinfo;

	char cmd=0;
	char timeText[80];
	char timeStartText[40];

    system("cls");

	printf("[s] Start pracy\n\n");

	while(cmd!='s')
	{
		cmd = getch();
	}

	timeStart = time(NULL);
	timeinfo = localtime (&timeStart);
	strftime(timeStartText, sizeof(timeStartText),"%H:%M:%S",timeinfo);


	cmd = 0;
	while(1)
	{
	    system("cls");
		printf("[s] Zakonczenie pracy\n\n");


		printf("Godzina rozpoczecia pracy: %s\n", timeStartText);

		timeNow = time(NULL);
		diffTime = timeNow - timeStart;
		timeinfo = gmtime(&diffTime);
		strftime (timeText, sizeof(timeText), "%H:%M:%S",timeinfo);
		printf("Czas pracy: %s\n", timeText);

		if(0 != kbhit())
		{
			cmd = getch();
			if('s' == cmd)
			{
				timeinfo = localtime(&timeNow);
				strftime (timeText, sizeof(timeText), "%H:%M:%S",timeinfo);
				printf("Godzina zakonczenia pracy: %s\n", timeText);

				break;
			}
		}

		sleep(1);
	}

	cmd = getch();

	fflush(stdout);

	return 0;
}
