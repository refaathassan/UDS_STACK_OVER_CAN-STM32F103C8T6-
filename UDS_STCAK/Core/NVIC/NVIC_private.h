/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :29-12-2022                                                            */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/
#ifndef  _NVIC_PRIVATE_H
#define  _NVIC_PRIVATE_H


#define  BASE_ADDRESSES            0xE000E100


#define  NVIC_ISER0                *((volatile u32 *)(BASE_ADDRESSES))       //ENABLE INTERRUPTS FROM 0 T0 31
#define  NVIC_ISER1                *((volatile u32 *)(BASE_ADDRESSES+0x04))  //ENABLE INTERRUPTS FROM 32 T0 63
#define  NVIC_ICER0                *((volatile u32 *)(BASE_ADDRESSES+0x80))  //DISABLE INTERRUPTS FROM 0 T0 31
#define  NVIC_ICER1                *((volatile u32 *)(BASE_ADDRESSES+0x84))  //DISABLE INTERRUPTS FROM 32 T0 63
#define  NVIC_ISPR0                *((volatile u32 *)(BASE_ADDRESSES+0x100))  //TO SET PENDING FROM 0 T0 31
#define  NVIC_ISPR1                *((volatile u32 *)(BASE_ADDRESSES+0x104))  //TO SET PENDING FROM 32 T0 63
#define  NVIC_ICPR0                *((volatile u32 *)(BASE_ADDRESSES+0x180))  //TO CLEAR  PENDING FROM 0 T0 31
#define  NVIC_ICPR1                *((volatile u32 *)(BASE_ADDRESSES+0x184))  //TO CLEAR PENDING FROM 32 T0 63
#define  NVIC_IABR0                *((volatile u32 *)(BASE_ADDRESSES+0x200))  //TO know if active or not  FROM 01 T0 31
#define  NVIC_IABR1                *((volatile u32 *)(BASE_ADDRESSES+0x204))  //TO know if active or not 32 T0 63

#define  NVIC_IPR                  ((volatile  u8 *)(BASE_ADDRESSES+0x300)) /*to put proirity of interrupt in 4-bit msb
                                                                              this register active by byte */
																			  
#define  SCB_AIRCR                 *((volatile  u32 *)0xE000ED0C ) //TO SAY THE NUMBER OF GROUPS AND SUBGROUPS 



#endif
