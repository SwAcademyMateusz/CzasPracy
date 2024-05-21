/*
 * UserInterface.c
 *
 *  Created on: 21 maj 2024
 *      Author: nzyj2j
 */


#include "ApplTypes.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>

void resetConsole()
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(ConsoleHandle, 0 | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    system("cls");
}

void setConsoleFontRed()
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);
}

void setConsoleFontWhite()
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}

void setConsoleFontGreen()
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_GREEN);
}


void printTime(time_t time)
{
	char timeText[6];
	struct tm * timeinfo;

	timeinfo = localtime (&time);
	strftime(timeText, sizeof(timeText),"%H:%M",timeinfo);
	printf("%s", timeText);
}

void printTimeSpan(time_t time)
{
	char timeText[9];
	struct tm * timeinfo;

	timeinfo = gmtime(&time);
	strftime(timeText, sizeof(timeText),"%H:%M:%S",timeinfo);
	printf("%s", timeText);
}


void printDate(time_t time)
{
	char dateText[11];
	struct tm * timeinfo;

	timeinfo = localtime (&time);
	strftime(dateText, sizeof(dateText),"%Y.%m.%d",timeinfo);

	printf("%s", dateText);
}


void printWorkTime(tWorkTime workTime)
{
	printDate(workTime.startWork);
	printf("\t");
	printTime(workTime.startWork);
	printf("\t\t\t");
	printTime(workTime.endWork);
	printf("\t\t\t");
	printTimeSpan(workTime.workDuration);
	printf("\n");

}


void printHeader()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD targetPosition = {0,0};
	SetConsoleCursorPosition(ConsoleHandle, targetPosition);

    setConsoleFontGreen();
	printf("[s] Start/stop pracy \t [q] Zamknij \n");
	setConsoleFontWhite();
}

void printWorkStartTime()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD targetPosition = {0,2};
	SetConsoleCursorPosition(ConsoleHandle, targetPosition);

	printf("Godzina rozpoczecia pracy: ");
	printTime(time(NULL));

}

void printWorkDurationTime(time_t workTime)
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD targetPosition = {0,3};
	SetConsoleCursorPosition(ConsoleHandle, targetPosition);

	printf("Czas pracy: ");
	setConsoleFontRed();
    printTimeSpan(workTime);
	setConsoleFontWhite();

}



void printStats()
{

	tWorkTime workTime[3] = {{1716152618, 1716152628, 60},
			{1716152618+3600, 1716152628+7200, 600},
			{1716152618+7800, 1716152628+9800, 300}};
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD targetPosition = {0,8};
	SetConsoleCursorPosition(ConsoleHandle, targetPosition);


	setConsoleFontGreen();
	printf("\t\t\t<<  ");
	setConsoleFontWhite();
	printf("Maj 2024");
	setConsoleFontGreen();
	printf("   >>\n");
	setConsoleFontWhite();


	printf("Data \t\tGodzina rozpoczecia \tGodzina zakonczenia \tCzas pracy\n");
	printWorkTime(workTime[0]);
	printWorkTime(workTime[1]);
	printWorkTime(workTime[2]);
}


void UserInterface_Init()
{
	CONSOLE_CURSOR_INFO ConsoleCursonSettings = {10, FALSE};
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	// Hide cursor
	SetConsoleCursorInfo(ConsoleHandle, &ConsoleCursonSettings);

	//clear console
    system("cls");

    printHeader();

	printWorkStartTime();




	printStats();
	fflush(stdout);

}

void UserInterface_Finish()
{
	fflush(stdout);
    system("cls");
}

char UserInterface_GetKeyCmd()
{
	char cmd = 0;

	if(0 != kbhit())
	{
		cmd = getch();
	}

	return cmd;
}

void UserInterface_Refresh(time_t workTime)
{
	  static time_t lastTime=0;
	  time_t timeNow;

	  timeNow = time(NULL);
	  if(timeNow != lastTime)
	  {

		  printWorkDurationTime(workTime);
		  lastTime = timeNow;
	  }

}




