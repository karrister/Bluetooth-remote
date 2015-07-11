/* 
 * File:   main.c
 * Author: karrister
 *
 * Created on 24. June 2015, 2:30
 */

#include <stdio.h>
#include <stdlib.h>

#include "project_includes.h"

union device_buttons_state_t
{
    struct
    {
        unsigned char reserved:5;
        unsigned char button3:1;
        unsigned char button2:1;
        unsigned char button1:1;
    };

    unsigned char button_bits;
} device_buttons_state;

union device_error_register_t
{
    struct
    {
        unsigned char reserved:7;
        unsigned char no_connection_to_bt_chip:1;
    };

    unsigned char error_bits;
} device_error_register;

union device_status_t
{
    struct
    {
        unsigned char reserved              :7;
        unsigned char is_bt_device_connected:1;
    };

    unsigned char status_bits;
} device_status;

unsigned char main_state;

void init(void)
{
    /* Init internal status structs */
    device_error_register.error_bits = 0;
    device_status.status_bits = 0;
    main_state = STATE_IDLE;

    /* Set default pinmuxes and other per-pin config */

    /* Output pins */
    //5(RC5) - nikon shutter focus (output, hi = focus camera)
    TRISCbits.TRISC5 = PIN_DIRECTION_OUTPUT;
    //6(RC4) - nikon shutter release (output, hi = release shutter)
    TRISCbits.TRISC4 = PIN_DIRECTION_OUTPUT;
    //7(RC3) - led2 (output, active hi)
    TRISCbits.TRISC3 = PIN_DIRECTION_OUTPUT;
    //13(RB4) - led1 (output, active hi)
    TRISBbits.TRISB4 = PIN_DIRECTION_INPUT;
    //8(RC6) - reset (output, active hi?)
    TRISCbits.TRISC6 = PIN_DIRECTION_OUTPUT;

    /* Input pins */
    //9(RC7) - bt status (input)
    TRISCbits.TRISC7 = PIN_DIRECTION_INPUT;
    //11(RB6) - sw3 (input. switch open = hi, switch closed = lo)
    TRISBbits.TRISB6 = PIN_DIRECTION_INPUT;
    //14(RC2) - mode sw (input. switch open = hi, switch closed = lo)
    TRISCbits.TRISC2 = PIN_DIRECTION_INPUT;
    //15(RC1) - sw2 (input. switch open = hi, switch closed = lo)
    TRISCbits.TRISC1 = PIN_DIRECTION_INPUT;
    //16(RC0) - sw1 (input. switch open = hi, switch closed = lo)
    TRISCbits.TRISC0 = PIN_DIRECTION_INPUT;

    /* General pins */
    //10(RB7) - uart tx
    TRISBbits.TRISB7 = PIN_DIRECTION_OUTPUT;
    //12(RB5) - uart rx
    TRISBbits.TRISB5 = PIN_DIRECTION_INPUT;

}

void poll_buttons(void)
{
    if(1)//TODO: replace with poll of GPIO
    {
        device_buttons_state.button1 = 1;
    }

    if(1)//TODO: replace with poll of GPIO
    {
        device_buttons_state.button2 = 1;
    }

    if(1)//TODO: replace with poll of GPIO
    {
        device_buttons_state.button3 = 1;
    }
}

void set_bt_dev_config(void)
{
    //Set BT baud rate to 9600
    //AT+BAUD4
    UART_SEND_BYTE('A'); //A
    UART_SEND_BYTE('T'); //T
    UART_SEND_BYTE('+');
    UART_SEND_BYTE('B');
    UART_SEND_BYTE('A');
    UART_SEND_BYTE('U');
    UART_SEND_BYTE('D');
    UART_SEND_BYTE('4');

    //Set BT chip name
    //AT+NAMEkarriremote
    UART_SEND_BYTE('A'); //A
    UART_SEND_BYTE('T'); //T
    UART_SEND_BYTE('+');
    UART_SEND_BYTE('N');
    UART_SEND_BYTE('A');
    UART_SEND_BYTE('M');
    UART_SEND_BYTE('E');
    UART_SEND_BYTE('k');
    UART_SEND_BYTE('a');
    UART_SEND_BYTE('r');
    UART_SEND_BYTE('r');
    UART_SEND_BYTE('i');
    UART_SEND_BYTE('r');
    UART_SEND_BYTE('e');
    UART_SEND_BYTE('m');
    UART_SEND_BYTE('o');
    UART_SEND_BYTE('t');
    UART_SEND_BYTE('e');

    //Set PIN password
    //AT+PIN1234
    UART_SEND_BYTE('A'); //A
    UART_SEND_BYTE('T'); //T
    UART_SEND_BYTE('+');
    UART_SEND_BYTE('P');
    UART_SEND_BYTE('I');
    UART_SEND_BYTE('N');
    UART_SEND_BYTE('1');
    UART_SEND_BYTE('2');
    UART_SEND_BYTE('3');
    UART_SEND_BYTE('4');
}

