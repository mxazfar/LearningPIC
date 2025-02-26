/*
 * File:   main.c
 * Author: mazfar
 *
 * Created on August 24, 2024, 5:08 PM
 */


#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic16f887.h>
#include "driver_lib.h"

volatile uint8_t secondsPassed = 0;
volatile uint16_t timerCnt = 0;

volatile uint8_t timerTriggered = STD_LOW;

void __interrupt() interruptHandler(void) {
    if (INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;  // Clear the interrupt flag
        
        timerTriggered = STD_HIGH;
        
        TMR0 = 0;               // Reset Timer0
    }
}

void main(void) {
    port_t port = PortA;
    
    uint8_t ledPin = 0;
    uint8_t timerPin = 1;
    
    start_timer0();
    enable_interrupts();
    
    configurePinDirection(port, ledPin, PIN_DIR_OUT);
    configurePinDirection(port, timerPin, PIN_DIR_OUT);
    
    setPinOutput(port, ledPin, STD_HIGH);
    
    while(1) {
        if(timerTriggered == STD_HIGH) {
            timerTriggered = STD_LOW;
            timerCnt++;
            
            if(timerCnt == TMR_CNT_SEC) {
                timerCnt = 0;
                
                togglePin(port, timerPin);
            }
        }
    }
}
