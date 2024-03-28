/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :4-1-2023                                                              */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/

#ifndef    _SYSTICK_PRIVATE_H
#define    _SYSTICK_PRIVATE_H
//struct have AFIO REGISTERS 
typedef  struct {
	volatile u32 CTRL;  /*TO ENABLE OR DISAPLE TIMER
	                      TO ENABLE OR DISAPLE INTERRUPT
						  ENALBLE CLOCK SOURCE  0:AHP/8   , 1:AHB   */
	volatile u32 LOAD;  /*TO BUT THE VALUE YOU WANT TO START FROM IT */
	volatile u32 VAL;   /*TAKE VALUE FROM LOAD AND START TO DECREASE IT UNTILE REACH TO ZERO */
	volatile u32 CALIB;	/* TO CALABRATE TIMER*/
}SYSTICK_t;  

//POINTER TO POINT TO ALL REGISTER IN AFIO 
#define    SYSTICK     ((volatile  SYSTICK_t*)0xE000E010)


/*types of clock source */ 
#define   AHB_8         0
#define   AHB           1
#endif
