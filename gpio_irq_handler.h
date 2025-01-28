#ifndef GPIO_IRQ_HANDLER_H
#define GPIO_IRQ_HANDLER_H

#include "pico/stdlib.h"

// Declaração da função para lidar com interrupções nos pinos GPIO
void gpio_irq_handler(uint gpio, uint32_t events);

#endif // GPIO_IRQ_HANDLER_H
