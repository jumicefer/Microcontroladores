/*
 * File:   CONTROLDEMOTOR.c
 * Author: kenst
 *
 * Created on 11 de mayo de 2021, 10:34
 */

#include <xc.h>
#include <stdio.h>
#include "LCD2.h"
#define _XTAL_FREQ 4000000
float ciclo;
float ccp = 0;
float ccp1 = 0;
float dato[];
int res;

void configuracion_registros(void);
void Ciclo_util (void);
void PWM (void);


void main(void) 
{
    TRISA = 1;
    TRISC = 0;
    TRISD = 0;
    TRISC = 0;
    configuracion_registros();
    lcd_init();
    lcd_clear_display();
    __delay_ms (10);    
    lcd_clear_display();
       lcd_goto(3,0);
    lcd_print ("DUTY CYCLE");
    
    while (1){
        Ciclo_util ();
        sprintf (dato, "%f",ciclo);
        lcd_goto(0,2);
        lcd_print(dato);
        lcd_print(" % ");
        __delay_ms(100);
        PWM ();
    }
    return;
}
void configuracion_registros(void)
{
    ADCON0 = 0;
    ADCON1 = 14;
    ADCON2 = 148;
}
void Ciclo_util (void){
    ADCON0bits.ADON = 1;
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE == 1)
    {
        float dutycycle = 0;
        float dutycyclet = 0;
        
        dutycyclet = ADRESL +(ADRESH*256);
        dutycycle = dutycyclet*100/1023;
        ciclo = dutycycle;

 
    }
 
}
void PWM (void){
   /*PR2 = 99;
    ccp = ciclo;
    CCPR1L = ccp;
    TRISCbits.RC1 = 0;
    TRISCbits.RC2 = 0;
    
    if (ccp >=768){
        ccp1 = 3;
    }
    else if (ccp >=512){
        ccp1 = 2;
    }
    else if (ccp >=256){
        ccp1 = 1;
    }
    else{
        ccp1 = 0;
    }
    T2CON = 0x00;
    CCP1CON = (ccp1*16)+12;
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;*/
    
    PR2 = 99;
    ccp = ciclo;
    res = ccp*400/100; // Variacion del del motor
    CCPR1L = res>>2;// sin las 2 ultimas cifras 
    TRISCbits.RC1 = 0;
    TRISCbits.RC2 = 0;
    T2CON = 0x00;
    CCP1CON =0x0C;// configurado como PWM
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;
    
           
}
