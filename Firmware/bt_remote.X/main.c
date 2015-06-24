/* 
 * File:   main.c
 * Author: karrister
 *
 * Created on 24. June 2015, 2:30
 */

#include <stdio.h>
#include <stdlib.h>


void init(void) {

    /* Set pinmuxes and other per-pin config */
    //4 - icsp/low batt indicator (input, hi = good, lo = low batt)
    //5 - nikon shutter focus (output, hi = focus camera)
    //6 - nikon shutter release (output, hi = release shutter)
    //7 - led2 (output, active hi)
    //8 - reset (output, active hi?)
    //9 - bt status (input)
    //10 - uart tx
    //11 - sw3 (input. switch open = hi, switch closed = lo)
    //12 - uart rx
    //13 - led1 (output, active hi)
    //14 - mode sw (input. switch open = hi, switch closed = lo)
    //15 - sw2 (input. switch open = hi, switch closed = lo)
    //16 - sw1 (input. switch open = hi, switch closed = lo)


}


int main(void) {

    init();

    return 0;
}

