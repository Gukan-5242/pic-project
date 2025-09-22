/*
 * File:   Car project ultrasonic sensor.c
 * Author: sekaran
 *
 * Created on 18 September, 2025, 4:08 PM
 */
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#include <xc.h>
#define _XTAL_FREQ 4000000   // 4 MHz internal oscillator

// ---------------- LCD Functions ----------------
// Data -> PORTD, RS -> RE0, EN -> RE1

void delay(signed int a)
{
    while(a--);
}

void enable()
{
    RE1 = 1;
    delay(1000);
    RE1 = 0;
    delay(1000);
}

void lcd(char rs, char data)
{
    RE0 = rs;
    PORTD = data;
    enable();
}

void string(char *str)
{
    while(*str)
    {
        lcd(1,*str++);
    }
}

// ---------------- Ultrasonic Function ----------------
// Trigger -> RC0, Echo -> RC1

unsigned int getDistance()
{
    unsigned int distance;
    unsigned long time;

    // Trigger pulse
    RC0 = 1;
    __delay_us(10);
    RC0 = 0;

    // Wait for echo high
    while(!RC1);
    time = 0;
    while(RC1)
    {
        __delay_us(1);
        time++;
    }

    // Convert time to distance (cm)
    distance = time / 58;
    return distance;
}

// ---------------- Main Program ----------------

int main()
{
    // Pin setup
    PORTA = PORTC =PORTB = PORTD = PORTE = 0x00;
    TRISA = 0xFF;      // RA0=Start, RA1=Door, RA2=Reverse
    TRISB = 0x00;
    TRISC = 0x02;      // RC1 Echo input, RC0/RC2/RC3 outputs
    TRISD = 0x00;
    TRISE = 0x00;
    ANSEL = ANSELH = 0x00;
    lcd(0,0x38);    // 8-bit, 2 line
    lcd(0,0x0C);    // Display ON, Cursor OFF
    lcd(0,0x06);    // Entry mode
    lcd(0,0x01);    // Clear display
    delay(1000);
    string("System Ready");

    __delay_ms(1000);
    lcd(0,0x01);

    while(1)
    {
        // ---------------- Button 1: Car Start ----------------
        if(RA0 == 1)
        {
            lcd(0,0x01);
            lcd(0,0x80);
            string("Car Started");
            RC2 = 0;   // Buzzer OFF
           // RB1 = 0;   // LED OFF
            __delay_ms(500);
            while(RA0==1); // Wait for release
        }

        // ---------------- Button 2: Door Indication ----------------
        /*if(RA1 == 1)
        {
            lcd(0,0x01);
            lcd(0,0x80);
            string("Door Status:");*/

            if(RA1 == 1 && RA2==1 && RA3==1 && RA4==1) // Assume RA3 = Door Sensor Switch
            {
                lcd(0,0xC0);
                
                RB1 = 1; // LED ON
                RB0=0; 
                //PORTB = 0x01;
                string("Door:OPEN ");
            }
        
            else
            {
                lcd(0,0xC0);
                string("Door:CLOSED");
                RB0 = 1;   // LED OFF
                RB1=0;
                //PORTB = 0x02;
            }

            //__delay_ms(500);
            //while(RA1==1); // Wait for release
       

        // ---------------- Button 3: Reverse Mode ----------------
        if(RA5 == 1)
        {
            lcd(0,0x01);
            lcd(0,0x80);
            string("Reverse Mode");

            unsigned int d = getDistance();

            lcd(0,0xC0);
            string("Dist: ");
            lcd(1,(d/100) + '0');
            lcd(1,((d/10)%10) + '0');
            lcd(1,(d%10) + '0');
            lcd(1,'c');
            lcd(1,'m');
            
            if(d < 15) 
                RC2 = 1;   // Buzzer ON
            else
                RC2 = 0;   // Buzzer OFF
            __delay_ms(500);
            while(RA2==1); // Wait for release
        }
    }
}
