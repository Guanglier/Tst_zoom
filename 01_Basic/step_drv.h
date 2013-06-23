#ifndef STEP_DRV_H_FILE
#define STEP_DRV_H_FILE


#include "machine.h"


enum{
       MOT_DIR_FORW,
       MOT_DIR_BACK,
       MOT_DIR_OFF,
       DEF_DIR_STOP

};

void mot_gestion_a (uint8 l_dir );
void mot_gestion_b (uint8 l_dir );
void mot_gestion_init ( void );


#endif




