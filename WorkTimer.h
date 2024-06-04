/*
 * WorkTimer.h
 *
 *  Created on: 12 maj 2024
 *      Author: nzyj2j
 */

#ifndef WORKTIMER_H_
#define WORKTIMER_H_

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "ApplTypes.h"

typedef enum
{
	WORKTIMER_STATE_INIT=0,
	WORKTIMER_STATE_WORK,
	WORKTIMER_STATE_PAUSE,
	WORKTIMER_STATE_END
}tWorkTimerState;

typedef struct
{
	time_t totalWorkStartTime;
	tWorkTimerState state;
	time_t lastWorkStartTime;
	time_t workTimeSum;
} tWorkTimer;


void WorkTimer_Init(tWorkTimer *timer);
boolean WorkTimer_IsInitialized(tWorkTimer *timer);
void WorkTimer_StartStop(tWorkTimer *timer);
uint8 WorkTimer_End(tWorkTimer *timer);
tWorkTimerState WorkTimer_GetWorkTimerState(tWorkTimer *timer);
time_t WorkTimer_GetWorkTime(tWorkTimer *timer);
time_t WorkTimer_GetPauseTime(tWorkTimer *timer);
time_t WorkTimer_GetTotalTime(tWorkTimer *timer);
tDayWorkTime WorkTimer_GetWorkDayData(tWorkTimer *timer);

#endif /* WORKTIMER_H_ */
