/***************************************************************************//**
 * @file serial_api.c
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#include "device.h"
#if DEVICE_SERIAL

#include "mbed_assert.h"
#include "serial_api.h"
#include "serial_api_HAL.h"
#include <string.h>
#include <stdbool.h>

#include "pinmap.h"
#include "pinmap_function.h"
#include "PeripheralPins.h"
#include "PeripheralNames.h"

#include "buffer.h"

/* Serial interface on USBTX/USBRX retargets stdio */
int stdio_uart_inited = 0;
serial_t stdio_uart;

void serial_init(serial_t *obj, PinName tx, PinName rx)
{

}

void serial_free(serial_t *obj)
{

}


/**
 * Set UART baud rate
 */
void serial_baud(serial_t *obj, int baudrate)
{
    
}


/**
 * Set UART format by re-initializing the peripheral.
 */
void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits)
{

}

/******************************************************************************
 *                               INTERRUPTS                                   *
 ******************************************************************************/
uint8_t serial_tx_ready(serial_t *obj)
{
	return true;
}

uint8_t serial_rx_ready(serial_t *obj)
{
    return false;
}



/**
 * Set handler for all serial interrupts (is probably SerialBase::_handler())
 * and store IRQ ID to be returned to the handler upon interrupt. ID is
 * probably a pointer to the calling Serial object.
 */
void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id)
{
}

/**
 * Set ISR for a given UART and interrupt event (TX or RX)
 */
void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable)
{

}

/******************************************************************************
 *                               READ/WRITE                                   *
 ******************************************************************************/

/**
 *  Get one char from serial link
 */
int serial_getc(serial_t *obj)
{
	while(1) { }
}

#ifndef MAX_PUTC_BUFFER
#define MAX_PUTC_BUFFER 128
#endif

static uint8_t _putc_buffer[MAX_PUTC_BUFFER];
static int _putc_buffer_pos = 0;

static void _putc_flush_buffer() {
	_putc_buffer[_putc_buffer_pos] = '\0';
	asm(
            "mov r0, #4\n"
            "mov r1, %[ptr]\n"
            "bkpt #0xAB\n"
            :
            : [ptr] "r" (&_putc_buffer)
            : "r0", "r1"
    );
	_putc_buffer_pos = 0;
}

/*
 * Send one char over serial link
 */
void serial_putc(serial_t *obj, int c)
{
	if (_putc_buffer_pos >= (MAX_PUTC_BUFFER - 2)) {
		_putc_flush_buffer();
	}

	_putc_buffer[_putc_buffer_pos++] = (uint8_t) c;

	if (c == '\n') {
		_putc_flush_buffer();
	}
}

/**
 * Check if data is available in RX data vector
 */
int serial_readable(serial_t *obj)
{
	return false;
}

/**
 * Check if TX buffer is empty
 */
int serial_writable(serial_t *obj)
{
	return true;
}

/**
 * Clear UART interrupts
 */
void serial_clear(serial_t *obj)
{
    /* Interrupts automatically clear when condition is not met anymore */
}

void serial_break_set(serial_t *obj)
{
	// ... TODO FIXME?
}

void serial_break_clear(serial_t *obj)
{
    /* No need to clear break, it is automatically cleared after one frame.
     * From the reference manual:
     *
     * By setting TXBREAK, the output will be held low during the stop-bit
     * period to generate a framing error. A receiver that supports break
     * detection detects this state, allowing it to be used e.g. for framing
     * of larger data packets. The line is driven high before the next frame
     * is transmitted so the next start condition can be identified correctly
     * by the recipient. Continuous breaks lasting longer than a USART frame
     * are thus not supported by the USART. GPIO can be used for this.
     */
}

void serial_pinout_tx(PinName tx)
{
}




#endif //DEVICE_SERIAL
