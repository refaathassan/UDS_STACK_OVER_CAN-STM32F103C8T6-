/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :23-12-2022                                                            */
/*           VERSION      :V02                                                                   */
/*************************************************************************************************/

#ifndef       _RCC_PRIVATE_H
#define       _RCC_PRIVATE_H

/* Register description */
#define BASE_ADRESS 0x40021000
#define  RCC_CR            *((volatile u32*)(BASE_ADRESS+0x00))  //CONTROL THE CLOCK INTER TO PROCESSOR
#define  RCC_CFGR          *((volatile u32*)(BASE_ADRESS+0x04))
#define  RCC_CIR           *((volatile u32*)(BASE_ADRESS+0x08))
#define  RCC_APB2STR       *((volatile u32*)(BASE_ADRESS+0x0C))
#define  RCC_APB1STR       *((volatile u32*)(BASE_ADRESS+0x10))
#define  RCC_AHBENR        *((volatile u32*)(BASE_ADRESS+0x14))   //ENABLE IN AHB PROTOCAL
#define  RCC_APB2ENR       *((volatile u32*)(BASE_ADRESS+0x18))   //ENABLE IN APB1 PROTOCAL MAX SPEED 32MHZ
#define  RCC_APB1ENR       *((volatile u32*)(BASE_ADRESS+0x1C))   //ENABLE IN APB2 PROTOCAL MAX SPEED 72MHZ
#define  RCC_BDCR          *((volatile u32*)(BASE_ADRESS+0x20))
#define  RCC_CSR           *((volatile u32*)(BASE_ADRESS+0x24))

#define RCC_CFGR_PLLMUL_BITS   18                //PULLMUL NUMBER IN RCC_CFGR REGISTER  

/* CLOCK TYPES*/
#define      RCC_HSI                        0
#define      RCC_HSE_CRYSTAL                1
#define      RCC_HSE_RC                     2
#define      RCC_PLL                        3

/* PLL TYPES */
#define      RCC_PLL_HSI_DIV_2              0
#define      RCC_PLL_HSE_CRYSTAL_DIV_2      1
#define      RCC_PLL_HSE_RC_DIV_2           2
#define      RCC_PLL_HSE_CRYSTAL            3
#define      RCC_PLL_HSE_RC                 4



#endif
