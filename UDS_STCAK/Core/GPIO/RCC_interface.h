/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :23-12-2022                                                            */
/*           VERSION      :V02                                                                   */
/*************************************************************************************************/
#include"STD_TYPES.h"
#ifndef     _RCC_INTERFACE_H
#define     _RCC_INTERFACE_H

/* TYPES OF BUSES TO PERIPHERALS */
#define     RCC_AHP     0     
#define     RCC_APB1    1    
#define     RCC_APB2    2

/* PERIPHERAL IDS */
#define      AFIO_BUS              0
#define      PORTA_BUS             2
#define      PORTB_BUS             3
#define      PORTC_BUS             4

  /* TO INTIATE THE CLOCK OF SYSTEM */
void RCC_voidIintSysClock(void); 

/*  TO ENABLE CLOCK TO SPECFICE PERIPHERAL
 PERIPHERAL IDS:
                PORTA_BUS
                PORTB_BUS
                PORTC_BUS
  BUSID :
                  RCC_AHP
                  RCC_APB1
                  RCC_APB2     */


void RCC_voidDisableClock(u8 Copy_u8BusId , u8 Copy_u8PerId); 

/*  TO DISABLE CLOCK TO SPECFICE PERIPHERAL
 PERIPHERAL IDS:
                PORTA_BUS
                PORTB_BUS
                PORTC_BUS
  BUSID :
                  RCC_AHP
                  RCC_APB1
                  RCC_APB2     */
void RCC_voidEnableClock(u8 Copy_u8BusId , u8 Copy_u8PerId);

#endif
