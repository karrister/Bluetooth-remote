/* 
 * File:   project_includes.h
 * Author: karrister
 *
 * Created on 24. June 2015, 2:32
 */

#ifndef PROJECT_INCLUDES_H
#define	PROJECT_INCLUDES_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "pic18f14k50.h"
#include "pic_config_bits.h"

/* Defines */
#define NO_GPIO_CONFIG_THROUGH_BT
#define ONLY_PASSIVE_CONNECTION_STATUS_QUERY

#define UART_BUFFER_SIZE                    (16)

#define PIN_DIRECTION_OUTPUT                (0)
#define PIN_DIRECTION_INPUT                 (1)

//States
#define STATE_IDLE                          (1)
#define STATE_BUTTON_PRESSED                (2)
#define STATE_REMOTE_CMD_RECEIVED           (3)

/* Macros */
#define UART_SEND_BYTE(byte)    (TXREG = byte)
#define UART_RECV_BYTE()        (RCREG)





/* Typedefs */
typedef unsigned char BYTE;


/* PIC Pinout:
 * 1 - vdd
 * 2 - xtal
 * 3 - xtal
 * 4 - icsp/low batt indicator (input, hi = good, lo = low batt)
 * 5 - nikon shutter focus (output, hi = focus camera)
 * 6 - nikon shutter release (output, hi = release shutter)
 * 7 - led2 (output, active hi)
 * 8 - reset (output, active hi?)
 * 9 - bt status (input)
 * 10 - uart tx
 * 11 - sw3 (input. switch open = hi, switch closed = lo)
 * 12 - uart rx
 * 13 - led1 (output, active hi)
 * 14 - mode sw (input. switch open = hi, switch closed = lo)
 * 15 - sw2 (input. switch open = hi, switch closed = lo)
 * 16 - sw1 (input. switch open = hi, switch closed = lo)
 * 17 - nc
 * 18 - icsp
 * 19 - icsp
 * 20 - gnd
 */




#ifdef	__cplusplus
}
#endif

#endif	/* PROJECT_INCLUDES_H */

