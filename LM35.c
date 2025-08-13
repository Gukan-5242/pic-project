/*
 * File:   pic.c
 * Author: Dell
 *
 * Created on 9 June, 2025, 12:47 PM
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
void lcd(char rs, char data) {
    RE0 = rs;
    PORTD = data;
    RE1 = 1;
    for (int i = 0; i < 100; i++);
    RE1 = 0;
    for (int i = 0; i < 100; i++);
}
int low=0,low1=0,high1=0,high=0,value=0,value1=0;
float voltage=0;
void ADC()
{
    ADCON0=0X81;
    ADCON1=0XB0;
  
        GO=1;
        while(GO==1);
        low=ADRESL;
        high=ADRESH;
        if(high==0)
        {
            value=low;
        }
        if(high==1)
        {
            value=low+256;
        }
        if(high==2)
        {
            value=low+512;
        }
        if(high==3)
        {
            value=low+768;
        }
        lcd(0,0X80);
     int a=value/1000;
        int b=(value/100)%10;
        int c=(value/10)%10;
        int d=value%10;
        
        lcd(1,a+48);
        lcd(1,b+48);
        lcd(1,c+48);
        lcd(1,d+48);
        
////        voltage=(value*1.5)/1023.0;
        lcd(0,0X86);
         
          int f=voltage*100;
        lcd(1,((f/100)%10)+48);
        lcd(1,((f/10)%10)+48);
        lcd(1,(f%10)+48);
        lcd(1,'C');
        lcd(0,0XC0);
       
}
void main()
{
    PORTA=0X00;
    PORTD=0X00;
    PORTE=0X00;
    TRISA=0XFF;
    TRISD=TRISE=0X00;
    ANSEL=0X01;
    ANSELH=0X00;
    //ADCON0=0X85;
    //ADCON1=0X80;
     lcd(0, 0X38);
    lcd(0, 0X0E);
   
   
    while(1)
    {
            
            ADC();
            
    }
}