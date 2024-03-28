#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include"CANTP_interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "UDSM_interface.h"
#include "UDSM_private.h"
#include "UDSM_config.h"


/*structure of packet to decode the frame in it
 * decode four possibilities of frame has only service or service and sub service
 * or service and data or service, sub service and data */
Packet_Handler_t My_Packet[4];

/*pointer to data in my system*/
u8 data_1[3]={0X10,0x11,0x12};
u8 data_2[10]={0X20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29};

/*flag indicate to timer to start count when we is not in default session*/
u8  Non_defualt_time_start_count_Flag=0;
/*flag indicate to timer to start count when receive new request
 * to calculate the p2 time */
u8  p2_time_start_count_Flag=0;
/*negative flag to indicate the response is negative  */
u8  nig_Flag=0;

/*indicate to the UDS is busy */
u8  processing_Flag=0;
/*flag indicate to timer to start count when open Security level
 * to calculate the time out of security session */
u8  Security_time_start_count_Flag=0;

/*UDS buffer*/
volatile u8 CAN_Package[20]={0};
/* length of received request*/
volatile u8 CAN_Package_len=0;
/*pointer to point to UDS buffer*/
volatile u8 *ptr_packet=CAN_Package;

/*counters to time out in s3, p2, and security level*/
volatile static u16 S3_time_counter=0;
volatile  static u16 p2_Timeout_counter=0;
volatile  static u16 Security_Level_Timeout_counter=0;

/*current statues of packet encode and decode*/
PacketRxState_t PacketState_de=SID;
PacketRxState_t PacketState_en=SID;

/*current statues session, security and
 * current packet processing to encode the same packet*/
Session_Status_t Current_Session=Defualt;
Security_Levels_t Current_Level=Multi_Level;
Service_char_t   Package_Target=SID_S;

/*function that decide the buffer is empty or full
 * will called when receive request */
Statue_2_t UDSM_voidCheckBuffer(void);


/*functions handle decode the stream data that received from CANTP
 * to frame that UDS can process it  */
STATUES Packet_SID_De( u8* const Data);
STATUES Packet_SUB_ID_De( u8* const Data);
STATUES Packet_DATA_De ( u8* const Data);

/*functions handle encode the processed packet to
 *  stream data to send to CANTP */
STATUES Packet_SID_En( u8* const Data);
STATUES Packet_SUB_ID_En( u8* const Data);
STATUES Packet_DATA_En ( u8* const Data);


/*function will called every timer ISR to handle times in UDS*/
void UDSM_voidTiming(void);

/*function to rest statues of decode and encode of frame */
void Packet_SmReset_de(void);
void Packet_SmReset_en(void);

/*to generate random key */
static u8 generateRandomByte(void);

/*services handlers*/
STATUES Read_ID( Packet_Handler_t* const Data);
STATUES Session_Control_fun(Packet_Handler_t* const Data);
STATUES Tester_Represent( Packet_Handler_t* const Data);
STATUES Write_ID( Packet_Handler_t* const Data);
STATUES Security_Access_fun( Packet_Handler_t* const Data);

/*array of structure has each segment and her decoder handler*/
static PacketSm_t const PacketSm_de[]=
{
 {SID, Packet_SID_De },
 {SUB_SID, Packet_SUB_ID_De},
 {DATA_SEG, Packet_DATA_De},
};

/*array of structure has each segment and her encoder handler*/
static PacketSm_t const PacketSm_en[]=
{
 {SID, Packet_SID_En },
 {SUB_SID, Packet_SUB_ID_En},
 {DATA_SEG, Packet_DATA_En},
};

/*table of services to call it directly without
 *  make switch in it when receive request*/
