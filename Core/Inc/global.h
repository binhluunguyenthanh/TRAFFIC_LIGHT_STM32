/*
 * global.h
 *
 *  Created on: Oct 29, 2025
 *      Author: ADMIN
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "button.h"
#include "software_timer.h"
#include "light_trafic.h"
#include "mode_normal.h"
#include "mode_manual.h"
#include "mode_manage.h"
#include "schedular.h"

//----- Định nghĩa trạng thái đèn giao thông----//
#define INIT_LIGHT       1
#define NS_RED_WE_GREEN  2
#define NS_RED_WE_YELLOW 3
#define NS_GREEN_WE_RED  4
#define NS_YELLOW_WE_RED 5

// ---- Định nghĩa Timer----//
#define TIMER_BLINKY       0
#define TIMER_FSM_1        1
#define TIMER_FSM_2        2
#define TIMER_COUNTDOWN_NS 3
#define TIMER_COUNTDOWN_WE 4
#define TIMER_MODIFY_LIGHT 5
#define TIMER_FSM_NORMAL   6

// --- 2 Mode chính --- //
#define MODE_NORMAL 1
#define MODE_MODIFY 2
#define MODE_MANUAL 3
// ---- Khai báo biến toàn cục-----//
// Normal_mode
extern int status_1;
extern int fsm_normal_status;
extern int fsm_manual_status;
extern int g_timer_countdown_NS;
extern int g_timer_countdown_WE;
// Modify_mode
extern int g_timeRed_setting;
extern int g_timeAmber_setting;
extern int g_timeGreen_setting;
extern int g_temp_value;
extern int fsm_modify_light_status;
// Manager_mode
extern int g_current_mode;
extern int led_cycle_index;

void LEDBlinky();
void Ledblinky();
#endif /* INC_GLOBAL_H_ */
