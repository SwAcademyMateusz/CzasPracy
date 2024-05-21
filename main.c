#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <stdlib.h>

#define STATE_PAUSE 0
#define STATE_WORK 1

int main()
{
	time_t timeNow, timeStart, diffTime, sumTime=0;
	struct tm * timeinfo;
	time_t sumTimeDispl;

	char cmd=0;
	char timeText[80];
	char timeStartText[40];
	char state=STATE_WORK;

    system("cls");

	printf("[s] Start pracy\n");
	printf("[q] Wyjscie z programu\n\n");

	while(cmd!='s' && cmd!='q')
	{
		cmd = getch();
	}

	timeStart = time(NULL);
	timeinfo = localtime (&timeStart);
	strftime(timeStartText, sizeof(timeStartText),"%H:%M:%S",timeinfo);


	while(cmd != 'q')
	{
	    system("cls");
		printf("[s] Start/przerwa w pracy\n");
		printf("[q] Wyjscie z programu\n\n");


		printf("Godzina rozpoczecia pracy: %s\n", timeStartText);
		timeNow = time(NULL);

		if(STATE_WORK==state)
		{
			diffTime = timeNow - timeStart;
			sumTimeDispl = diffTime + sumTime;
			timeinfo = gmtime(&sumTimeDispl);
			printf("[PRACA]");

		}
		else
		{
			timeinfo = gmtime(&sumTime);
			printf("[PRZERWA]");
		}

		strftime (timeText, sizeof(timeText), "%H:%M:%S",timeinfo);
		printf("Czas pracy: %s\n", timeText);

		while(timeNow == time(NULL))
		{
			if(0 != kbhit())
			{
				cmd = getch();
				if('s' == cmd)
				{
					if(state==STATE_PAUSE)
					{
						state = STATE_WORK;
						timeStart = time(NULL);
					}
					else if(STATE_WORK==state)
					{
						state=STATE_PAUSE;
						sumTime = sumTime + diffTime;
					}
				}
			}
		}
	}

	timeinfo = localtime(&timeNow);
	strftime (timeText, sizeof(timeText), "%H:%M:%S",timeinfo);
	printf("Godzina zakonczenia pracy: %s\n", timeText);

	cmd = getch();

	fflush(stdout);

	return 0;
}