void query_bt_connection_status(void)
{
    BYTE status_readback[2];
    //For now, set status so that the BT device is not connected
    device_status.is_bt_device_connected = 0;

    //Send AT in hexa to inquire status
    UART_SEND_BYTE('A'); //A
    UART_SEND_BYTE('T'); //T

    status_readback[0] = UART_RECV_BYTE();
    status_readback[1] = UART_RECV_BYTE();

    //Expecting to read back OK from uart
    if((status_readback[0] != 'O') || (status_readback[1] != 'K'))
    {
        device_error_register.no_connection_to_bt_chip = 1;
        return;
    }

#ifndef ONLY_PASSIVE_CONNECTION_STATUS_QUERY
    //TODO: implement here an active connection query - query the host application
    //      on the paired BT device.
#else
    device_status.is_bt_device_connected = 1;
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

    /* Configure the Bluetooth chip */
    set_bt_dev_config();

    query_bt_connection_status();

#ifndef NO_GPIO_CONFIG_THROUGH_BT
    if(device_status.is_bt_device_connected)
    {
        get_config_from_bt();
    }
    else
#endif //NO_GPIO_CONFIG_THROUGH_BT
    {
        set_default_config();
    }

    {
    BYTE uart_buff[UART_BUFFER_SIZE];

    while(1)
    {

        switch(main_state)
        {
            case STATE_IDLE:
                //Poll all buttons
                poll_buttons();

                //if preseed, set state and break
                if(device_buttons_state.button_bits)
                {
                    main_state = STATE_BUTTON_PRESSED;
                    break;
                }

                //Attempt to receive UART cmd
                uart_buff[0] = UART_RECV_BYTE();
                uart_buff[1] = UART_RECV_BYTE();
                uart_buff[2] = UART_RECV_BYTE();

                if((uart_buff[0] == 'C') && (uart_buff[1] == 'M') && (uart_buff[2] == 'D'))
                {
                    main_state = STATE_REMOTE_CMD_RECEIVED;
                    //break at the end of case
                }

                break;
            case STATE_BUTTON_PRESSED:

                while(device_buttons_state.button_bits)
                {
                    unsigned char switch_id_char;

                    //Get the next switch ID to transmit
                    if(device_buttons_state.button1)
                    {
                        switch_id_char = '1';
                        device_buttons_state.button1 = 0;
                    }
                    else if(device_buttons_state.button2)
                    {
                        switch_id_char = '2';
                        device_buttons_state.button2 = 0;
                    }
                    else if(device_buttons_state.button3)
                    {
                        switch_id_char = '3';
                        device_buttons_state.button3 = 0;
                    }

                    //Command
                    UART_SEND_BYTE('C');
                    UART_SEND_BYTE('M');
                    UART_SEND_BYTE('D');

                    //Switch toggled
                    UART_SEND_BYTE('S');
                    UART_SEND_BYTE('W');
                    UART_SEND_BYTE('T');

                    //Switch ID
                    UART_SEND_BYTE('S');
                    UART_SEND_BYTE(switch_id_char);
                }

                break;
            case STATE_REMOTE_CMD_RECEIVED:
            default:
                //unexpected state - set WD and reset
                //Debug msg
                UART_SEND_BYTE('D');
                UART_SEND_BYTE('B');
                UART_SEND_BYTE('G');
                //Message
                UART_SEND_BYTE('E');
                UART_SEND_BYTE('R');
                UART_SEND_BYTE('R');
                break;
        }
    } //WHILE(1)

    }

    //Debug msg
    UART_SEND_BYTE('D');
    UART_SEND_BYTE('B');
    UART_SEND_BYTE('G');

    //Message
    UART_SEND_BYTE('F');
    UART_SEND_BYTE('I');
    UART_SEND_BYTE('N');

    return 0;
}

