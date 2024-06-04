/*
 * UserInterface.h
 *
 *  Created on: 12 maj 2024
 *      Author: nzyj2j
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "WorkHistory.h"

void UserInterface_Init();
void UserInterface_Finish();

void UserInterface_Refresh();
char UserInterface_GetKeyCmd();
void UserInterface_RefreshHistory(tWorkHistory* workHistory);


#endif /* USERINTERFACE_H_ */
