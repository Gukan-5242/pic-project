/*
 * File:   Digital Thermometer task.c
 * Author: sekaran
 *
 * Created on 18 July, 2025, 11:01 AM
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
int high=0,high1=0,low=0,value=0;
int a=0;
int b=0;
int c=0;
int d=0;
int e=0;
int f=0;
int g=0;
int h=0;
float voltage=0;
void main(void) 
{
    PORTA=PORTC=PORTD=PORTE=PORTB=0X00;
    TRISA = 0X0F;
    TRISB=0X01;
    TRISC=TRISD=TRISE=0X00;
    ANSEL=0X00;//(RB1)
    ANSELH=0X10;
    ADCON0=0XB1;
    ADCON1=0XB0;
    lcd(0,0X38);
    lcd(0,0X0E);  
    while(1)
    {
        /*ADCON0=0X81;
        ADCON1=0XB0;*/
        
        GO=1;
        while(GO==1)
        low=ADRESL;
        high=ADRESH;
        if(high==0)
        {
            //0 0 ->0
            value=low;
        }
        if(high==1)
        {
            //0 1 -> 1=256
            value=low+256;
        }
        if(high==2)
        {
            //1 0 -> 2=512
            value=low+512;
        }
        if(high==3)
        {
            //1 1 -> 3=768
            value=low+768;
        }
        if(RA0==1)
        {
        lcd(0,0X80);
        string("celcius:");
        voltage=(value*1.5)/1023.0;
        c = voltage*100;
        lcd(1,(c/100)%10+48);
        lcd(1,(c/10)%10+48);
        lcd(1,c%10+48);
        lcd(1,39);
        lcd(1,' C');
        while(RA0==1);
        }
        if(RA1==1)
        {
            lcd(0,0xC0);
            string("FARENHEIT:");
            b = ((c*9)/5)+32;
            lcd(1,(b/100)%10+48);
            lcd(1,(b/10)%10+48);
            lcd(1,b%10+48);
            lcd(1,39);
            lcd(1,' F');
        }
        if(b>98)
        {
            lcd(0,0x01);
            lcd(0,0x80);
            string("ABOVE BODY TEMPERATURE");
            RC0=1;
        }
}
}
