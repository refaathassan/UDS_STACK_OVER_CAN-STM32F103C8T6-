/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :4-1-2023                                                              */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"SYSTICK_interface.h"
#include"SYSTICK_private.h"
#include"SYSTICK_config.h"

static void(*CallBack)(void);
/* TO INTIATE CLOCK SOURCE OF SYSTICK IF AHB or AHB/8 */
void MSYSTICK_voidInit(void)
{
	#if  SYSTICK_CLOCK==AHB
	      SET_BIT(SYSTICK->CTRL,2);  //TO ENABLE SYSTICK
	#elif  SYSTICK_CLOCK==AHB_8
	     CLR_BIT(SYSTICK->CTRL,2);

    #endif
	     CLR_BIT(SYSTICK->CTRL,0);
	     CLR_BIT(SYSTICK->CTRL,1);

	
}
/*TO MAKE  DELAY*/
void MSYSTICK_voidDelay(u32 COPY_u32TickNumber)
{   CLR_BIT(SYSTICK->CTRL,0);
    CLR_BIT(SYSTICK->CTRL,1);
	SYSTICK->VAL=0;
    SYSTICK->LOAD=COPY_u32TickNumber; //LOAD THE NUMBER YOU WANT TO START FROM IT
	SET_BIT(SYSTICK->CTRL,1);  //TO ENABLE SYSTICK INTERRUPT
	SET_BIT(SYSTICK->CTRL,0);  //TO ENABLE SYSTICK  TO START COUNT
}
/*TO MAKE  BUSY DELAY*/
void MSYSTICK_voidBusyDelay(u32 COPY_u32TickNumber)
{
	CLR_BIT(SYSTICK->CTRL,0);
	CLR_BIT(SYSTICK->CTRL,1);
	SYSTICK->LOAD=COPY_u32TickNumber; //LOAD THE NUMBER YOU WANT TO START FROM IT
	//SET_BIT(SYSTICK->CTRL,1);  //TO ENABLE SYSTICK INTERRUPT
	SET_BIT(SYSTICK->CTRL,0);  //TO ENABLE SYSTICK  TO START COUNT
	while(SYSTICK->VAL !=0);
}

/*TO MAKE CALLBACK TO FUNCATION WHAT YOU WANT TO IMPELEMENT*/
void MSYSTICK_voidCallBack(void(*ptr)(void))
{
	CallBack=ptr;
}

/*to disaple systick*/
void MSYSTICK_voidDisable(void)
{   CLR_BIT(SYSTICK->CTRL,0);
	CLR_BIT(SYSTICK->CTRL,1);
	SYSTICK->VAL=0;
}
void SysTick_Handler(void)
{
	//MGPIO_voidSetPinValue(GPIO_PORTB, PIN3,GPIO_HIGH);
	CallBack();
}
