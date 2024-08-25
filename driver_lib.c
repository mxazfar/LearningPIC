/*
 * File:   driver_lib.c
 * Author: mazfar
 * 
 * My OWN lower level driver library for PIC16F887
 *
 * Created on August 24, 2024, 5:40 PM
 */

#include <xc.h>
#include <pic16f887.h>
#include <stdint.h>

#include "driver_lib.h"

void configurePinDirection(port_t port, uint8_t pin, uint8_t direction) {
    uint8_t bitmask = (1 << pin);
    
    switch(direction) {
        case PIN_DIR_IN:
            GET_TRIS_ADDR(port) |= bitmask;
        case PIN_DIR_OUT:
            GET_TRIS_ADDR(port) &= ~bitmask;       
    }
}

void setPinOutput(port_t port, uint8_t pin, uint8_t level) {
    uint8_t bitmask = (1 << pin);
    
    switch(level) {
        case STD_HIGH:
            GET_PORT_ADDR(port) |= bitmask;
            break;
        case STD_LOW:
            GET_PORT_ADDR(port) &= ~bitmask;
    }
}
