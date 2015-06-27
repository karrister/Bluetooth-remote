/* 
 * File:   main.c
 * Author: karrister
 *
 * Created on 24. June 2015, 2:30
 */

#include <stdio.h>
#include <stdlib.h>

#include "pic18f14k50.h"

#include "pic_config_bits.h"

#define PIN_DIRECTION_OUTPUT  (0)
#define PIN_DIRECTION_INPUT   (1)

struct device_status_t
{
    unsigned char reserved              :7;
    unsigned char is_bt_device_connected:1;
} device_status;

void init(void)
{

    /* Set default pinmuxes and other per-pin config */

    /* Output pins */
    //5(RC5) - nikon shutter focus (output, hi = focus camera)
    TRISCbits_t.TRISC5 = PIN_DIRECTION_OUTPUT;
    //6(RC4) - nikon shutter release (output, hi = release shutter)
    TRISCbits_t.TRISC4 = PIN_DIRECTION_OUTPUT;
    //7(RC3) - led2 (output, active hi)
    TRISCbits_t.TRISC3 = PIN_DIRECTION_OUTPUT;
    //13(RB4) - led1 (output, active hi)
    TRISBbits_t.TRISB4 = PIN_DIRECTION_INPUT;
    //8(RC6) - reset (output, active hi?)
    TRISCbits_t.TRISC6 = PIN_DIRECTION_OUTPUT;

    /* Input pins */
    //9(RC7) - bt status (input)
    TRISCbits_t.TRISC7 = PIN_DIRECTION_INPUT;
    //11(RB6) - sw3 (input. switch open = hi, switch closed = lo)
    TRISBbits_t.TRISB6 = PIN_DIRECTION_INPUT;
    //14(RC2) - mode sw (input. switch open = hi, switch closed = lo)
    TRISCbits_t.TRISC2 = PIN_DIRECTION_INPUT;
    //15(RC1) - sw2 (input. switch open = hi, switch closed = lo)
    TRISCbits_t.TRISC1 = PIN_DIRECTION_INPUT;
    //16(RC0) - sw1 (input. switch open = hi, switch closed = lo)
    TRISCbits_t.TRISC0 = PIN_DIRECTION_INPUT;

    /* General pins */
    //10(RB7) - uart tx
    TRISBbits_t.TRISB7 = PIN_DIRECTION_OUTPUT;
    //12(RB5) - uart rx
    TRISBbits_t.TRISB5 = PIN_DIRECTION_INPUT;

}

void query_bt_connection_status(void)
{
    //TODO handle BT

#if 1 //For now, set status so that the BT device is not connected
    device_status.is_bt_device_connected = 0;
#endif
}

void get_config_from_bt(void)
{
    //TODO implement
}

void set_default_config(void)
{
    //TODO implement
}

int main(void)
{
    init();

    //query_bt_connection_status();

    if(device_status.is_bt_device_connected)
    {
        get_config_from_bt();
    }
    else
    {
        set_default_config();
    }

    return 0;
}

