/*
 * WorkHistory.c
 *
 *  Created on: 3 cze 2024
 *      Author: nzyj2j
 */
#include "Platform_Types.h"
#include "time.h"
#include "ApplTypes.h"
#include "WorkHistory.h"
#include <stdio.h>



tYearMonth Time2YearMonth(time_t date)
{
	tYearMonth retVal;
	struct tm * timeinfo;

	timeinfo = localtime (&date);

	retVal.month =  timeinfo->tm_mon%12 + 1;
	retVal.year = 1900+timeinfo->tm_year;

	return retVal;
}



void WorkHistory_Init(tWorkHistory *workHistory)
{
	workHistory->currentWorkMonth = Time2YearMonth(time(NULL));
	workHistory->numOfDataItems = 0;
}

void WorkHistory_PrevMonth(tWorkHistory *workHistory)
{
	uint32 itemPtr;
	sint16 monthsOffset = (12 + workHistory->currentWorkMonth.month - 1) % 12;
	if(monthsOffset == 0)
	{
		monthsOffset = 12;
		workHistory->currentWorkMonth.year--;
	}
	workHistory->currentWorkMonth.month = monthsOffset;


}
void WorkHistory_NextMonth(tWorkHistory *workHistory)
{
	uint32 itemPtr;
	sint16 monthsOffset = (workHistory->currentWorkMonth.month + 1) % 13;
	if(monthsOffset == 0)
	{
		monthsOffset = 1;
		workHistory->currentWorkMonth.year++;
	}
	workHistory->currentWorkMonth.month = monthsOffset;


}

uint8 WorkHistory_AddItem(tWorkHistory *workHistory, tDayWorkTime item)
{
	uint8 retVal;

	if(workHistory->numOfDataItems+1 < HISTORY_LENGTH)
	{
		workHistory->data[workHistory->numOfDataItems] = item;

		workHistory->numOfDataItems = workHistory->numOfDataItems + 1;

		retVal = 0;
	}
	else
	{
		retVal = 1;
	}

	return retVal;
}

uint32 WorkHistory_GetNumOfItems(tWorkHistory *workHistory)
{
	return workHistory->numOfDataItems;
}

uint32 WorkHistory_GetMonthItems(tWorkHistory *workHistory, uint32* firstItemIndex)
{
	uint32 numOfItems=0;
	uint32 i;
	tYearMonth targetMonthYear = workHistory->currentWorkMonth;


	*firstItemIndex = 0;
	tYearMonth currItemMonth;


	for(i=0; i<workHistory->numOfDataItems; i++)
	{
		currItemMonth = Time2YearMonth(workHistory->data[i].startWork);

		if(0 == numOfItems)
		{
			if(currItemMonth.month == targetMonthYear.month && currItemMonth.year == targetMonthYear.year)
			{
				*firstItemIndex = i;
				numOfItems=1;
			}
		}
		else
		{
			if(currItemMonth.month == targetMonthYear.month && currItemMonth.year == targetMonthYear.year)
			{
				numOfItems++;
			}
			else
			{
				break;
			}
		}
	}

	return numOfItems;

}

tDayWorkTime WorkHistory_GetItem(tWorkHistory *workHistory, uint32 itemIndex)
{
	tDayWorkTime retVal;

	if(itemIndex < workHistory->numOfDataItems)
	{
		retVal = workHistory->data[itemIndex];
	}

	return retVal;
}

#define FILE_NAME_HISTORY "CzasPracyHistoria.csv"
uint8 WorkHistory_SaveToFile(tWorkHistory *workHistory)
{

	return 0;
}
uint8 WorkHistory_ReadFromFile(tWorkHistory *workHistory)
{
	FILE* filePtr = fopen(FILE_NAME_HISTORY, "r");
	if (filePtr == NULL) {
		//printf("Brak pliku!");
		return 1;
	}
	else
	{
		//printf("Otwarto plik");
	}

	tDayWorkTime workDay;

	while (fscanf(filePtr, "%lu;%lu;%lu\r", &(workDay.startWork), &(workDay.endWork), &(workDay.workDuration)) == 3)
	{
		//printf("Dodano element!");
		WorkHistory_AddItem(workHistory, workDay);
	}


	return 0;
}
