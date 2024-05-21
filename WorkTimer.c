#include "WorkTimer.h"

boolean WorkTimer_IsInitialized(tWorkTimer *timer)
{
	boolean retVal;
	if((WORKTIMER_STATE_WORK==timer->state) || (WORKTIMER_STATE_PAUSE==timer->state))
	{
		retVal = TRUE;
	}
	else
	{
		retVal = FALSE;
	}

	return retVal;
}


void WorkTimer_Init(tWorkTimer *timer)
{
	timer->state = WORKTIMER_STATE_INIT;
	timer->totalWorkStartTime = 0U;
	timer->lastWorkStartTime = 0U;
	timer->workTimeSum = 0U;
}

tWorkTimerState WorkTimer_GetWorkTimerState(tWorkTimer *timer)
{
	return timer->state;
}

void WorkTimer_StartStop(tWorkTimer *timer)
{
	if(WORKTIMER_STATE_INIT == timer->state)
	{
		timer->totalWorkStartTime = time(NULL);
		timer->lastWorkStartTime = timer->totalWorkStartTime;
		timer->state = WORKTIMER_STATE_WORK;
	}
	else if(WORKTIMER_STATE_WORK ==  timer->state)
	{
		timer->workTimeSum = WorkTimer_GetWorkTime(timer);

		timer->state = WORKTIMER_STATE_PAUSE;
	}
	else if(WORKTIMER_STATE_PAUSE ==  timer->state)
	{
		timer->lastWorkStartTime = time(NULL);

		timer->state = WORKTIMER_STATE_WORK;

	}
}

time_t WorkTimer_GetTotalTime(tWorkTimer *timer)
{
	time_t totalTime;

	if(WorkTimer_IsInitialized(timer))
	{
		totalTime = (time(NULL)-timer->totalWorkStartTime);
	}
	else
	{
		totalTime = 0;
	}

	return totalTime;
}

time_t WorkTimer_GetWorkTime(tWorkTimer *timer)
{
	time_t workTime;

	if(WORKTIMER_STATE_WORK==timer->state)
	{
		workTime = timer->workTimeSum + (time(NULL) - timer->lastWorkStartTime);
	}
	else if(WORKTIMER_STATE_PAUSE==timer->state)
	{
		workTime = timer->workTimeSum;
	}
	else
	{
		workTime =0;
	}

	return workTime;
}


time_t WorkTimer_GetPauseTime(tWorkTimer *timer)
{
	time_t pauseTime;

	pauseTime = WorkTimer_GetTotalTime(timer) - WorkTimer_GetWorkTime(timer);

	return pauseTime;
}
