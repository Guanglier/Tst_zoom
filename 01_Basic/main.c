/*
 * File:   newmain.c
 * Author: user
 *
 * Created on 2 juin 2013, 16:20
 */
#include "machine.h"
#include "step_drv.h"
#include <stdio.h>
#include <stdlib.h>


#include <xc.h>

// CONFIG1H
#pragma config OSC = HSPLL         // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = BOHW     // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (VBOR set to 2.1V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

/*
 *
 */


#define BTN_1    PORTBbits.RB0
#define BTN_2    PORTBbits.RB1

#define BTN_3    PORTAbits.RA0
#define BTN_4    PORTAbits.RA1

#define TEMPS_MIN   (0x4000)
#define TEMPS_MAX   (0x1000)


void main ( void ){
uint16  l_cpt;
uint16  l_temps;

    ADCON1 = 0xff;
    CMCON = 0x07;

    mot_gestion_init ();

do{
        if ( 0 == BTN_1 ){
           mot_gestion_a ( MOT_DIR_FORW );
        }

        if ( 0 == BTN_2 ){
            mot_gestion_a ( MOT_DIR_BACK );
        }

        if ( 0 == BTN_3 ){
            mot_gestion_b ( MOT_DIR_FORW );
        }

        if ( 0 == BTN_4 ){
            mot_gestion_b ( MOT_DIR_BACK );
        }



        for ( l_cpt=0 ; l_cpt<TEMPS_MAX ; l_cpt++){}

}while(1);
}