/*
 * light_traffic.c
 *
 *  Created on: Oct 30, 2025
 *      Author: ADMIN
 */
#include"light_trafic.h"
/*
 * fsm_automatic.c
 *
 *  Created on: Sep 12, 2025
 *      Author: ADMIN
 */


#include "light_trafic.h"
#include "mode_normal.h"

const uint8_t segCode[10] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
};



// --- Các hàm điều khiển LED Giao thông ---
void led_off() {
    GPIOA->BRR = LED_ALL;
}

void NS_green_WE_red() {
    GPIOA->BSRR  = LED_NS_GREEN | LED_WE_RED;
    GPIOA->BRR = LED_NS_YELLOW | LED_NS_RED | LED_WE_GREEN | LED_WE_YELLOW;
}

void NS_yellow_WE_red() {
    GPIOA->BSRR  = LED_NS_YELLOW | LED_WE_RED;
    GPIOA->BRR = LED_NS_GREEN | LED_NS_RED | LED_WE_GREEN | LED_WE_YELLOW;
}

void NS_red_WE_green() {
    GPIOA->BSRR  = LED_NS_RED | LED_WE_GREEN;
    GPIOA->BRR = LED_NS_GREEN | LED_NS_YELLOW | LED_WE_YELLOW | LED_WE_RED;
}

void NS_red_WE_yellow() {
    GPIOA->BSRR  = LED_NS_RED | LED_WE_YELLOW;
    GPIOA->BRR = LED_NS_GREEN | LED_NS_YELLOW | LED_WE_GREEN | LED_WE_RED;
}

// --- Các hàm điều khiển 74HC595 ---
void shiftByte(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        if (data & 0x80) {
            HAL_GPIO_WritePin(HC595_SDI_PORT, HC595_SDI_PIN, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(HC595_SDI_PORT, HC595_SDI_PIN, GPIO_PIN_RESET);
        }
        data <<= 1;
        HAL_GPIO_WritePin(HC595_SCLK_PORT, HC595_SCLK_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC595_SCLK_PORT, HC595_SCLK_PIN, GPIO_PIN_SET);
    }
}

void update4Digits(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4) {
    HAL_GPIO_WritePin(HC595_LOAD_PORT, HC595_LOAD_PIN, GPIO_PIN_RESET);

    shiftByte(segCode[d4]); // LED 4 (U5 - đơn vị WE)
    shiftByte(segCode[d3]); // LED 3 (U4 - chục WE)
    shiftByte(segCode[d2]); // LED 2 (U3 - đơn vị NS)
    shiftByte(segCode[d1]); // LED 1 (U2 - chục NS)

    HAL_GPIO_WritePin(HC595_LOAD_PORT, HC595_LOAD_PIN, GPIO_PIN_SET);
}
