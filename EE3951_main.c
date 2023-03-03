/*
 * File:   EE3951_main.c
 * Author: ryanbelmont
 *
 * Created on February 3, 2023, 1:44 PM
 */

#include "xc.h"
#include "stdint.h"
#include "circle_buffer.h"

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))


void setup(void)
{
    CLKDIVbits.RCDIV = 0; //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9FFF; //sets all pins to digital I/O
    TRISA = 0b1111111111111110;  // set pin RA0 to output
    LATA = 0x0000; // set pin RA0
}

void adc_init()
{
    TRISAbits.TRISA0 = 1;
    AD1PCFGbits.PCFG0 = 0;      // setup I/O
    
    AD1CON2bits.VCFG = 0b000;   // AVDD (3.3v) and AVSS 0v as min and max
    AD1CON3bits.ADCS = 0;       // 1*tcy = TAD
    AD1CON1bits.SSRC = 0b010;   // end sample and convert at timer 3 rollover
    AD1CON3bits.SAMC = 13;       // 13*TAD auto sample  
    AD1CON1bits.FORM = 0;       // output is in the form of unsigned int
    
    AD1CON1bits.ASAM = 1;       // auto  sampler auto sets SAMP - automatically begin sampling after conversion finishes
    AD1CON2bits.SMPI = 0b1111; // interrupt after 1 conversion
    AD1CON1bits.ADON = 1;
    
    _AD1IF = 0;
    _AD1IE = 1;
    
    TMR3 = 0; // settup timer 3
    T3CON = 0;
    T3CONbits.TCKPS = 0b10; // 1:64 prescale
    PR3 = 15000-1; // .06 seconds 
    T3CONbits.TON = 1;
            
}

void __attribute__((__interrupt__,__auto_psv__)) _ADC1Interrupt(void)
{
    _AD1IF = 0; // reset flag
    putVal(ADC1BUF0); // put value into the circular buffer.
}

int main(void) {
    setup();
    adc_init();
    initBuffer();
    
    
    while(1)
    {
        
    }
    return 0;
}
