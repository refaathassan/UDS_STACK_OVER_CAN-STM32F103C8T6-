/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :15-1-2023                                                              */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/
#include"std_types.h"
#ifndef    _USRT_PRIVATE_H
#define    _USRT_PRIVATE_H
//struct have USRT REGISTERS 
typedef  struct {
   volatile u32 SR;  /*STATE REGISTER OF USRT*/
   volatile u32 DR;  /*DATA REGISTER OF USRT*/
   volatile u32 BRR;   /*BUAD RATE REGISTER*/
   volatile u32 CR1;   /* GENERAL CONFIGURATION AND  INTERRUPT CONTROL ENABLE OR DISABLE FLAGES IN USRT*/
   volatile u32 CR2;   /* GENERAL CONFIGURATION IN USRT*/
   volatile u32 CR3;   /* GENERAL CONFIGURATION IN USRT*/
   volatile u32 GTPR;

}USRT_t;

//POINTER TO POINT TO ALL REGISTER IN DMA 
#define    USRT1     ((volatile USRT_t*)0x40013800)

#define    USRT2     ((volatile USRT_t*)0x40004400)

#endif
