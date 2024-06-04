/*
 * WorkHistory.h
 *
 *  Created on: 4 cze 2024
 *      Author: nzyj2j
 */

#ifndef WORKHISTORY_H_
#define WORKHISTORY_H_

#include "ApplTypes.h"
#include "Platform_Types.h"

#define HISTORY_LENGTH 100000


typedef struct
{
	tDayWorkTime data[HISTORY_LENGTH];
	uint32 numOfDataItems;
	tYearMonth currentWorkMonth;
} tWorkHistory;




void WorkHistory_Init(tWorkHistory *workHistory);

uint8 WorkHistory_AddItem(tWorkHistory *workHistory, tDayWorkTime item);
uint32 WorkHistory_GetNumOfItems(tWorkHistory *workHistory);
uint32 WorkHistory_GetMonthItems(tWorkHistory *workHistory, uint32* firstItemIndex);
tDayWorkTime WorkHistory_GetItem(tWorkHistory *workHistory, uint32 itemIndex);
void WorkHistory_PrevMonth(tWorkHistory *workHistory);
void WorkHistory_NextMonth(tWorkHistory *workHistory);
uint8 WorkHistory_SaveToFile(tWorkHistory *workHistory);
uint8 WorkHistory_ReadFromFile(tWorkHistory *workHistory);


#endif /* WORKHISTORY_H_ */