static Commands_t const Commands_Table[]=
{
		     {Reserved0,Non_Service, NULL},
			 {Reserved1,Non_Service, NULL},
			 {Reserved2,Non_Service, NULL},
			 {Reserved3,Non_Service, NULL},
			 {Reserved4,Non_Service, NULL},
			 {Reserved5,Non_Service, NULL},
			 {Reserved6,Non_Service, NULL},
			 {Reserved7,Non_Service, NULL},
			 {Reserved8,Non_Service, NULL},
			 {Reserved9,Non_Service, NULL},
			 {ReservedA,Non_Service,NULL},
			 {ReservedB,Non_Service, NULL},
			 {ReservedC,Non_Service, NULL},
			 {ReservedD,Non_Service, NULL},
			 {ReservedE,Non_Service, NULL},
			 {ReservedF,Non_Service, NULL},
			 {Session_Control,SID_SUB,Session_Control_fun},
			 {Reserved11,Non_Service,NULL},
			 {Reserved12,Non_Service,NULL},
			 {Reserved13,Non_Service,NULL},
			 {Reserved14,Non_Service,NULL},
			 {Reserved15,Non_Service,NULL},
			 {Reserved16,Non_Service,NULL},
			 {Reserved17,Non_Service,NULL},
			 {Reserved18,Non_Service,NULL},
			 {Reserved19,Non_Service,NULL},
			 {Reserved1A,Non_Service,NULL},
			 {Reserved1B,Non_Service,NULL},
			 {Reserved1C,Non_Service,NULL},
			 {Reserved1D,Non_Service,NULL},
			 {Reserved1E,Non_Service,NULL},
			 {Reserved1F,Non_Service,NULL},
			 {Reserved20,Non_Service,NULL},
			 {Reserved21,Non_Service,NULL},
			 {Read,SID_DATA,Read_ID},
			 {Reserved23,Non_Service, NULL},
			 {Reserved24,Non_Service, NULL},
			 {Reserved25,Non_Service,NULL},
			 {Reserved26,Non_Service,NULL},
			 {Security_Access,SID_SUB_DATA,Security_Access_fun},
			 {Reserved28,Non_Service,NULL},
			 {Reserved29,Non_Service,NULL},
			 {Reserved2A,Non_Service,NULL},
			 {Reserved2B,Non_Service,NULL},
			 {Reserved2C,Non_Service,NULL},
			 {Reserved2D,Non_Service,NULL},
			 {Write,SID_DATA,Write_ID},
			 {Reserved2F,Non_Service,NULL},
			 {Reserved30,Non_Service,NULL},
			 {Reserved31,Non_Service,NULL},
			 {Reserved32,Non_Service,NULL},
			 {Reserved33,Non_Service,NULL},
			 {Reserved34,Non_Service,NULL},
			 {Reserved35,Non_Service,NULL},
			 {Reserved36,Non_Service,NULL},
			 {Reserved37,Non_Service,NULL},
			 {Reserved38,Non_Service,NULL},
			 {Reserved39,Non_Service,NULL},
			 {Reserved3A,Non_Service,NULL},
			 {Reserved3B,Non_Service,NULL},
			 {Reserved3C,Non_Service,NULL},
			 {Reserved3D,Non_Service,NULL},
			 {Test_Represent,SID_S,Tester_Represent},
			 {Reserved3F,Non_Service,NULL}
};

/*create data to read and write by identifier */
static Data_By_Id const Data_Table[]={
		{0xF3A0,(u8*)data_1,3,DATA_WR_R,Multi_Session,Extened,Multi_Level,Level1},
		{0xF3A1,(u8*)data_2,10,DATA_WR_R,Multi_Session,Extened,Multi_Level,Level1}
};
/*length of data table*/
u8 Data_Table_len=2;




/*function to inite the UDS*/
void UDSM_voidInit(void)
{
	/*initialise CANTP*/
	CANTP_voidInit();
	/*INIATE SYSTICK*/
	MSYSTICK_voidInit();
	//FUNCTION TO CALL IN TIMER ISR
    MSYSTICK_voidCallBack(UDSM_voidTiming);
    //make timer interrupt every 1MS
    MSYSTICK_voidDelay(1000);
    /*CALL BACK Function to provide buffer pointer to CANTP*/
    CANTP_voidCallBack(UDSM_voidCheckBuffer);


}
/*Flag will set when receive new request*/
void UDSM_voidRecieveAsy(volatile u8* ptr)
{
	CANTP_RxFlag(ptr);
}

/*function that will make decode to the stream data to packet can process it */
STATUES Packet_DecodeSm(u8* const Data)
{
	STATUES PacketSmResult = FALSE;//return value will set true when decode correctly
	while(PacketState_de!=PACKET_STATE_END) //stop when rich to end of frame
	{
	 PacketSmResult = (PacketSm_de[PacketState_de].Implemention)(Data); //call the handler
	 if(PacketSmResult==TRUE) //if the previous step completed correctly step to next step
	 {
		 PacketState_de++;
	 }
	 /*reset if the previous step not completed  */
	 else
	 {
		 Packet_SmReset_de();
		 break;
	 }
	}
	Packet_SmReset_de();
	 return PacketSmResult;
}

