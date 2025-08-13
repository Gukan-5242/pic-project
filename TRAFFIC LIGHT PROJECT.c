/*
 * File:   TRAFFIC LIGHT PROJECT.c
 * Author: sekaran
 *
 * Created on 13 August, 2025, 12:49 PM
 */
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
    while(a--);
}
void enable()
{
    RE1=1;
    delay(10);
    RE1=0;
    delay(10);
}
void lcd(char rs,char data)
{
    RE0=rs;
    PORTC=data;
    enable();
}
void string(char *str)
{
    while(*str)
    {
        lcd(1,*str++);
    }
}
int b[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0XFF,0X67};
int count=0,i=0,j=0,c=0;
void timer(int a)
{
    count =0;
    while(count<(2*a))
    {
        if(TMR1IF==1)
        {
            count++;
            TMR1=3036;
            TMR1IF=0;
        }
    }
}
int main()
{
    PORTA=PORTB=PORTC=PORTD=PORTE=0X00;
    TRISA=0X07;
    TRISB=TRISC=TRISD=TRISE=0X00;
    ANSEL=ANSELH=0X00;
    T1CON=0X35;
    TMR1=3036;
    lcd(0,0X38);
    lcd(0,0X0E);
    lcd(0,0X80);
    while(1)
    {
        if(RA0==1)
        {
            lcd(0,0x80);
            string("SYSTEM ON");
            RB0=RB3=1;
            i=1;
        }
        if(RA1==1 && i==1)
        {
            lcd(0,0x01);
            lcd(0,0x80);
            string(" WALKING");
            RB0=RB3=0;
            RB0=RB5=1;
            timer(5);
            RB0=RB5=0;
            RB1=RB4=1;
            timer(3);
            RB1=RB4=0;
            RB2=RB3=1;
            timer(2);
            RB2=RB3=1;
            RB2=RB3=0;
        }
        if(RA2==1)
        {
            c++;
            while(RA2==1);
        }
            lcd(0,0XC0);
            lcd(1,(c/10)%10+48);
            lcd(1,c%10+48);
            if(c==10)
            {
                RB2=0;
                RB0=RB3=1;
                lcd(0,0X01);
                lcd(0,0X80);
                string("  WALKING");
                for(j=0;j<10;j++)
                {
                    PORTD=b[j];
                    timer(1);
                }
            }
        }
}
