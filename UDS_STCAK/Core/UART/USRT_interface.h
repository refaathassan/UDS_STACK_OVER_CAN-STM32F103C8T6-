/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :15-1-2023                                                              */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/
#include"std_types.h"
#include"interface.h"
#ifndef    _USRT_INTERFACE_H
#define    _USRT_INTERFACE_H

//typedef enum{FALSE ,TRUE}STATUES;

/*INITIATE USRT  */
void MUSRT1_voidInit(void);

void MUSRT1_voidInterrputEnable(void);
void MUSRT1_voidInterrputDisable(void);
void MUSART1_u8RecieveChrAsys(volatile u8 *ptt );
void MUSART1_u8RecieveUDSAsys(volatile u8 *ptr,volatile u8* len,volatile u8* flag );
/*TO SEND  CHAR data  */
void  MUSRT1_voidTransimtChr(u8 COPY_u8Data);

/*TO SEND  string data  */
void  MUSRT1_voidTransimtString(u8 *Ptr_u8Data);

/*TO RECIEVED data*/
u8 MUSART1_u8RecieveChr( void );
//volatile ERROR_STATUES MUSART1_u8RecieveHex( volatile u16 * ptr);
void MUSART1_u8RecieveAsys(void (FUN)(void ));
void MUSRT2_voidInit(void);
void MUSRT2_voidInterrputEnable(void);
void MUSRT2_voidInterrputDisable(void);
void MUSART2_u8RecieveChrAsys(volatile u16 *ptr );

/*TO SEND  CHAR data  */
void  MUSRT2_voidTransimtChr(u8 COPY_u8Data);
u8 MUSART2_u8RecieveChr( void );

#endif
