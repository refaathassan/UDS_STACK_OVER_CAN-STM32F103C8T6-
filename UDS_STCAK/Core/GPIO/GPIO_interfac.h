/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :25-12-2022                                                            */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/
#include"STD_TYPES.h"
#ifndef  _GPIO_INTERFAC_H
#define  _GPIO_INTERFAC_H


#define GPIO_LOW                     0
#define GPIO_HIGH                    1
/*   PORT NAMES    */ 
#define GPIO_PORTA                	 0
#define GPIO_PORTB                	 1
#define GPIO_PORTC                   2

/*  PIN NUMBERS   */
#define PIN0                      	 0
#define PIN1                      	 1
#define PIN2            	      	 2
#define PIN3            		  	 3
#define PIN4            		  	 4
#define PIN5            		  	 5	
#define PIN6            		  	 6
#define PIN7            		  	 7
#define PIN8            		     8
#define PIN9            		     9
#define PIN10           		     10
#define PIN11           		 	 11
#define PIN12           			 12
#define PIN13           		 	 13
#define PIN14           		     14
#define PIN15           		     15

/*  types of mode and config */ 

#define INPUT_ANALOG                 0b0000
#define INPUT_FLOATING               0b0100
#define INPUT_POLL_UP_DOWN           0b1000

                 
#define OUTPUT_SPEED_10MHZ_PP        0b0001
#define OUTPUT_SPEED_10MHZ_OD        0b0101
#define OUTPUT_SPEED_10MHZ_AF_PP     0b1001
#define OUTPUT_SPEED_10MHZ_AF_OD     0b1101

#define OUTPUT_SPEED_2MHZ_PP         0b0010
#define OUTPUT_SPEED_2MHZ_OD         0b0110
#define OUTPUT_SPEED_2MHZ_AF_PP      0b1010
#define OUTPUT_SPEED_2MHZ_AF_OD      0b1110


#define OUTPUT_SPEED_50MHZ_PP        0b0011
#define OUTPUT_SPEED_50MHZ_OD        0b0111
#define OUTPUT_SPEED_50MHZ_AF_PP     0b1011
#define OUTPUT_SPEED_50MHZ_AF_OD     0b1111
 

/*   TO SET MODE OF PINS IN PORTS */
void  MGPIO_voidSetPinDirection(u8 COPY_u8Port,u8 COPY_u8Pin,u8 COPY_u8Mode);

/*   TO SET VALUE OF PINS IN PORTS IF IT IS OUTPUT */
void  MGPIO_voidSetPinValue(u8 COPY_u8Port,u8 COPY_u8Pin,u8 COPY_u8Value);

/*   TO GET VALUE OF PINS IN PORTS IF IT IS INPUT */
u8    MGPIO_u8GetPinValue(u8 COPY_u8Port,u8 COPY_u8Pin);


void  MGPIO_voidTogPinValue(u8 COPY_u8Port,u8 COPY_u8Pin);
/*   TO SET VALUE OF  PORTS IF IT IS OUTPUT */
void  MGPIO_voidSetPortValue(u8 COPY_u8Port,u16 COPY_u16Value);


#endif
