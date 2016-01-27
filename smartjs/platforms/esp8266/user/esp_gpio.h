/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef ESP_GPIO_INCLUDED
#define ESP_GPIO_INCLUDED

#include <stdint.h>

#include "smartjs/src/sj_gpio.h"

#ifdef RTOS_SDK
void gpio_output_conf(uint32_t set_mask, uint32_t clear_mask,
                      uint32_t enable_mask, uint32_t disable_mask);
uint32_t gpio_input_get();
void gpio_output_set(uint32_t set_mask, uint32_t clear_mask,
                     uint32_t enable_mask, uint32_t disable_mask);
#define GPIO_PIN_ADDR(i) (GPIO_PIN0_ADDRESS + i * 4)
#endif /* RTOS_SDK */

#ifndef RTOS_SDK
#define ENTER_CRITICAL(type) ETS_INTR_DISABLE(type)
#define EXIT_CRITICAL(type) ETS_INTR_ENABLE(type)
#else
#define ENTER_CRITICAL(dummy) portENTER_CRITICAL()
#define EXIT_CRITICAL(dummy) portEXIT_CRITICAL()
#endif

int sj_gpio_set_mode(int pin, enum gpio_mode mode, enum gpio_pull_type pull);
int sj_gpio_write(int pin, enum gpio_level level);

#endif
