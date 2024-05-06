#include <stdio.h>
#include <time.h>

int main()
{
	time_t timeNow;
	struct tm * timeinfo;

	char timeText[80];

	timeNow = time(NULL);
	timeinfo = localtime (&timeNow);
	strftime(timeText, sizeof(timeText),"%H:%M:%S",timeinfo);

	printf("Godzina: %s", timeText);

	fflush(stdout);

	return 0;
}
