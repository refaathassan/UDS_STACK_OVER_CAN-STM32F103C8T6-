/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :15-1-2023                                                              */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"USRT_interface.h"
#include"USRTM_interface.h"

//volatile static u8 * ptr1_1;
//volatile u8 * ptr11;

//void Call_Back(void);
void MUSARTM_voidInit(void)
{
	MUSRT1_voidInit();
	//MUSART1_u8RecieveChrAsys(ptr11);
	//MUSART1_u8RecieveAsys(Call_Back);
	MUSRT1_voidInterrputEnable();   // enable recieve with interrupt
}
STATUES MUSARTM_u8RecieveUDSDecode(volatile u8 *ptr, u8 len,volatile u8 *ptr_return)
{   u8 err_coun=0;
	for(u8 i=0,j=0;i<len-1;i+=2,j++)
	{
		if(ptr[i]>='0'&&ptr[i]<='9')
		{
			ptr_return[j]=(ptr[i]-((u8)'0'))<<(4);
		}
		else
		{
			switch(ptr[i])
			{
			case'A':
			case'a':
				ptr_return[j]=0xA<<4;
				break;
			case'B':
			case'b':
				ptr_return[j]=0xB<<4;
				break;
			case'C':
			case'c':
				ptr_return[j]=0xC<<4;
				break;
			case'D':
			case'd':
				ptr_return[j]=0xD<<4;
				break;
			case'E':
			case'e':
				ptr_return[j]=0xE<<4;
				break;
			case'F':
			case'f':
				ptr_return[j]=0xF<<4;
				break;
			default:
				err_coun++;
               break;
			}
		}
		if(ptr[i+1]>='0'&&ptr[i+1]<='9')
		{
			ptr_return[j]|=(ptr[i+1]-((u8)'0'));
		}
		else
		{
			switch(ptr[i+1])
			{
			case'A':
			case'a':
				ptr_return[j]|=0xA;
				break;
			case'B':
			case'b':
				ptr_return[j]|=0xB;
				break;
			case'C':
			case'c':
				ptr_return[j]|=0xC;
				break;
			case'D':
			case'd':
				ptr_return[j]|=0xD;
				break;
			case'E':
			case'e':
				ptr_return[j]|=0xE;
				break;
			case'F':
			case'f':
				ptr_return[j]|=0xF;
				break;
			default:
				err_coun++;
               break;
			}
		}
	}
	if(err_coun==0)
	{
		return FALSES;
	}
	else
	{
		return TRUES;
	}
}
STATUES MUSARTM_u8transmitUDSencode(volatile u8 *ptr, u8 len,volatile u8 *ptr_return)
{
	u8 err_coun=0;
	len=len*2;
		for(u8 i=0,j=0;j<len-1;i++,j+=2)
		{
			if((ptr[i]>>4)>=0&&(ptr[i]>>4)<=9)
			{
				ptr_return[j]=((ptr[i]>>4)+((u8)'0'));
			}
			else
			{
				switch((ptr[i]>>4))
				{
				case 0xA:
					ptr_return[j]='A';
					break;
				case 0xB:
					ptr_return[j]='B';
					break;
				case 0xC:
					ptr_return[j]='C';
					break;
				case 0xD:
					ptr_return[j]='D';
					break;
				case 0xE:
					ptr_return[j]='E';
					break;
				case 0xF:
					ptr_return[j]='F';
					break;
				default:
					err_coun++;
	               break;
				}
			}
			if((ptr[i]&0b00001111)>=0&&(ptr[i]&0b00001111)<=9)
			{
				ptr_return[j+1]=((ptr[i]&0b00001111)+((u8)'0'));
			}
			else
			{
				switch((ptr[i]&0b00001111))
				{
				case 0xA:
					ptr_return[j+1]='A';
					break;
				case 0xB:
					ptr_return[j+1]='B';
					break;
				case 0xC:
					ptr_return[j+1]='C';
					break;
				case 0xD:
					ptr_return[j+1]='D';
					break;
				case 0xE:
					ptr_return[j+1]='E';
					break;
				case 0xF:
					ptr_return[j+1]='F';
					break;
				default:
					err_coun++;
	               break;
				}
			}
		}
		if(err_coun==0)
		{
			return FALSES;
		}
		else
		{
			return TRUES;
		}
}
void MUSARTM_u8RecieveUDSAsys(volatile u8 *ptr,volatile u8* len,volatile u8* flag )
{
	MUSART1_u8RecieveUDSAsys(ptr,len,flag);

}
void MUSARTM_TransmitUDSencode(volatile u8 *ptr, u8 len)
{
	 for(u8 i=0;i<len;i++)
	 {
	 MUSRT1_voidTransimtChr((u8)ptr[i]);
	 }
	 MUSRT1_voidTransimtChr('\n');
}

//void Call_Back(void)
//{
//
//}
