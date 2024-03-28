/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :29-12-2022                                                            */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/
#ifndef  _NVIC_INTERFACE_H
#define  _NVIC_INTERFACE_H


#define  GROUP3                   0x05FA0300  //MAK 4-BIT OF IPR TO GROUPS
#define  GROUP4                   0x05FA0400  //MAK 3-BIT OF IPR TO GROUPS AND 1-BIT TO SUBGROUPS 
#define  GROUP5                   0x05FA0500  //MAK 2-BIT OF IPR TO GROUPS AND 2-BIT TO SUBGROUPS
#define  GROUP6                   0x05FA0600  //MAK 1-BIT OF IPR TO GROUPS AND 3-BIT TO SUBGROUPS
#define  GROUP7                   0x05FA0700  //MAK 4-BIT OF IPR TO SUBGROUPS

/*function to enable interrupt pin 
note pin number not include internal interrupts  */
void MNVIC_voidEnableInterrupt(u8 COPY_u8PinNumber);


/*function to disable interrupt pin 
note pin number not include internal interrupts  */
void MNVIC_voidDisableInterrupt(u8 COPY_u8PinNumber);

/*function to SET pandding flag bit 
note pin number not include internal interrupts  */
void MNVIC_voidSetPenddingFlag(u8 COPY_u8PinNumber);

/*function to clear pendding flag bit 
note pin number not include internal interrupts  */
void MNVIC_voidClrPenddingFlag(u8 COPY_u8PinNumber);

/*function to KNOW IF INTERRUPT PIN HAVE ACTIVEOR NOT 
note pin number not include internal interrupts  */
u8 MNVIC_voidActiveFlag(u8 COPY_u8PinNumber);


/* to set SW proirity of interrupt*/
void MNVIC_voidSetPriority(s8 COPY_s8IntID,u8 COPY_u8GroupProirity,u8 COPY_u8SubGroupProirity,u32 COPY_u32GROUPING);

#endif  
