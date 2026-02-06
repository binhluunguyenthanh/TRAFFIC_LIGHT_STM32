/*
 * software_timer.c
 *
 *  Created on: Oct 26, 2025
 *      Author: ADMIN
 */
#include <software_timer.h>

SoftwareTimer timerPool[MAX_COUNTER];

void Timer_init() {
    for (int i = 0; i < MAX_COUNTER; i++) {
        timerPool[i].flag = 0;
    }
}
int IsTimerExpired(int index){
	if(timerPool[index].flag){
		timerPool[index].flag = 0;
		return 1;
	}
	return 0;
}
void Settimer(int index, int duration) {
    if (index >= MAX_COUNTER) return;
    timerPool[index].count = duration / TIMER_TICK;
    timerPool[index].flag = 0;
}

void Timer_run() {
    for (int i = 0; i < MAX_COUNTER; i++) {
        if(timerPool[i].count > 0){
        	timerPool[i].count--;
            if (timerPool[i].count <= 0) {
                timerPool[i].flag = 1;
            }
        }
    }
}
