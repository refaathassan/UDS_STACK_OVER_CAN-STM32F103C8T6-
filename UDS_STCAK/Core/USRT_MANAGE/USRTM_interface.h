/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :15-1-2023                                                              */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/
#include"std_types.h"
#include"interface.h"
#ifndef    _USRTM_INTERFACE_H
#define    _USRTM_INTERFACE_H

typedef enum{FALSES ,TRUES}STATUES;



void MUSARTM_voidInit(void);
STATUES MUSARTM_u8RecieveUDSDecode(volatile u8 *ptr, u8 len,volatile u8 *ptr_return);
STATUES MUSARTM_u8transmitUDSencode(volatile u8 *ptr, u8 len,volatile u8 *ptr_return);
void MUSARTM_TransmitUDSencode(volatile u8 *ptr, u8 len);
void MUSARTM_u8RecieveUDSAsys(volatile u8 *ptr,volatile u8* len,volatile u8* flag );

#endif
