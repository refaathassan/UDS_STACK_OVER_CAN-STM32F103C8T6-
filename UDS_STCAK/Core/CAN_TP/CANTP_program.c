#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interfac.h"
#include"CAN_interface.h"
#include "NVIC_interface.h"

#include "USRT_interface.h"
#include "CANTP_interface.h"
#include "CANTP_private.h"
#include "CANTP_config.h"

u8 ID_frame=10;

volatile static u16 flag_ack= 0;

/* global counter used to track data in case of data received more than 8 bytes*/
static u8 tp_global_counter = 0;
/* global index used to track data in case of data received more than 8 bytes*/
static u8 tp_current_ind = 0;
/**/
static u8 tp_cons_ind_1 = 0;

volatile static u16 length = 0;
/* global data length used in case of data sent or received more than 8 bytes */
volatile static s16 len_temp=0;
/* Global Data array to be sent using CAN (TP buffer)*/
static u8 buffer[8]={0};
/*  Global pointer to data length to be checked for UDS */
volatile static u8 * ptr_1;
/*  Global pointer to flag to be checked for UDS */
volatile static u8 * ptr_2;

/* Global pointer to function to be called from UDS */
static Statue_2_t(*fun_1)(void);
/*  Global pointer to data (UDS buffer ) */
volatile u8* gdata_1;
/*  Global pointer to data received from (CAN buffer) */
volatile u8* gdata_2;
/**
  * @brief  This function to be done when CAN raise interrupt flag
  * @retval NULL
  */
void CANTP_RecievAsy(void);
/**
  * @brief  This function to be called when received interrupt flag from CAN
  * @param  (fun) pointer to Function
  * @retval NULL
  */
void CANTP_voidCallBack(Statue_2_t(*fun)(void))
{
	/* set local pointer to function to global pointer to function in TP */
	fun_1=fun;

}
/**
  * @brief  This function request flag for UDS to start processing
  * @param  (cpy_ptr) pointer to flag
  * @retval NULL
  */
void CANTP_RxFlag(volatile u8 * cpy_ptr)
{
	/* set local pointer flag to global pointer flag in TP */
	ptr_2=cpy_ptr;
}

void CANTP_RxAsy(volatile u8 **DATA,volatile u8 *ptr )
{
	/* make Global pointer reference to data received from CAN*/
	gdata_2=*DATA;
	/*  */
	ptr_1=ptr;

}

/**
  * @brief  This function Init CAN , filter configuration , interrupt Activation , start communication
  * @retval NULL
  */
void CANTP_voidInit(void)
{
	/* CAN init */
	CAN_voidInit();
	/* CAN Filter set */
	CAN_FilterConfig();
	/* callback function to be done when CAN raise interrupt flag */
	CAN_voidCallBack(CANTP_RecievAsy);
	/* interrupt Activation */
	CAN_Interrupt();
	/* CAN Start */
	CAN_voidStart();
}

/**
  * @brief  This function Send data using CAN protocol
  * @param  (packet) pointer to Data to be sent
  * @param  (len) Length of Data to be sent
  * @retval NULL
  */
void CANTP_SendPacket(volatile u8* packet,volatile s8 len)
{
	flag_ack=0;
	u16 PCI=0;
	s8 len_copy=len;
	if(len_copy<=7)
	{
		buffer[0]=len_copy;
		for(u8 i=0;i<len_copy;i++)
		{
			buffer[i+1]=packet[i];
		}
		CAN_TX(buffer,len_copy+1,0x200);
	}
	else if(len_copy>7)
	{
		tp_cons_ind_1=0;
		PCI=1<<12;
		PCI|=len_copy;
		buffer[0]=(u8)(PCI>>8);
		buffer[1]=(u8)PCI;
		for(u8 i=0;i<6;i++)
		{
			buffer[i+2]=packet[i];
		}
		CAN_TX(buffer,8,0x200);
		len_copy-=6;
		tp_cons_ind_1=6;
		while(len_copy>0)
		{
			buffer[0]=0x21;
			for(u8 i=0;(i<len_copy)&&(i<7);i++)
			{

				buffer[i+1]=packet[tp_cons_ind_1];
				tp_cons_ind_1++;
			}
			if(len_copy>7)
			{
				CAN_TX(buffer,8,0x200);
			}
			else
			{
				CAN_TX(buffer,len_copy+1,0x200);
			}
			len_copy-=7;
		}


	}


}


/**
  * @brief  This function to be done when CAN raise interrupt flag
  * @retval NULL
  */
void CANTP_RecievAsy(void)
{
	Statue_2_t   check_buff=NO;

	 CAN_RxAsy(&gdata_1);
	 check_buff=fun_1();

	 if(check_buff==OK)
	 {
		 /* get frame type PCI first byte from data received from CAN */
		ID_frame=(gdata_1[0]>>4);

		/* Check if you still receiving data or not*/
		if(flag_ack==0)
		{

		/* Check for frame type*/
		 switch(ID_frame)
		 {
		 case 0: // Single Frame
			 /* Get data length */
			 length=0x0F&gdata_1[0];
			 /*  set Global pointer to data length from data received from CAN */
			 *ptr_1=length;
			 /* check if data length is less than or equal 8*/
			  if(length<=8)
			  {
				  for(u8 i=0;i<length;i++)
				  {
					  gdata_2[i]=gdata_1[i+1];
					  tp_global_counter++;
				  }
			  }

			 break;
		 case 1: // First Frame
			 length=0;
			 length = ((u16)(0x0F&gdata_1[0]))<<8;
			 length |= gdata_1[1];
			 *ptr_1=length;
			 len_temp=length;
			 for(u8 j=2,i=tp_current_ind;j<8;i++,j++)
			 {
				 gdata_2[i]=gdata_1[j];
				 tp_global_counter++;
				 tp_current_ind++;
				 len_temp--;
			 }

		 	 break;
		 case 2:
			 for(u8 j=1,i=tp_current_ind;(j<8)&&(len_temp>0);i++,j++)
			 {
				 gdata_2[i]=gdata_1[j];
				 tp_global_counter++;
				 tp_current_ind++;
				 len_temp--;
			 }
		 	     	 break;
		 case 3:
		 			 break;
		 default:
			         break;

		 }
		 if(length==tp_global_counter)
		 {
			 *ptr_2=1;
			 tp_global_counter=0;
			 tp_current_ind=0;
			 ID_frame=10;
			 flag_ack=1;

		 }
		}

	}

}

