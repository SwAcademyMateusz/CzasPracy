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
#include "WorkTimer.h"
#include "WorkHistory.h"

#define HISTORY_DISPLAY_MAX_ROWS 28

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


void printWorkTime(tDayWorkTime workTime)
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
	printf("[s] Start/pauza pracy \t  [k] Koniec pracy \t [q] Zamknij \n");
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

void printWorkEndTime()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD targetPosition = {0,5};
	SetConsoleCursorPosition(ConsoleHandle, targetPosition);

	printf("Godzina zakonczenia pracy: ");
	printTime(time(NULL));

}
void clearWorkEndTime()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD targetPosition = {0,5};
	SetConsoleCursorPosition(ConsoleHandle, targetPosition);

	printf("                                                    ");
}

void printWorkDurationTime(time_t workTime, time_t pauseTime)
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD targetPosition = {0,3};
	SetConsoleCursorPosition(ConsoleHandle, targetPosition);

	printf("Czas pracy: ");
	setConsoleFontRed();
    printTimeSpan(workTime);
	setConsoleFontWhite();

	targetPosition.Y = 4;
	SetConsoleCursorPosition(ConsoleHandle, targetPosition);
	printf("Czas przerwy: ");
	printTimeSpan(pauseTime);
}


void printMonthYear(tYearMonth date)
{
	switch(date.month)
	{
		case 1:
			printf("styczen");
		break;
		case 2:
			printf("luty");
		break;
		case 3:
			printf("marzec");
		break;
		case 4:
			printf("kwiecien");
		break;
		case 5:
			printf("maj");
		break;
		case 6:
			printf("czerwiec");
		break;
		case 7:
			printf("lipiec");
		break;
		case 8:
			printf("sierpien");
		break;
		case 9:
			printf("wrzesien");
		break;
		case 10:
			printf("pazdziernik");
		break;
		case 11:
			printf("listopad");
		break;
		case 12:
			printf("grudzien");
		break;

		default:
		break;

	}

	printf(" %d", date.year);

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

	fflush(stdout);

}

void UserInterface_Finish()
{
	fflush(stdout);
    system("cls");
}

int UserInterface_GetKeyCmd()
{
	int cmd = 0;

	if(0 != kbhit())
	{
		cmd = getch();
		//printf("%d", cmd);

	}


	  if ( cmd == 224)
	  {
	        cmd = 256 + getch();
	  }
	  //cmd=getch(); /* get keyboard arrow */

	return cmd;
}

void UserInterface_Refresh(tWorkTimer *workTimer)
{
	  static time_t lastTime=0;
	  static tWorkTimerState lastTimerState = WORKTIMER_STATE_INIT;
	  tWorkTimerState currTimerState;
	  time_t timeNow;

	  if(WorkTimer_IsInitialized(workTimer))
	  {

		  timeNow = time(NULL);
		  if(timeNow != lastTime)
		  {
			  lastTime = timeNow;

			  printWorkDurationTime(WorkTimer_GetWorkTime(workTimer), WorkTimer_GetPauseTime(workTimer));

		  }
	  }

	  currTimerState = WorkTimer_GetWorkTimerState(workTimer);
	  if(currTimerState != lastTimerState)
	  {

		  if(WORKTIMER_STATE_WORK == currTimerState)
		  {
			  printWorkStartTime();
			  clearWorkEndTime();
		  }
		  else if(WORKTIMER_STATE_END == currTimerState)
		  {
			  printWorkEndTime();
		  }

		lastTimerState = currTimerState;
	  }

}

void UserInterface_RefreshHistory(tWorkHistory* workHistory)
{
	uint32 i, numOfItems=0;
	uint32 firstItemIndex=0;
	tDayWorkTime workDay;

	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD targetPosition = {0,8};
	SetConsoleCursorPosition(ConsoleHandle, targetPosition);
	for(i=0; i<HISTORY_DISPLAY_MAX_ROWS+3; i++)
	{
		printf("                                                                                  \n");
	}
	SetConsoleCursorPosition(ConsoleHandle, targetPosition);

	setConsoleFontGreen();
	printf("\t\t\t<<  ");
	setConsoleFontWhite();
	printMonthYear(workHistory->currentWorkMonth);
	setConsoleFontGreen();
	printf("   >>               \n");
	setConsoleFontWhite();


	printf("Data \t\tGodzina rozpoczecia \tGodzina zakonczenia \tCzas pracy\n");

	numOfItems = WorkHistory_GetMonthItems(workHistory, &firstItemIndex);

	time_t timeMonthSum = 0;

	for(i=firstItemIndex; i<firstItemIndex+numOfItems; i++)
	{
		workDay = WorkHistory_GetItem(workHistory, i);
		timeMonthSum += workDay.workDuration;
	}

	if(numOfItems>HISTORY_DISPLAY_MAX_ROWS)
	{
		firstItemIndex = firstItemIndex + (numOfItems-HISTORY_DISPLAY_MAX_ROWS);
		numOfItems = HISTORY_DISPLAY_MAX_ROWS;
	}

	for(i=firstItemIndex; i<firstItemIndex+numOfItems; i++)
	{
		workDay = WorkHistory_GetItem(workHistory, i);
		printWorkTime(workDay);
	}
	setConsoleFontRed();
	printf("                                                    SUMA: \t");
	printTimeSpan(timeMonthSum);
	setConsoleFontWhite();
	printf("\n");




}

