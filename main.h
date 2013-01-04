/*
 * File: main.h
 * Date: 02.01.2013
 * Denis Zheleznyakov aka ZiB @ http://ziblog.ru
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stm8s.h"

#include "macros.h"
#include "program.h"
#include "task_manager.h"

#include "mcu_gpio.h"

#define PIN_LED_GREEN	D, 0, LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ

#define PIN_BAM_0		B, 3,  LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ
#define PIN_BAM_1		B, 5,  LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ
#define PIN_BAM_2		B, 7,  LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ
#define PIN_BAM_3		B, 6,  LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ
#define PIN_BAM_4		B, 4,  LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ
#define PIN_BAM_5		B, 2,  LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ
#define PIN_BAM_6		C, 6,  LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ
#define PIN_BAM_7		C, 4,  LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ
#define PIN_BAM_8		C, 2,  LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ
#define PIN_BAM_9		C, 3,  LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ
#define PIN_BAM_10		C, 5,  LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ
#define PIN_BAM_11		C, 7,  LOW, OUTPUT_PUSH_PULL_SPEED_LIMIT_10MHZ

#endif /* MAIN_H_ */
