
#include "p18F4680.h"
#include "step_drv.h"


#define B1_PIN_1_TRIS   TRISDbits.TRISD7
#define B1_PIN_2_TRIS   TRISDbits.TRISD6
#define B1_PIN_1        PORTDbits.RD7
#define B1_PIN_2        PORTDbits.RD6
#define B2_PIN_1_TRIS   TRISDbits.TRISD5
#define B2_PIN_2_TRIS   TRISDbits.TRISD4
#define B2_PIN_1        PORTDbits.RD5
#define B2_PIN_2        PORTDbits.RD4


// commandes pour les broches de pilotage
#define DRIVE_MOT_B1_SENS_1         B1_PIN_1=1; B1_PIN_2=0;
#define DRIVE_MOT_B1_SENS_2         B1_PIN_1=0; B1_PIN_2=1;
#define DRIVE_MOT_B1_OFF            B1_PIN_1=0; B1_PIN_2=0;
#define DRIVE_MOT_B2_SENS_1         B2_PIN_1=1; B2_PIN_2=0;
#define DRIVE_MOT_B2_SENS_2         B2_PIN_1=0; B2_PIN_2=1;
#define DRIVE_MOT_B2_OFF            B2_PIN_1=0; B2_PIN_2=0;

// nombres représentant une commande à effectuer
#define DEF_MOT_SENS_1			(0x01)
#define DEF_MOT_SENS_2			(0x02)
#define DEF_MOT_STOP			(0x03)
#define DEF_MOT_OFF			(0x00)


//==============================================================
//          MOTEUR B
#define MOT_B_B1_PIN_1_TRIS   TRISDbits.TRISD3
#define MOT_B_B1_PIN_2_TRIS   TRISDbits.TRISD2
#define MOT_B_B1_PIN_1        PORTDbits.RD3
#define MOT_B_B1_PIN_2        PORTDbits.RD2
#define MOT_B_B2_PIN_1_TRIS   TRISCbits.TRISC4
#define MOT_B_B2_PIN_2_TRIS   TRISCbits.TRISC5
#define MOT_B_B2_PIN_1        PORTCbits.RC4
#define MOT_B_B2_PIN_2        PORTCbits.RC5


// commandes pour les broches de pilotage
#define DRIVE_MOT_B_B1_SENS_1         MOT_B_B1_PIN_1=1; MOT_B_B1_PIN_2=0;
#define DRIVE_MOT_B_B1_SENS_2         MOT_B_B1_PIN_1=0; MOT_B_B1_PIN_2=1;
#define DRIVE_MOT_B_B1_OFF            MOT_B_B1_PIN_1=0; MOT_B_B1_PIN_2=0;
#define DRIVE_MOT_B_B2_SENS_1         MOT_B_B2_PIN_1=1; MOT_B_B2_PIN_2=0;
#define DRIVE_MOT_B_B2_SENS_2         MOT_B_B2_PIN_1=0; MOT_B_B2_PIN_2=1;
#define DRIVE_MOT_B_B2_OFF            MOT_B_B2_PIN_1=0; MOT_B_B2_PIN_2=0;






#define MOT_NB_ETAPES	(8)			//sert par la suite, sinon g_tab_step aurait pu être de dimension auto !

// étapes pour la bobine 1
uint8	g_tab_step_b1[MOT_NB_ETAPES]= {
	DEF_MOT_OFF,
	DEF_MOT_SENS_1,
	DEF_MOT_SENS_1,
	DEF_MOT_SENS_1,
	DEF_MOT_OFF,
	DEF_MOT_SENS_2,
	DEF_MOT_SENS_2,
	DEF_MOT_SENS_2
};

// étapes pour la bobine 2
uint8	g_tab_step_b2[MOT_NB_ETAPES]= {
	DEF_MOT_SENS_1,
	DEF_MOT_SENS_1,
	DEF_MOT_OFF	,
	DEF_MOT_SENS_2,
	DEF_MOT_SENS_2,
	DEF_MOT_SENS_2,
	DEF_MOT_OFF	,
	DEF_MOT_SENS_1
};



void mot_gestion_init ( void ){
    DRIVE_MOT_B1_OFF;
    DRIVE_MOT_B2_OFF;
    B1_PIN_1_TRIS = 0;
    B1_PIN_2_TRIS = 0;
    B2_PIN_1_TRIS = 0;
    B2_PIN_2_TRIS = 0;

    DRIVE_MOT_B_B1_OFF;
    DRIVE_MOT_B_B2_OFF;
    MOT_B_B1_PIN_1_TRIS = 0;
    MOT_B_B1_PIN_2_TRIS = 0;
    MOT_B_B2_PIN_1_TRIS = 0;
    MOT_B_B2_PIN_2_TRIS = 0;


}


void mot_gestion_a (uint8 l_dir ){
	static 	uint8 l_etat=0;


	switch (l_dir)
	{
		case MOT_DIR_FORW:
			l_etat++;
			if ( l_etat >= MOT_NB_ETAPES){ l_etat = 0; }
			break;
		case MOT_DIR_BACK:
			if ( l_etat > 1){ l_etat--; }else{ l_etat = MOT_NB_ETAPES-1; }
			break;
		case DEF_DIR_STOP:
			break;
		case MOT_DIR_OFF:
			l_etat = 0;
			break;

	}



	switch ( g_tab_step_b1[l_etat] )
	{

		case DEF_MOT_SENS_1:
			DRIVE_MOT_B1_SENS_1;
			break;

		case DEF_MOT_SENS_2:
			DRIVE_MOT_B1_SENS_2;
			break;
		case DEF_MOT_STOP:
			break;
		default:
		case DEF_MOT_OFF:
			DRIVE_MOT_B1_OFF;
			break;
	};

	switch ( g_tab_step_b2[l_etat] )
	{

		case DEF_MOT_SENS_1:
			DRIVE_MOT_B2_SENS_1;
			break;

		case DEF_MOT_SENS_2:
			DRIVE_MOT_B2_SENS_2;
			break;
		case DEF_MOT_STOP:
			break;
		default:
		case DEF_MOT_OFF:
			DRIVE_MOT_B2_OFF;
			break;
	};

}







void mot_gestion_b (uint8 l_dir ){
	static 	uint8 l_etat=0;


	switch (l_dir)
	{
		case MOT_DIR_FORW:
			l_etat++;
			if ( l_etat >= MOT_NB_ETAPES){ l_etat = 0; }
			break;
		case MOT_DIR_BACK:
			if ( l_etat > 1){ l_etat--; }else{ l_etat = MOT_NB_ETAPES-1; }
			break;
		case DEF_DIR_STOP:
			break;
		case MOT_DIR_OFF:
			l_etat = 0;
			break;

	}



	switch ( g_tab_step_b1[l_etat] )
	{

		case DEF_MOT_SENS_1:
			DRIVE_MOT_B_B1_SENS_1;
			break;

		case DEF_MOT_SENS_2:
			DRIVE_MOT_B_B1_SENS_2;
			break;
		case DEF_MOT_STOP:
			break;
		default:
		case DEF_MOT_OFF:
			DRIVE_MOT_B_B1_OFF;
			break;
	};

	switch ( g_tab_step_b2[l_etat] )
	{

		case DEF_MOT_SENS_1:
			DRIVE_MOT_B_B2_SENS_1;
			break;

		case DEF_MOT_SENS_2:
			DRIVE_MOT_B_B2_SENS_2;
			break;
		case DEF_MOT_STOP:
			break;
		default:
		case DEF_MOT_OFF:
			DRIVE_MOT_B_B2_OFF;
			break;
	};

}



