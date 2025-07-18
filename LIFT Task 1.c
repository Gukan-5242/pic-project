/*
 * File:   LIFT Task 1.c
 * Author: sekaran
 *
 * Created on 25 June, 2025, 11:41 AM
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
void delay(signed int a)
{
    while (a--);
}
void enable()
{
    RE1=1;
    delay(1000);
    RE1=0;
    delay(1000);
}
void lcd(char rs,char data)
{
    RE0=rs;
    PORTD=data;
    enable();
}
void string(char *str)
{
    while(*str)
    {
        lcd(1,*str++);
    }
}
void main()
{
    
    PORTA=0X00;PORTB=0X00;PORTC=0X00;PORTD=PORTE=0X00;
    TRISA=0XFF;
    TRISC=0XFF;
    TRISB=0X00;
    TRISD=0X00;
    TRISE=0X00;
    ANSEL=ANSELH=0X00;
    lcd(0,0X38);
    lcd(0,0X0E);
    lcd(0,0X80);
    
    while(1)
    {
        int a=0;
    int s=0;
        if(RA0==1)
        {
            a=0;
        }
        if(RA1==1)
        {
            a=1;
        }
        if(RA2==1)
        {
            a=2;
        }
        if(RA3==1)
        {
            a=3;
        }
        if(RC0==1)
        {
            s=0;
        }
        if(RC1==1)
        {
            s=1;
        }
        if(RC2==1)
        {
            s=2;
        }
        if(RC3==1)
        {
            s=3;
        }
        if(a>s)
        {
           RB0=1;
            RB1=0;
        }
        if(a<s)
        {
            RB1=1;
            RB0=0;
        }
        if(a==s)
        {
            RB1=0;
            RB0=0;
        }
    }
}