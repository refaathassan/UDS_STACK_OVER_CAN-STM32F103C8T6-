/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :25-12-2022                                                            */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/

#include <GPIO_interfac.h>
#include"STD_TYPES.h"
#include"BIT_MATH.h"
//#include"RCC_interface.h"
#include"GPIO_private.h"
#include"GPIO_config.h"
/*   TO SET MODE OF PINS IN PORTS */
void  MGPIO_voidSetPinDirection(u8 COPY_u8Port,u8 COPY_u8Pin,u8 COPY_u8Mode)
{
	switch(COPY_u8Port)
	{
		case GPIO_PORTA:
			             //RCC_voidDisableClock(RCC_APB2, 2);
		                 if(COPY_u8Pin<=7)  //TO CHECK IF I USED HIGHT OR LOW  CR REGISTER
						 {
							 GPIO_PORTA_CRL &= (~((0b1111)<<(COPY_u8Pin*4)));    // TO REST BITS I WILL USED 
							 GPIO_PORTA_CRL |= ((COPY_u8Mode)<<(COPY_u8Pin*4));  // TO SET MODE IN THE BITS 
						 }
		                 else if(COPY_u8Pin<=15)
						 {   COPY_u8Pin=COPY_u8Pin-8;
							 GPIO_PORTA_CRH &= (~((0b1111)<<(COPY_u8Pin*4)));
							 GPIO_PORTA_CRH |= ((COPY_u8Mode)<<(COPY_u8Pin*4));
						 }
						 break;
		case GPIO_PORTB:
						//RCC_voidDisableClock(RCC_APB2, 3);
		                 if(COPY_u8Pin<=7)
						 {
							 GPIO_PORTB_CRL &= (~((0b1111)<<(COPY_u8Pin*4)));
							 GPIO_PORTB_CRL |= ((COPY_u8Mode)<<(COPY_u8Pin*4));
						 }
		                 else if((COPY_u8Pin>=7)&&(COPY_u8Pin<=15))
						 {   COPY_u8Pin=COPY_u8Pin-8;
							 GPIO_PORTB_CRH &= (~((0b1111)<<(COPY_u8Pin*4)));
							 GPIO_PORTB_CRH |= ((COPY_u8Mode)<<(COPY_u8Pin*4));
						 }
						 break;
		case GPIO_PORTC:
						//RCC_voidDisableClock(RCC_APB2, 4);
		                 if(COPY_u8Pin<=7)
						 {
							 GPIO_PORTC_CRL &= (~((0b1111)<<(COPY_u8Pin*4)));
							 GPIO_PORTC_CRL |= ((COPY_u8Mode)<<(COPY_u8Pin*4));
						 }
		                 else if(COPY_u8Pin<=15)
						 {    COPY_u8Pin=COPY_u8Pin-8;
							 GPIO_PORTC_CRH &= (~((0b1111)<<(COPY_u8Pin*4)));
							 GPIO_PORTC_CRH |= ((COPY_u8Mode)<<(COPY_u8Pin*4));
						 }
						 break;
	}
}

/*   TO SET VALUE OF PINS IN PORTS IF IT IS OUTPUT */
void  MGPIO_voidSetPinValue(u8 COPY_u8Port,u8 COPY_u8Pin,u8 COPY_u8Value)
{    
	switch(COPY_u8Port)
	{
		case GPIO_PORTA: 
                          if(COPY_u8Value==GPIO_HIGH)                    //CHECK IF VALUE IS HIGH
						        SET_BIT(GPIO_PORTA_ODR,COPY_u8Pin);      //SET BIN 
                          else if (COPY_u8Value==GPIO_LOW)               //CHECK IF VALUE IS LOW
							    CLR_BIT(GPIO_PORTA_ODR,COPY_u8Pin);      //CLEAR BIN
						  break;
		case GPIO_PORTB:    
		                  if(COPY_u8Value==GPIO_HIGH)
						        SET_BIT(GPIO_PORTB_ODR,COPY_u8Pin); 
                          else if (COPY_u8Value==GPIO_LOW)
							    CLR_BIT(GPIO_PORTB_ODR,COPY_u8Pin);
						  break;
		case GPIO_PORTC:  
		                  if(COPY_u8Value==GPIO_HIGH)
						        SET_BIT(GPIO_PORTC_ODR,COPY_u8Pin); 
                          else if (COPY_u8Value==GPIO_LOW)
							    CLR_BIT(GPIO_PORTC_ODR,COPY_u8Pin);
						  break;
}
}
/*   TO SET VALUE OF PINS IN PORTS IF IT IS OUTPUT */
void  MGPIO_voidTogPinValue(u8 COPY_u8Port,u8 COPY_u8Pin)
{
	switch(COPY_u8Port)
	{
		case GPIO_PORTA:
						        TOG_BIT(GPIO_PORTA_ODR,COPY_u8Pin);      //Toggle BIN
						        break;
		case GPIO_PORTB:
		                	  TOG_BIT(GPIO_PORTB_ODR,COPY_u8Pin);
						  break;
		case GPIO_PORTC:
		                	  TOG_BIT(GPIO_PORTC_ODR,COPY_u8Pin);
						  break;
}
}
/*   TO GET VALUE OF PINS IN PORTS IF IT IS INPUT */
u8    MGPIO_u8GetPinValue(u8 COPY_u8Port,u8 COPY_u8Pin)
{
  u8 Local_u8Resualt = 0;
  switch(COPY_u8Port){
  case GPIO_PORTA:Local_u8Resualt = GET_BIT(GPIO_PORTA_IDR,COPY_u8Pin);   break;
  case GPIO_PORTB:Local_u8Resualt = GET_BIT(GPIO_PORTB_IDR,COPY_u8Pin);   break;
  case GPIO_PORTC: Local_u8Resualt =GET_BIT(GPIO_PORTC_IDR,COPY_u8Pin);   break;}
  return Local_u8Resualt ;
}

/*   TO SET VALUE OF  PORTS IF IT IS OUTPUT */
void  MGPIO_voidSetPortValue(u8 COPY_u8Port,u16 COPY_u16Value)
{
	switch(COPY_u8Port)
	{
		case GPIO_PORTA:
                GPIO_PORTA_ODR=COPY_u16Value ;
						  break;
		case GPIO_PORTB:
			   GPIO_PORTB_ODR=COPY_u16Value ;
						   break;
		case GPIO_PORTC:
			GPIO_PORTC_ODR=COPY_u16Value ;
							break;
}
}
