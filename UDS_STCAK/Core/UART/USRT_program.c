/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :15-1-2023                                                              */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"RCC_interface.h"
#include"GPIO_interfac.h"
#include"nvic_interface.h"
#include"USRT_interface.h"
#include"USRT_private.h"
#include"USRT_config.h"
#include"interface.h"
volatile static u8 * ptr1;
volatile static u8 * ptr1_1;
volatile static u8  buffer[50]={0};
volatile static u8 *flag_1=0;
volatile static u8 * len_1;
volatile static u16 * ptr2;
void (*FUN_1)(void);
/*INITIATE USRT  */
static u8 AsciToHex(u8 Copy_u8Asci)
{
	u8 Result;
	if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )
	{
		Result = Copy_u8Asci - 48;
	}

	else
	{
		Result = Copy_u8Asci - 55;
	}

	return Result;
}
void MUSRT1_voidInit(void)
{

	RCC_voidEnableClock(RCC_APB2, 14);   //enable USRT clock
	MGPIO_voidSetPinDirection(  GPIO_PORTA , PIN9 , OUTPUT_SPEED_10MHZ_AF_PP);  //TX AS OUTPUT
	MGPIO_voidSetPinDirection(  GPIO_PORTA , PIN10 ,INPUT_POLL_UP_DOWN);	    // RX AS INPUT
	MGPIO_voidSetPinValue(GPIO_PORTA, PIN10,GPIO_HIGH);  //make rx as pull up
    /*BUAD RATE IS 9600*/  
    USRT1->BRR=0X341;
    /*TO ENABLE TRANSIMT DATA*/
   SET_BIT(USRT1->CR1,3);
   /*TO ENABLE RECIEVE DATA*/
   SET_BIT(USRT1->CR1,2);
   /*TO ENABLE USRT */
    SET_BIT(USRT1->CR1,13);
	/*CLEAR STATE REGISTER*/
	USRT1->SR=0X00C0;
}
void MUSRT2_voidInit(void)
{

    /*BUAD RATE IS 9600*/
    USRT2->BRR=0X341;
    /*TO ENABLE TRANSIMT DATA*/
   SET_BIT(USRT2->CR1,3);
   /*TO ENABLE RECIEVE DATA*/
   SET_BIT(USRT2->CR1,2);
   /*TO ENABLE USRT */
    SET_BIT(USRT2->CR1,13);
	/*CLEAR STATE REGISTER*/
	USRT2->SR=0X00C0;
}
void MUSRT1_voidInterrputEnable(void)
{
	MNVIC_voidEnableInterrupt(37);
	//CLR_BIT(USRT1->SR,5);
	//CLR_BIT(USRT1->SR,6);
	 //SET_BIT(USRT1->CR1,6);  //ENABLE TRANSMIT INTERRUPT
	 SET_BIT(USRT1->CR1,5);  // ENABLE RX INTERRUPT
}
void MUSRT2_voidInterrputEnable(void)
{
	MNVIC_voidEnableInterrupt(38);
	CLR_BIT(USRT2->SR,5);
	CLR_BIT(USRT2->SR,6);
	 //SET_BIT(USRT1->CR1,6);  //ENABLE TRANSMIT INTERRUPT
	 SET_BIT(USRT2->CR1,5);  // ENABLE RX INTERRUPT
}
void MUSRT1_voidInterrputDisable(void)
{
	 CLR_BIT(USRT1->CR1,6);  //DISABLE TRANSMIT INTERRUPT
	 CLR_BIT(USRT1->CR1,5);  // DISABLE RX INTERRUPT
	 MNVIC_voidDisableInterrupt(38);
}
void MUSRT2_voidInterrputDisable(void)
{
	 CLR_BIT(USRT2->CR1,6);  //DISABLE TRANSMIT INTERRUPT
	 CLR_BIT(USRT2->CR1,5);  // DISABLE RX INTERRUPT
	 MNVIC_voidDisableInterrupt(37);
}