STATUES Packet_encodeSm(u8* const Data)
{
 	STATUES PacketSmResult = FALSE;//return value will set true when encode correctly
	while(PacketState_en!=PACKET_STATE_END)//stop when rich to end of frame
	{
	 PacketSmResult = (PacketSm_en[PacketState_en].Implemention)(Data);//call the handler
	 if(PacketSmResult==TRUE)//if the previous step completed correctly step to next step
	 {
		 PacketState_en++;
	 }
	 /*reset if the previous step not completed  */
	 else
	 {
		 Packet_SmReset_en();
		 break;
	 }
	}
	/*reset if  completed  decode */
	Packet_SmReset_en();
	 return PacketSmResult;
}



STATUES Packet_Process(Packet_Handler_t* const Data)
{
	STATUES PacketResult = FALSE;//return value will set true when process correctly
	if(Commands_Table[Data[0].SID].Implemention!=NULL&&Data[0].SID<0x40)
	{
		Package_Target=Commands_Table[Data[0].SID].Decode; //choice the correct packet
		/*call the handler and pass the correct packet*/
		PacketResult = (Commands_Table[Data[0].SID].Implemention)(&Data[Commands_Table[Data[0].SID].Decode]);
	}
	/*send negative response the service not supported if the service not founded*/
	else
	{
		CAN_Package[0]=0x7F;
		CAN_Package[1]=Data[0].SID;
		CAN_Package[2]=SERVICE_NOT_SUPPORTED;
		CAN_Package_len=3;
		nig_Flag=1;
	}
	//make it trues after complete process
	PacketResult=TRUE;
	return PacketResult;

}
//the main fun in UDS
void UDSM_voidResponse(void)
{
	processing_Flag=1; //Flag indicate to UDS is busy
	p2_time_start_count_Flag=1; //flag indicate to the p2 time is started
	STATUES result_Dec=FALSE; //variable to hold to decode result is completed or not
	STATUES result_Pro=FALSE; //variable to hold to  decode result is completed or not
	STATUES result_En=FALSE;  //variable to hold to encode result is completed or not
/*implement the decoding */
	result_Dec=Packet_DecodeSm((u8* const) CAN_Package);
	/*if decoding successful completed  implement the processing */
	if(result_Dec==TRUE)
	{
		result_Pro=Packet_Process(My_Packet);
		/*if processing successful completed  implement the encoding */
		if(result_Pro==TRUE)
		{
			result_En=Packet_encodeSm((u8* const) CAN_Package);
			/*if encoding completed and it is positive response send the packet*/
			if(result_En==TRUE&&nig_Flag==0)
			{
				CANTP_SendPacket(CAN_Package,(s8)CAN_Package_len);

			}
			else
			{

			}
		}
	}
	/*clear the buffer*/
	for(u8 i=0;i<20;i++)
	{
		CAN_Package[i]=0;
	}
	/*reset negative flag*/
	nig_Flag=0;

	processing_Flag=0;
}
/*service id decode handler*/
STATUES Packet_SID_De( u8* const Data)
{
	STATUES Result = FALSE;
	My_Packet[0].SID=Data[0];
	My_Packet[1].SID=Data[0];
	My_Packet[2].SID=Data[0];
	My_Packet[3].SID=Data[0];
	Result = TRUE;
	return Result;
}
/*sub service id decode handler*/
STATUES Packet_SUB_ID_De( u8* const Data)
{
	STATUES Result = FALSE;
	if(CAN_Package_len>=2)
	{
		My_Packet[0].SUB_SID=0xFF;
		My_Packet[1].SUB_SID=Data[1];
		My_Packet[2].SUB_SID=0xFF;
		My_Packet[3].SUB_SID=Data[1];

	}

	Result = TRUE;
	return Result;
}
/*data id decode handler*/
STATUES Packet_DATA_De( u8* const Data)
{
		STATUES Result = FALSE;
		if(CAN_Package_len>=3)
		{

			for(u8 i=0;i<CAN_Package_len-1;i++)
			{
				My_Packet[2].DATA_SEG[i]=Data[i+1];
			}
			for(u8 i=0;i<CAN_Package_len-2;i++)
			{
				My_Packet[3].DATA_SEG[i]=Data[i+2];
			}
		}
		else
		{

		}

	Result = TRUE;
	return Result;
}
/*service id encode handler*/
STATUES Packet_SID_En( u8* const Data)
{
	STATUES Result = FALSE;
	Data[0]=My_Packet[Package_Target].SID;
	Result = TRUE;
	return Result;
}
/*sub service id encode handler*/
STATUES Packet_SUB_ID_En( u8* const Data)
{
	STATUES Result = FALSE;

	if(Package_Target==SID_SUB)
	{
		Data[1]=My_Packet[Package_Target].SUB_SID;
	}
	if(Package_Target==SID_SUB_DATA)
	{
		Data[1]=My_Packet[Package_Target].SUB_SID;
	}

	Result = TRUE;
	return Result;
}
/*data id encode handler*/
STATUES Packet_DATA_En( u8* const Data)
{
	STATUES Result = FALSE;
	if(Package_Target==SID_DATA)
	{

            for(u8 i=1;i<CAN_Package_len;i++)
            {
            	Data[i]=My_Packet[Package_Target].DATA_SEG[i-1];
            }

	}
	else if(Package_Target==SID_SUB_DATA)
	{
            for(u8 i=2;i<CAN_Package_len;i++)
            {
            	Data[i]=My_Packet[Package_Target].DATA_SEG[i-2];
            }
	}

	Result = TRUE;
	return Result;
}
/*reset the decoding statue */
void Packet_SmReset_de(void)
{
	PacketState_de=SID;
}
/*reset the encoding statue */
void Packet_SmReset_en(void)
{
	PacketState_en=SID;
}
/*read data services handler*/
STATUES Read_ID( Packet_Handler_t* const Data)
{
	STATUES   Pro_res=FALSE;
	STATUES   read_re=FALSE;
	u8 Error_Flage=0;
	u16 Local_DID= ((((u16)Data->DATA_SEG[0])<<8)|((u16)Data->DATA_SEG[1]));
        if(CAN_Package_len==3)
        {
			for(u8 i=0;i<Data_Table_len;i++)
			{
					if(Local_DID==Data_Table[i].DID)
					{
						if((Data_Table[i].DATA_Session_R==Current_Session)||(Data_Table[i].DATA_Session_R==Multi_Session))
						{
							if((Data_Table[i].DATA_Level_R==Current_Level)||(Data_Table[i].DATA_Level_R==Multi_Level))
							{
								Data->SID=Data->SID+0x40;
								for(u8 j=0;j<Data_Table[i].length;j++)
								{
									Data->DATA_SEG[j+2]=Data_Table[i].Data_ptr[j];
								}
								read_re=TRUE;
								CAN_Package_len=3+Data_Table[i].length;
							}
						}
					}
			 }
        }
        else
        	Error_Flage=1;
        if(read_re==FALSE)
		{
				nig_Flag=1;
				CAN_Package[0]=0x7F;
				CAN_Package[1]=Data->SID;
				CAN_Package[2]=FAILER_EXECUTION_OF_REUESTED_ACTION;
				CAN_Package_len=3;
				switch(Error_Flage)
				{
				case 1:
					CAN_Package[2]=INCORRECT_MASSAGE_LEN;
					break;
				}
				CANTP_SendPacket(CAN_Package,CAN_Package_len);
		}
	Pro_res=TRUE;

    return Pro_res;
}

