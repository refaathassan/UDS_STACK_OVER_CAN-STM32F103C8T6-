/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :23-12-2022                                                            */
/*           VERSION      :V02                                                                   */
/*************************************************************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"RCC_interface.h"
#include"RCC_private.h"
#include"RCC_config.h"


/* TO INTIATE THE CLOCK OF SYSTEM */
void RCC_voidIintSysClock(void)
{
	#if     RCC_CLOCK_TYPE    ==  RCC_HSE_CRYSTAL
                      RCC_CR    =0X00010000;        //ENABLE HSE WITH CRYSTAL CLOCK SOURCE
                      RCC_CFGR	=0X00000001;
					  
	#elif     RCC_CLOCK_TYPE    ==  RCC_HSE_RC
	                  RCC_CR    =0X00050000;       //ENABLE HSE WITH RC CLOCK SOURCE
					  RCC_CFGR	=0X00000001;
					  
	#elif     RCC_CLOCK_TYPE    ==  RCC_HSI
	                  RCC_CR    =0X00000081;      //ENABLE HSI CLOCK SOURCE with triming zero(triming by defualt 0x10)
					  RCC_CFGR	=0X00000000;
					  
	#elif     RCC_CLOCK_TYPE    ==  RCC_PLL
	                 #if RCC_PLL_INPUT     ==  RCC_PLL_HSI_DIV_2
					   RCC_CFGR	&=(~(0b1111<<RCC_CFGR_PLLMUL_BITS));  // mask pllmul bit
					   RCC_CFGR	|=((RCC_PLL_MUL_VAL-2)<<RCC_CFGR_PLLMUL_BITS);   // set nember to multiblucation
					   RCC_CR    =0X01000081;        // active pll and hsi 
                       RCC_CFGR	|=(0X2);			 // enable pll as source of clock 		   
					    
			         #elif RCC_PLL_INPUT   ==  RCC_PLL_HSE_CRYSTAL_DIV_2
					   RCC_CFGR	&=(~(0b1111<<RCC_CFGR_PLLMUL_BITS));
					   RCC_CFGR	|=((RCC_PLL_MUL_VAL-2)<<RCC_CFGR_PLLMUL_BITS);
					   RCC_CR    =0X01010000;
                       RCC_CFGR	|=(0X3<<16);					   
					   RCC_CFGR	|=(0X2);
					   
					   
			         #elif RCC_PLL_INPUT   ==  RCC_PLL_HSE_RC_DIV_2
					   RCC_CFGR	&=(~(0b1111<<RCC_CFGR_PLLMUL_BITS));
					   RCC_CFGR	|=((RCC_PLL_MUL_VAL-2)<<RCC_CFGR_PLLMUL_BITS);
					   RCC_CR    =0X01050000; 
					   RCC_CFGR	|=(0X3<<16);
					   RCC_CFGR	|=(0X2);
					   	
					 
	                 #elif RCC_PLL_INPUT   ==  RCC_PLL_HSE_CRYSTAL
					   RCC_CFGR	&=(~(0b1111<<RCC_CFGR_PLLMUL_BITS));
					   RCC_CFGR	|=((RCC_PLL_MUL_VAL-2)<<RCC_CFGR_PLLMUL_BITS);
					   RCC_CR    =0X01010000;
					   RCC_CFGR	|=(0X3<<16);
                       RCC_CFGR	|=(0X2);
					   						   

					   
					 #elif RCC_PLL_INPUT   ==  RCC_PLL_HSE_RC
					   RCC_CFGR	&=(~(0b1111<<RCC_CFGR_PLLMUL_BITS));
					   RCC_CFGR	|=((RCC_PLL_MUL_VAL-2)<<RCC_CFGR_PLLMUL_BITS);
					   RCC_CR    =0X01050000;
					   RCC_CFGR	|=(0X3<<16);
                       RCC_CFGR	|=(0X2);
					   
			         #else
			         #endif 
	#else
                      #error("please enter the correct type of clock ")		
	#endif
}


/*  TO ENABLE CLOCK TO SPECFICE PERIPHERAL */
void RCC_voidEnableClock(u8 Copy_u8BusId , u8 Copy_u8PerId){
	
	if(Copy_u8PerId<=31)
	{
		switch(Copy_u8BusId) 
		{
			case RCC_AHP  :    SET_BIT(RCC_AHBENR    ,Copy_u8PerId);      break;  // TO ENABLE PERIPHERAL IN AHP BUS
			case RCC_APB1 :    SET_BIT(RCC_APB1ENR   ,Copy_u8PerId);      break;  // TO ENABLE PERIPHERAL IN APB1 BUS
			case RCC_APB2 :    SET_BIT(RCC_APB2ENR   ,Copy_u8PerId);      break;  // TO ENABLE PERIPHERAL IN APB2 BUS
		}
		
	}
	else 
	{
		//Retrun Error
	}
	
	
/*  TO DISABLE CLOCK TO SPECFICE PERIPHERAL */	
}

void RCC_voidDisableClock(u8 Copy_u8BusId , u8 Copy_u8PerId){
	
	if(Copy_u8PerId<=31)
	{
		switch(Copy_u8BusId) 
		{
			case RCC_AHP  :    CLR_BIT(RCC_AHBENR    ,Copy_u8PerId);      break; // TO ENABLE PERIPHERAL IN AHP BUS
			case RCC_APB1 :    CLR_BIT(RCC_APB1ENR   ,Copy_u8PerId);      break; // TO ENABLE PERIPHERAL IN APB1 BUS
			case RCC_APB2 :    CLR_BIT(RCC_APB1ENR   ,Copy_u8PerId);      break; // TO ENABLE PERIPHERAL IN APB2 BUS
		}
		
	}
	else 
	{
		//Retrun Error
	}
	
	
	
}