/*TO SEND char data  */
void  MUSRT1_voidTransimtChr(u8 COPY_u8Data)  
    {
    CLR_BIT(USRT1->SR,6);
	USRT1 -> DR = COPY_u8Data ;

	while( GET_BIT( USRT1 -> SR , 6 ) == 0 );

}
void  MUSRT2_voidTransimtChr(u8 COPY_u8Data)
    {
    CLR_BIT(USRT2->SR,6);
	USRT2 -> DR = COPY_u8Data ;

	while( GET_BIT( USRT2 -> SR , 6 ) == 0 );

}
/*TO SEND  string data  */
void  MUSRT1_voidTransimtString(u8 *Ptr_u8Data)
    {

    while(*Ptr_u8Data!='\0'){
	CLR_BIT( USRT1 -> SR , 6 );
	USRT1 -> DR = *Ptr_u8Data;
	while(GET_BIT(USRT1->SR,6)== 0);
    
	Ptr_u8Data++;
   }
   

}

/*TO RECIEVED data*/
u8 MUSART1_u8RecieveChr( void ){

	u8  Loc_u8Data  = 0 ;

	//CLR_BIT(USRT1->SR,5);

	while(GET_BIT(USRT1->SR,5)==0);
	Loc_u8Data=USRT1->DR;
	//CLR_BIT(USRT1->SR,5);
	return Loc_u8Data;

}

u8 MUSART2_u8RecieveChr( void ){

	u8  Loc_u8Data  = 0 ;

	//CLR_BIT(USRT1->SR,5);

	while(GET_BIT(USRT2->SR,5)==0);
	Loc_u8Data=USRT2->DR;
	//CLR_BIT(USRT1->SR,5);
	return Loc_u8Data;

}

volatile ERROR_STATUES MUSART1_u8RecieveHex( volatile u16 * ptr)
{  u8 i=0;
 ERROR_STATUES Error_Staue=  ERROR_OCCUR;

     u8* ptr_copy=(u8*)ptr;
     u8 low_digit=0;
     u8 high_digit=0;
	for(i=0;i<16;i++)
	{
	//CLR_BIT(USRT1->SR,5);
	while((GET_BIT(USRT1->SR,5)==0));
	high_digit=AsciToHex(USRT1->DR);
	//CLR_BIT(USRT1->SR,5);
	while((GET_BIT(USRT1->SR,5)==0));
	low_digit=AsciToHex(USRT1->DR);
	*ptr_copy=(high_digit<<4)|low_digit;
	}
	if(i==16)
	{
		Error_Staue =NO_ERROR;
	}
	return Error_Staue;
}

//void MUSART1_u8RecieveAsys(void (FUN)(void ))
//{
//
//	FUN_1=FUN;
//	//
//}
void MUSART1_u8RecieveUDSAsys(volatile u8 *ptr,volatile u8* len,volatile u8* flag )
{
ptr1_1=ptr;
len_1=len;
flag_1=flag;

}
void MUSART1_u8RecieveChrAsys(volatile u8 * ptt)
{
	ptr1=ptt;
}


void MUSART2_u8RecieveChrAsys(volatile u16 *ptr ){

ptr2=ptr;
	//
}

void USART1_IRQHandler(void)
{
	//u32 i=0;
	//MGPIO_voidTogPinValue(GPIO_PORTA, PIN0);
//	while(i<500000)i++;
//	i=0;
	//static u8 count=0;
	//*ptr1=;
	static u8 length=0;
    if(USRT1->DR!=' ')
    {
	buffer[length]=USRT1->DR;
	length++;
	//count++;
    }
    else
    {
    	for(u8 i=0;i<length;i++)
    	{
    		ptr1_1[i]=buffer[i];
    	}
    	*len_1=length;
    	length=0;
    	*flag_1=1;
    }

	 CLR_BIT(USRT1->SR,5);
	 CLR_BIT(USRT1->SR,6);

//	MGPIO_voidTogPinValue(GPIO_PORTA, PIN0);
//	while(i<500000)i++;
}

void USART2_IRQHandler(void)
{
	//MGPIO_voidTogPinValue(GPIO_PORTA, PIN1);
	//u32 i=0;
	//MGPIO_voidTogPinValue(GPIO_PORTA, PIN0);
//	while(i<500000)i++;
//	i=0;

	*ptr2=USRT2->DR;
	CLR_BIT(USRT1->SR,5);
	CLR_BIT(USRT1->SR,6);

//	MGPIO_voidTogPinValue(GPIO_PORTA, PIN0);
//	while(i<500000)i++;
}

