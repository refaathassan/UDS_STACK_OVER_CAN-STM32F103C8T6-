/*********************************************************************************/
/* Author    : REFAAT HASSAN                                                      */
/* Version   : V02                                                               */
/* Date      : 11-2-2024                                                         */
/*********************************************************************************/
#ifndef CAN_CONFIG_H
#define CAN_CONFIG_H



/** CAN  configuration structure definition **/

 /*!< This parameters can be set to ENABLE or DISABLE. */
#define AutoRetransmission           ENABLE
#define AutoBussOff                  ENABLE
#define AutoWakeUp                   DISABLE
#define TimeTriggeredMode            DISABLE
#define ReceiveFifoLocked            DISABLE
#define TransmitFifoPriority         DISABLE

/********** option : 
 * 					 CAN_MODE_NORMAL
 * 					 CAN_MODE_LOOPBACK
 * 					 CAN_MODE_SILENT
 * 					 CAN_MODE_SILENT_LOOPBACK
 	 	 	 	 	 	 	 	 	 	 	 	 **********************************/
#define MODE				 CAN_MODE_NORMAL
/********** option : CAN_50KBPS
 * 					 CAN_100KBPS
 * 					 CAN_125KBPS
 * 					 CAN_250KBPS
 * 					 CAN_500KBPS
 * 					 CAN_800KBPS,
 * 					 CAN_1MBPS
 	 	 	 	 	 	 	 	 	 	 	 	 *************************/
#define BOUDRATE		CAN_100KBPS
u16 Std_id_High(u16 local_u16Std_Id)
{
	return (local_u16Std_Id << 5);
}
void CAN_FilterConfig(void)
{
	CAN_FilterTypeDef CAN_FilterInit;
	CAN_FilterInit.FilterActivation = ENABLE;
	CAN_FilterInit.FilterBank = 0;
	CAN_FilterInit.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	CAN_FilterInit.FilterIdHigh = Std_id_High(0x100);
	CAN_FilterInit.FilterIdLow = 0x0000;
	CAN_FilterInit.FilterMaskIdHigh = 0x0000;
	CAN_FilterInit.FilterMaskIdLow = 0x0000;
	CAN_FilterInit.FilterMode = CAN_FILTERMODE_IDLIST;
	CAN_FilterInit.FilterScale = CAN_FILTERSCALE_32BIT;

	CAN_voidConfigFilter(&CAN_FilterInit);
}

#endif /* CAN_CONFIG_H */