/*session data services handler*/
STATUES Session_Control_fun(Packet_Handler_t* const Data)
{
	if(Data->SUB_SID>0&&Data->SUB_SID<4)
	{
		Current_Session=Data->SUB_SID;
		Data->SID=Data->SID+0x40;
		if(Current_Session!=Defualt)
		{
			Non_defualt_time_start_count_Flag=1;
		}
		else
		{
			Non_defualt_time_start_count_Flag=0;
		}
		CAN_Package_len=2;
	}
	else
	{
		nig_Flag=1;
		CAN_Package[0]=0x7F;
		CAN_Package[1]=Data->SID;
		CAN_Package[2]=SUB_SERVICE_NOT_SUPPORTED;
		CAN_Package_len=3;
		CANTP_SendPacket(CAN_Package,CAN_Package_len);
	}
	return TRUE;
}
/*Tester Represent data services handler*/
STATUES Tester_Represent( Packet_Handler_t* const Data)
{
	Data->SID=Data->SID+0x40;
	CAN_Package_len=1;
	S3_time_counter=0;
	return TRUE;
}

/*write  data services handler*/
STATUES Write_ID( Packet_Handler_t* const Data)
{
	STATUES   Pro_res=FALSE;
	STATUES   read_re=FALSE;
	u16 Local_DID= ((u16)(Data->DATA_SEG[0]))<<8;
		Local_DID=((u16)(Data->DATA_SEG[1]));
	u8 Error_Flage=0;

			for(u8 i=0;i<Data_Table_len;i++)
			{
					if(Local_DID==Data_Table[i].DID)
					{
							if((Data_Table[i].DATA_Session_W==Current_Session)||(Data_Table[i].DATA_Session_W==Multi_Session))
							{
								if((Data_Table[i].DATA_Level_W==Current_Level)||(Data_Table[i].DATA_Level_W==Multi_Level))
								{
									Data->SID=Data->SID+0x40;
									for(u8 j=0;j<Data_Table[i].length;j++)
									{

										Data_Table[i].Data_ptr[j]=(Data->DATA_SEG)[j+2];
									}
									read_re=TRUE;
									CAN_Package_len=3+Data_Table[i].length;
								}
							}
					}
			 }
		if(read_re==FALSE)
		{
				nig_Flag=1;
				CAN_Package[0]=0x7F;
				CAN_Package[1]=Data->SID;
				CAN_Package[2]=FAILER_EXECUTION_OF_REUESTED_ACTION;
				CAN_Package_len=3;
				switch(Error_Flage)
				{
				case 1:
					CAN_Package[2]=INCORRECT_MASSAGE_LEN;
					break;
				}
				CANTP_SendPacket(CAN_Package,CAN_Package_len);
		}
	Pro_res=TRUE;
	return Pro_res;
}

