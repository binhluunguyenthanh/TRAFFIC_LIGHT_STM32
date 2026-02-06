/*
 * software_timer.h
 *
 *  Created on: Oct 26, 2025
 *      Author: ADMIN
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_


#define TIMER_TICK 10
#define MAX_COUNTER 10

typedef struct {
    int count;
    int flag;
} SoftwareTimer;

extern SoftwareTimer timerPool[MAX_COUNTER];

void Timer_init();
void Settimer(int index, int duration);
void Timer_run();
int IsTimerExpired(int index);
#endif /* INC_SOFTWARE_TIMER_H_ */
