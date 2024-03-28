#include "STD_TYPES.h"
#include "BIT_MATH.h"

#ifndef UDSM_PRIVATE
#define UDSM_PRIVATE


#define NULL ((void *)0)   //TO INDIACTE TO NULL POINTER

/*enum to indicate to segments in frame  */
typedef enum
{
	 SID,                  /**< Looks for a SERVICE ID */
	 SUB_SID,             /**< Receives the SUB SERVICE ID*/
	 DATA_SEG,                 /**< Receives the packet data */
	 PACKET_STATE_END
} PacketRxState_t;

/*enum to indicate to types of frame  */
typedef enum
{
	 SID_S,  			  //frame has only service id
	 SID_SUB,             //frame has service id and sub service
	 SID_DATA,           //frame has service id and data
	 SID_SUB_DATA,       //frame has service id, sub service and data
	 Non_Service
} Service_char_t;


/*ENUM TO ANY STATUES TO CKECK IF OPERATION PROCESSED CORRECTILY */
typedef enum{FALSE ,TRUE}STATUES;


/*STRUCT TO DECODE THE PACKAGE IN IT */
typedef struct
{
 u8  SID;
 u8  SUB_SID;
 u8 DATA_SEG[15];
}Packet_Handler_t;

/*STRUCT TO MAKE ARRAY FROM IT TO REPRESENT STATUES OF ENCODE
  AND DECODE TO EACH PART OF FRAM
  AND EACH HANDLER   */
typedef struct
{
 PacketRxState_t State;
 STATUES(*Implemention)(u8* const Data);
}PacketSm_t;


/*ENUME TO REPRESENT ALL SEVICES*/
typedef enum
{
	 Reserved0,
	 Reserved1,
	 Reserved2,
	 Reserved3,
	 Reserved4,
	 Reserved5,
	 Reserved6,
	 Reserved7,
	 Reserved8,
	 Reserved9,
	 ReservedA,
	 ReservedB,
	 ReservedC,
	 ReservedD,
	 ReservedE,
	 ReservedF,
	 Session_Control,
	 Reserved11,
	 Reserved12,
	 Reserved13,
	 Reserved14,
	 Reserved15,
	 Reserved16,
	 Reserved17,
	 Reserved18,
	 Reserved19,
	 Reserved1A,
	 Reserved1B,
	 Reserved1C,
	 Reserved1D,
	 Reserved1E,
	 Reserved1F,
	 Reserved20,
	 Reserved21,
	 Read,
	 Reserved23,
	 Reserved24,
	 Reserved25,
	 Reserved26,
	 Security_Access,
	 Reserved28,
	 Reserved29,
	 Reserved2A,
	 Reserved2B,
	 Reserved2C,
	 Reserved2D,
	 Write,
	 Reserved2F,
	 Reserved30,
	 Reserved31,
	 Reserved32,
	 Reserved33,
	 Reserved34,
	 Reserved35,
	 Reserved36,
	 Reserved37,
	 Reserved38,
	 Reserved39,
	 Reserved3A,
	 Reserved3B,
	 Reserved3C,
	 Reserved3D,
	 Test_Represent,
	 Reserved3F,
} ServicesID_t;

/*STRUCT TO MAKE ARRAY FROM IT TO REPRESENT
 *  THE SEVICESE AND THE HANDLER TO THIS SERVICES  */
typedef struct
{
 ServicesID_t State;       //indicate to service number
 Service_char_t Decode;    //type of frame that service processes
 STATUES(*Implemention)(Packet_Handler_t* const Data);  //fun to handle the services
}Commands_t;

/*sessions in system*/
typedef enum
{
	 Defualt=1,
	 Programming,
	 Extened,
	 Multi_Session,
	 NOT_VALID_Session

} Session_Status_t;

/*ENUME CONTENT THE LEVELS OF SECUIRITY  */
typedef enum
{
	Level0,
	Level1,
	Level2,
	Level3,
	Level4,
	Multi_Level,
	NOT_VALID_Level
} Security_Levels_t;

/*INICATE TO Keys and Seeds in system*/
typedef enum
{
	Seed_1=0x01,
	Key_1,
	Seed_2,
	Key_2,
	Seed_3,
	Key_3,
} Security_SubService_t;

/*indicate to permissions in data read or write os read and write  */
typedef enum
{
	DATA_WR_R,
	DATA_WR,
	DATA_R
} Permision_t;


/*structure to save data characteristics */
typedef struct
{
u16 DID;
u8* Data_ptr;
u8 length;
Permision_t PREM;
Session_Status_t DATA_Session_R;
Session_Status_t DATA_Session_W;
Security_Levels_t DATA_Level_R;
Security_Levels_t DATA_Level_W;
}Data_By_Id;


//NRC FRFOM EACH NEGATIVE RESPONSE
#define 	GENERAL_REJECT  			                          0x10
#define 	SERVICE_NOT_SUPPORTED                                  0X11
#define 	SUB_SERVICE_NOT_SUPPORTED                              0X12
#define     FAILER_EXECUTION_OF_REUESTED_ACTION                    0x26
#define     INCORRECT_MASSAGE_LEN                                  0x13
#define     SURVICE_NOT_SUPPORTED_IN_ACTION_SESSION               0x7F
#define     SURVICE_NOT_SUPPORTED_IN_ACTION_LEVEL                 0x7E
#endif
