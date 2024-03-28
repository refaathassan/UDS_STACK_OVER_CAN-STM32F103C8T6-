/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :23-12-2022                                                            */
/*           VERSION      :V02                                                                   */
/*************************************************************************************************/
#ifndef      _RCC_CONFIG_H
#define      _RCC_CONFIG_H

/* options is   :RCC_HSI
                 RCC_HSE_CRYSTAL
				 RCC_HSE_RC
                 RCC_PLL */
#define     RCC_CLOCK_TYPE        RCC_HSI


// NOTE :  confige that only you have choise PLL CLOCK SOURCE 
#if         RCC_CLOCK_TYPE   ==  RCC_PLL


/* PLL TYPES   : RCC_PLL_HSI_DIV_2              
				 RCC_PLL_HSE_CRYSTAL_DIV_2     
				 RCC_PLL_HSE_RC_DIV_2          
				 RCC_PLL_HSE_CRYSTAL           
				 RCC_PLL_HSE_RC    */             				 
#define     RCC_PLL_INPUT        RCC_PLL_HSI_DIV_2

/* options from 2 to 16  */
#define     RCC_PLL_MUL_VAL      2

#endif 


#endif
