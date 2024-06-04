/*
 * ApplTypes.h
 *
 *  Created on: 21 maj 2024
 *      Author: nzyj2j
 */

#ifndef APPLTYPES_H_
#define APPLTYPES_H_

#include <time.h>
#include "Platform_Types.h"

typedef struct
{
	time_t startWork;
	time_t endWork;
	time_t workDuration;

} tDayWorkTime;


typedef struct
{
	uint8 month;
	uint16 year;
} tYearMonth;





#endif /* APPLTYPES_H_ */
