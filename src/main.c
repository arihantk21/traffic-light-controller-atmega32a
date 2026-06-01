/*
 * 4-Way Traffic Light Controller with Countdown Timer
 * Microcontroller: ATmega32
 * Clock: 8 MHz Internal RC
 * 
 * Based on working traffic light pattern with added 7-segment countdown
 * 
 * Pin Configuration:
 * PORTB: PB0-PB7 -> Traffic Light control bits
 * PORTD: PD0-PD3 -> Traffic Light control bits
 * PORTC: PC0-PC3 -> 74LS47 BCD Decoder (A, B, C, D)
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

// Function to display BCD digit on 7-segment via 74LS47
void display_bcd(uint8_t num) {
    // Output BCD value to PC0-PC3 (lower 4 bits)
    PORTC = (PORTC & 0xF0) | (num & 0x0F);
}

// Delay function with countdown for GREEN phase (10 seconds)
void delay_green_countdown(void) {
    for (uint8_t i = 10; i > 0; i--) {
        display_bcd(i);
        _delay_ms(1000);  // 1 second delay (compile-time constant)
    }
    display_bcd(0);
}

// Delay function with countdown for YELLOW phase (3 seconds)
void delay_yellow_countdown(void) {
    for (uint8_t i = 3; i > 0; i--) {
        display_bcd(i);
        _delay_ms(1000);  // 1 second delay (compile-time constant)
    }
    display_bcd(0);
}

int main(void)  // Changed from void main() to int main(void)
{
    // Configure PORTB as output (traffic lights)
    DDRB = 0xFF;
    
    // Configure PORTD as output (traffic lights)
    DDRD = 0xFF;
    
    // Configure PORTC lower 4 bits as output (BCD for 7-segment)
    DDRC = 0x0F;
    
    // Initialize 7-segment to 0
    PORTC = 0x00;
    
    while(1)
    {
        // LIGHT 1 GREEN PHASE (10 seconds)
        PORTB = 0b0100110;
        PORTD = 0b00000010;
        delay_green_countdown();
        
        // LIGHT 1 YELLOW PHASE (3 seconds) 
        PORTB = 0b01010010;
        PORTD = 0b00000010;
        delay_yellow_countdown();
        
        // LIGHT 2 GREEN PHASE (10 seconds)
        PORTB = 0b01100001;
        PORTD = 0b00000010;
        delay_green_countdown();
        
        // LIGHT 2 YELLOW PHASE (3 seconds) 
        PORTB = 0b10010001;
        PORTD = 0b00000010;
        delay_yellow_countdown();
        
        // LIGHT 3 GREEN PHASE (10 seconds)
        PORTD = 0b00000011;
        PORTB = 0b00001001;
        delay_green_countdown();
        
        // LIGHT 3 YELLOW PHASE (3 seconds)
        PORTB = 0b10001001;
        PORTD = 0b00000100;
        delay_yellow_countdown();
        
        // LIGHT 4 GREEN PHASE (10 seconds)
        PORTD = 0b00001000;
        PORTB = 0b01001001;
        delay_green_countdown();
        
        // LIGHT 4 YELLOW PHASE (3 seconds) 
        PORTD = 0b00000100;
        PORTB = 0b01001010;
        delay_yellow_countdown();
    }
    
    return 0;  // Added return statement
}
