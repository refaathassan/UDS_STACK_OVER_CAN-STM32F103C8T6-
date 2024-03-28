/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :30-12-2022                                                            */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"AFIO_interface.h"
#include"AFIO_private.h"
#include"AFIO_config.h"


/*TO config  what is the port you want to enable in line
    COPY_u8PORT: PORTA
                 PORTB
                 PORTC	*/			 
void MAFIO_AFIOLineConfig(u8 COPY_u8Line,u8 COPY_u8PORT)
{
	u8 Local_IndexLine = 0;
	if(COPY_u8Line<=3)
	{
		Local_IndexLine = 0;
	}
	else if(COPY_u8Line<=7)
	{
		Local_IndexLine = 1;
		COPY_u8Line-=4;
	}
	else if(COPY_u8Line<=11)
	{
		Local_IndexLine = 2;
		COPY_u8Line-=8;
	}
	else if(COPY_u8Line<=15)
	{
		Local_IndexLine = 3;
		COPY_u8Line-=11;
	}
	AFIO ->EXTICR[Local_IndexLine] &=(~((0b1111)<<(COPY_u8Line*4)));
	AFIO ->EXTICR[Local_IndexLine] |=(COPY_u8PORT<<(COPY_u8Line*4)); 
}
