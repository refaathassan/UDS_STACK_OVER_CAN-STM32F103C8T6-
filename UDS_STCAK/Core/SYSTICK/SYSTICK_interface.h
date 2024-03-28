/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :4-1-2023                                                              */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/

#ifndef    _SYSTICK_INTERFACE_H
#define    _SYSTICK_INTERFACE_H



/* TO INTIATE CLOCK SOURCE OF SYSTICK IF AHB or AHB/8 */

void MSYSTICK_voidInit(void);
/*TO MAKE  DELAY*/
void MSYSTICK_voidDelay(u32 COPY_u32TickNumber);

/*TO MAKE  BUSY DELAY*/
void MSYSTICK_voidBusyDelay(u32 COPY_u32TickNumber);

/*TO MAKE CALLBACK TO FUNCATION WHAT YOU WANT TO IMPELEMENT*/
void MSYSTICK_voidCallBack(void(*ptr)(void));

/*to disaple systick*/
void MSYSTICK_voidDisable(void);
#endif
