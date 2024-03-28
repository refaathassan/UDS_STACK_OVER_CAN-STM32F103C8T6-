/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :29-12-2022                                                            */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"NVIC_interface.h"
#include"NVIC_private.h"
#include"NVIC_config.h"

/*function to enable interrupt pin 
note pin number not include internal interrupts  */
void MNVIC_voidEnableInterrupt(u8 COPY_u8PinNumber)
{
	if(COPY_u8PinNumber<=31)
	{
		NVIC_ISER0=(1<<COPY_u8PinNumber);
	}
	else if(COPY_u8PinNumber<=59)
	{
		COPY_u8PinNumber-=32;
		NVIC_ISER1=(1<<COPY_u8PinNumber);
	}
}


/*function to disable interrupt pin 
note pin number not include internal interrupts  */
void MNVIC_voidDisableInterrupt(u8 COPY_u8PinNumber)
{
	if(COPY_u8PinNumber<=31)
	{
		NVIC_ICER0=(1<<COPY_u8PinNumber);
	}
	else if(COPY_u8PinNumber<=59)
	{
		COPY_u8PinNumber-=32;
		NVIC_ICER1=(1<<COPY_u8PinNumber);
	}
}

/*function to SET pandding flag bit 
note pin number not include internal interrupts  */
void MNVIC_voidSetPenddingFlag(u8 COPY_u8PinNumber)
{
	if(COPY_u8PinNumber<=31)
	{
		NVIC_ISPR0=(1<<COPY_u8PinNumber);
	}
	else if(COPY_u8PinNumber<=59)
	{
		COPY_u8PinNumber-=32;
		NVIC_ISPR1=(1<<COPY_u8PinNumber);
	}
}

/*function to clear pendding flag bit 
note pin number not include internal interrupts  */
void MNVIC_voidClrPenddingFlag(u8 COPY_u8PinNumber)
{
	if(COPY_u8PinNumber<=31)
	{
		NVIC_ICPR0=(1<<COPY_u8PinNumber);
	}
	else if(COPY_u8PinNumber<=59)
	{
		COPY_u8PinNumber-=32;
		NVIC_ICPR1=(1<<COPY_u8PinNumber);
	}
}

/*function to KNOW IF INTERRUPT PIN HAVE ACTIVEOR NOT 
note pin number not include internal interrupts  */
u8 MNVIC_voidActiveFlag(u8 COPY_u8PinNumber)
{
	u8 Local_Resualt=0;
	if(COPY_u8PinNumber<=31)
	{
		Local_Resualt=GET_BIT(NVIC_IABR0,COPY_u8PinNumber);
	}
	else if(COPY_u8PinNumber<=59)
	{
		COPY_u8PinNumber-=32;
		Local_Resualt=GET_BIT(NVIC_IABR1,COPY_u8PinNumber);
	}
	return Local_Resualt;
}
/* to set SW proirity of interrupt*/
void MNVIC_voidSetPriority(s8 COPY_s8IntID,u8 COPY_u8GroupProirity,u8 COPY_u8SubGroupProirity,u32 COPY_u32GROUPING)
{
	u8 Local_Proirity= COPY_u8SubGroupProirity|(COPY_u8GroupProirity<<((COPY_u32GROUPING-0x05FA0300)/0x100));
	/*CORE PERIPHERAL INTERRUPTS */
	
	/*EXTERNAL INTERRUPTS*/
	if(COPY_s8IntID>=0)
	{
		NVIC_IPR[COPY_s8IntID] = Local_Proirity<<4;
		
	}
	SCB_AIRCR=COPY_u32GROUPING;
	
}