/*Security Access services handler*/
STATUES Security_Access_fun(Packet_Handler_t* const Data)
{
	STATUES Local_Status = FALSE;
	static u8 Seed_Value = 0;

		if(((Data->SUB_SID) %2==1)&&((Data->SUB_SID)<6)){
			// send a seed 8 bit , Random generator
			Seed_Value = generateRandomByte();

			Data->SID = Data->SID+0x40;
			Data->DATA_SEG[0] = Seed_Value;
			Local_Status = TRUE;
			CAN_Package_len=3;
		}
		else if(Data->SUB_SID == Key_1)
		{
			// check for key sent by tester by algorithm add by 5
			// if true access is accepted else,  NRC 0x35    Invalid Key
			if((Seed_Value+5) == Data->DATA_SEG[0])
			{
				Data->SID = Data->SID+0x40;
				Current_Level = Level1;
				Security_time_start_count_Flag=1;
				Local_Status = TRUE;
				CAN_Package_len=4;
			}
		}
		else if(Data->SUB_SID == Key_2)
		{
				if((Seed_Value+10) == Data->DATA_SEG[0])
				{
					Data->SID = Data->SID+0x40;
					Current_Level = Level2;
					Security_time_start_count_Flag=1;
					Local_Status = TRUE;
					CAN_Package_len=4;
				}
		}
	return Local_Status;
}

static u8 generateRandomByte(void){
    // Seed the random number generator
    srand((u16)time(NULL));

    // Generate a random byte
    u8 randomByte = rand() % 256;

    return randomByte;
}
/*function to check if UDS can receive new request */
Statue_2_t UDSM_voidCheckBuffer(void)
{
	if(processing_Flag==0)
	{
		CANTP_RxAsy(&ptr_packet,&CAN_Package_len);
		return OK ;
	}
	else
		return NO;
}
/*call back function to handle all times in UDS when timer interrupt fired*/
void UDSM_voidTiming(void)
{

	 if(Non_defualt_time_start_count_Flag==1)
	 {
		 S3_time_counter++;
		 if(S3_time_counter<=1000000)
		 {
			 Current_Session=Defualt;
			 S3_time_counter=0;
			 Non_defualt_time_start_count_Flag=0;
		 }
	 }
	 else
	 {
		 S3_time_counter=0;
	 }
	 if(Security_time_start_count_Flag==1)
	 {
		 Security_Level_Timeout_counter++;
		 if(Security_Level_Timeout_counter<=1000000)
		 {
			 Current_Level=Multi_Level;
			 Security_Level_Timeout_counter=0;
			 Security_time_start_count_Flag=0;
			// MSYSTICK_voidDisable();
		 }
	 }
	 else
	 {
		 Security_Level_Timeout_counter=0;
	 }

	 if(p2_time_start_count_Flag==1)
	 {
		 p2_Timeout_counter++;
		 if(p2_Timeout_counter<=1000)
		 {
			 u8 Pending_Frame[3];
			 Pending_Frame[0]=0X7F;
			 Pending_Frame[1]=My_Packet[0].SID;
			 Pending_Frame[2]=0X78;
			 CANTP_SendPacket(Pending_Frame,3);
			 p2_Timeout_counter=0;
			 p2_time_start_count_Flag=0;
		 }
	 }
	 else
	 {
		 p2_Timeout_counter=0;
	 }
}

