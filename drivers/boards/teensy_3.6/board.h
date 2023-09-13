/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "pin_mux.h"
#include "peripherals.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief The board name */
#define BOARD_NAME "TEENSY36"

/* Board led color mapping */
#define LOGIC_LED_ON 1U
#define LOGIC_LED_OFF 0U
#ifndef BOARD_LED_GPIO
#define BOARD_LED_GPIO GPIOC
#endif
#define BOARD_LED_GPIO_PORT PORTC
#ifndef BOARD_LED_GPIO_PIN
#define BOARD_LED_GPIO_PIN 5U
#endif

#define LED_INIT(output)  \
    GPIO_PortInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, {kGPIO_DigitalOutput, 1}) /*!< Turn on target LED_RED */
#define BOARD_LED_ON() \
    GPIO_PinWrite((BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, 1) /*!< Turn on target LED_RED */
#define BOARD_LED_OFF() \
    GPIO_PinWrite((BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, 0) /*!< Turn off target LED_RED */
#define BOARD_LED_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_GPIO, 0x01 << BOARD_LED_GPIO_PIN) /*!< Toggle on target LED_RED */

/* DAC base address */
#define BOARD_DAC_BASEADDR DAC0

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_Init(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
