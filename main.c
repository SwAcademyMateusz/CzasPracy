#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
	time_t timeNow, timeStart, diffTime;
	struct tm * timeinfo;

	char timeText[80];

	timeStart = time(NULL);
	timeinfo = localtime (&timeStart);
	strftime(timeText, sizeof(timeText),"%H:%M:%S",timeinfo);

	printf("Godzina: %s\n", timeText);

	for(int i=0; i<5; i++)
	{
		timeNow = time(NULL);
		diffTime = timeNow - timeStart;
		timeinfo = gmtime(&diffTime);
		strftime (timeText, sizeof(timeText), "%H:%M:%S",timeinfo);
		printf("Czas pracy: %s\n", timeText);

		sleep(1);
	}

	fflush(stdout);

	return 0;
}
