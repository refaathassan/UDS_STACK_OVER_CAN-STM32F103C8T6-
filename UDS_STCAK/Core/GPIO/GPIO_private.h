/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :25-12-2022                                                            */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/
#ifndef       _GPIO_PRIVATE_H
#define       _GPIO_PRIVATE_H



/* PORTA REGISTERS  */
#define GPIO_PORTA_CRL         *((volatile u32*)0x40010800)   //TO CONTROL MODE OF PINS FORM 0 T0 7 IN PORTA
#define GPIO_PORTA_CRH         *((volatile u32*)0x40010804)   //TO CONTROL MODE OF PINS FORM 8 T0 15 IN PORTA
#define GPIO_PORTA_IDR         *((volatile u32*)0x40010808)   //TO GET INPUT FROM PINS IF IT INPUT MODE  IN PORTA
#define GPIO_PORTA_ODR         *((volatile u32*)0x4001080C)   // TO SET VALUE TO PIN IF IT OUTPUT MODE IN PORTA
#define GPIO_PORTA_BSRR        *((volatile u32*)0x40010810)
#define GPIO_PORTA_BRR         *((volatile u32*)0x40010814)


/* PORTB REGISTERS  */
#define GPIO_PORTB_CRL         *((volatile u32*)0x40010C00)
#define GPIO_PORTB_CRH         *((volatile u32*)0x40010C04)
#define GPIO_PORTB_IDR         *((volatile u32*)0x40010C08)
#define GPIO_PORTB_ODR         *((volatile u32*)0x40010C0C)
#define GPIO_PORTB_BSRR        *((volatile u32*)0x40010C10)
#define GPIO_PORTB_BRR         *((volatile u32*)0x40010C14)

/* PORTC REGISTERS  */
#define GPIO_PORTC_CRL         *((volatile u32*)0x40011000)
#define GPIO_PORTC_CRH         *((volatile u32*)0x40011004)
#define GPIO_PORTC_IDR         *((volatile u32*)0x40011008)
#define GPIO_PORTC_ODR         *((volatile u32*)0x4001100C)
#define GPIO_PORTC_BSRR        *((volatile u32*)0x40011010)
#define GPIO_PORTC_BRR         *((volatile u32*)0x40011014)
#endif
