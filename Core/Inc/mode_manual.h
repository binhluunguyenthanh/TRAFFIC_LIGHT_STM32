/*
 * mode_2.h
 *
 *  Created on: Oct 31, 2025
 *      Author: ADMIN
 */

#ifndef INC_MODE_2_H_
#define INC_MODE_2_H_

#include "global.h"

#define INIT_MODIFY 0
#define MODIFY_RED 1
#define MODIFY_YELLOW 2
#define MODIFY_GREEN 3

extern int g_temp_value;

void FSM_Mode_Manual_run();
#endif /* INC_MODE_2_H_ */
