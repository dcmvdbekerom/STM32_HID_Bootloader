/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2015 Chuck McManis <cmcmanis@mcmanis.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdlib.h> //atoi()
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include "stm32-stdio.h"

//#include <libopencm3/cm3/scb.h>
//#define APP_BASE 0x08004000

static void clock_setup(void)
{
    /* Set PLL and HSE to 168 MHz */
    rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
	
    /* Enable GPIOD clock for LED & USARTs. */
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);

	/* Enable clocks for USART2. */
	rcc_periph_clock_enable(RCC_USART2);
}

static void usart_setup(void)
{
	/* Setup USART2 parameters. */
	usart_set_baudrate(USART2, 115200);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX_RX);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART2);
}

static void gpio_setup(void)
{
	/* Setup GPIO pin GPIO2 on GPIO port B for LED. */
	gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO2);

	/* Setup GPIO pins for USART2 transmit and receive. */
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);

	/* Setup USART2 TX pin as alternate function. */
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3);
}


int main(void)
{
    //SCB_VTOR = APP_BASE;
	int i, j;

	clock_setup();
	gpio_setup();
	usart_setup();
	printf("\nStandard I/O Example.\n");

	/* Blink the LED (PB2) on the board with every transmitted byte. */
	while (1) {
		int delay = 0;
		char local_buf[32];

		gpio_toggle(GPIOB, GPIO2);	/* LED on/off */
		do {
			printf("Enter the delay constant for blink : ");
			fflush(stdout);
            // Waiting for input here
			fgets(local_buf, 32, stdin);
			delay = atoi(local_buf);
			if (delay <= 0) {
				printf("Error: expected a delay > 0\n");
			}
		} while (delay <= 0);

		printf("Blinking with a delay of %d\n", delay);
		for (j = 0; j < 1000; j++) {
            printf("Iteration %d\n",j);
			gpio_toggle(GPIOB, GPIO2);
			for (i = 0; i < delay; i++) {	/* Wait a bit. */
				__asm__("NOP");
			}
		}
	}
	return 0;
}





