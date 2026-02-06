/*
 * light_trafic.h
 *
 *  Created on: Oct 30, 2025
 *      Author: ADMIN
 */

#ifndef INC_LIGHT_TRAFIC_H_
#define INC_LIGHT_TRAFIC_H_

#include "main.h" // Chỉ include main.h
#include "stdint.h" // Include để biết kiểu uint8_t

// --- Định nghĩa mask LED Giao thông ---
#define LED_NS_GREEN     (LED_GREEN_N_Pin | LED_GREEN_S_Pin)
#define LED_NS_YELLOW    (LED_YELLOW_N_Pin | LED_YELLOW_S_Pin)
#define LED_NS_RED       (LED_RED_N_Pin    | LED_RED_S_Pin)
#define LED_WE_GREEN     (LED_GREEN_W_Pin | LED_GREEN_E_Pin)
#define LED_WE_YELLOW    (LED_YELLOW_W_Pin | LED_YELLOW_E_Pin)
#define LED_WE_RED       (LED_RED_W_Pin    | LED_RED_E_Pin)
#define LED_ALL (LED_NS_GREEN | LED_NS_YELLOW | LED_NS_RED | \
                 LED_WE_GREEN | LED_WE_YELLOW | LED_WE_RED)

// --- Định nghĩa các chân điều khiển 74HC595 ---
#define HC595_SDI_PORT   GPIOB
#define HC595_SDI_PIN    GPIO_PIN_15
#define HC595_SCLK_PORT  GPIOB
#define HC595_SCLK_PIN   GPIO_PIN_1
#define HC595_LOAD_PORT  GPIOB
#define HC595_LOAD_PIN   GPIO_PIN_2

extern const uint8_t segCode[10];

void led_off();
void NS_red_WE_green();
void NS_red_WE_yellow();
void NS_green_WE_red();
void NS_yellow_WE_red();
void shiftByte(uint8_t data);
void update4Digits(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4);


#endif /* INC_LIGHT_TRAFIC_H_ */
