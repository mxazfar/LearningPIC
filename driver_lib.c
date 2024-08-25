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

/// @brief Sets the pin direction
/// @param port Target port
/// @param pin Target pin
/// @param direction PIN_DIR_IN or PIN_DIR_OUT
void configurePinDirection(port_t port, pin_t pin, uint8_t direction) {
    uint8_t bitmask = (0x01 << pin);
    
    switch(direction) {
        case PIN_DIR_IN:
            GET_TRIS_ADDR(port) |= bitmask;
            break;
        case PIN_DIR_OUT:
            GET_TRIS_ADDR(port) &= ~bitmask;
            break;
    }
}

/// @brief Sets pin output
/// @param port Target port
/// @param pin Target pin
/// @param level STD_HIGH or STD_LOW
void setPinOutput(port_t port, pin_t pin, uint8_t level) {
    uint8_t bitmask = (0x01 << pin);
    
    switch(level) {
        case STD_HIGH:
            GET_PORT_ADDR(port) |= bitmask;
            break;
        case STD_LOW:
            GET_PORT_ADDR(port) &= ~bitmask;
    }
}

/// @brief Toggles the given pin on the given port
/// @param port Target port
/// @param pin Target pin
void togglePin(port_t port, pin_t pin) {
    uint8_t bitmask = (0x01 << pin);
    
    GET_PORT_ADDR(port) ^= bitmask;
}

/// @brief Utility function to set a chunk of bits in a register
/// @param addr The address of the register we are setting
/// @param data The data we want to write
/// @param startBit The start bit of our chunk
void setRegisterChunk(uint8_t addr, uint8_t data, uint8_t startBit, uint8_t stopBit) {
    uint8_t size = stopBit - startBit + 1;
    uint8_t clearBitmask = 0;
    volatile uint8_t i;

    // Generate clear bitmask based on size
    for(i = 0; i < size; i++) {
        clearBitmask |= (1 << i);
    }

    // Clear the register chunk
    addr &= ~(clearBitmask << startBit);

    // Set it to our requested data
    addr |= (data << startBit);
}

/// @brief Sets passed port to the passed byte, useful for LCD comm
/// @param port Target port
/// @param byte Target data
void setPort(port_t port, uint8_t byte) {
    GET_PORT_ADDR(port) |= byte;
}

/// @brief Function to start the timer module. enable_interupts must be called before this.
/// @param  None
void start_timer0(void) {
    OPTION_REG &= ~0b00100000;  // Clear T0CS bit to use internal clock
    OPTION_REG |= 0b00000111;   // Set prescaler to 1:256
    TMR0 = 0;                   // Clear Timer0 register
}

/// @brief Enables timer and global interrupts
/// @param None 
void enable_interrupts(void) {
    INTCONbits.TMR0IE = 1;  // Enable Timer0 interrupt
    INTCONbits.GIE = 1;     // Enable global interrupts
}