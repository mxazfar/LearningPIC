/* 
 * File:   driver_lib.h
 * Author: mazfar
 *
 * Created on August 24, 2024, 5:59 PM
 */
#ifndef DRIVER_LIB_H
#define	DRIVER_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define PORTA_ADDRESS 0x05
#define TRISA_ADDRESS 0x85

#define GET_TRIS_ADDR(port) *((volatile uint8_t*) TRISA_ADDRESS + port)
#define GET_PORT_ADDR(port) *((volatile uint8_t*) PORTA_ADDRESS + port)
    
#define STD_HIGH 0x01
#define STD_LOW  0x00
    
#define PIN_DIR_IN  0x00
#define PIN_DIR_OUT 0x01
    
#define TMR_CNT_SEC 9008U
    
typedef enum {
    PortA,
    PortB,
    PortC,
    PortD,
    PortE,
    PortNum
} port_t;

void configurePinDirection(port_t port, uint8_t pin, uint8_t direction);
void setPinOutput(port_t port, uint8_t pin, uint8_t level);
void togglePin(port_t port, uint8_t pin);

void start_timer0(void);

void enable_interrupts(void);


#ifdef	__cplusplus
}
#endif

#endif	/* DRIVER_LIB_H */

