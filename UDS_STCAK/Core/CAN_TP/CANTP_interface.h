#ifndef CANTP_INTERFACE
#define CANTP_INTERFACE

/* ----------------- Includes -----------------*/
#include "CAN_interface.h"
#include"SYSTICK_interface.h"

/**
  * @brief  This function Init CAN , filter configuration , interrupt Activation , start communication
  * @retval NULL
  */
void CANTP_voidInit(void);
/**
  * @brief  This function Send data using CAN protocol
  * @param  (packet) pointer to Data to be sent
  * @param  (len) Length of Data to be sent
  * @retval NULL
  */
void CANTP_SendPacket(volatile u8* packet,volatile s8 len);
/**
  * @brief  This function request flag for UDS to start processing
  * @param  (cpy_ptr) pointer to flag
  * @retval NULL
  */
void CANTP_RxFlag(volatile u8 * cpy_ptr);
/**
  * @brief  This function Receive data using CAN protocol
  * @param  (packet) pointer to Data to be sent
  * @param  (len) Length of Data to be sent
  * @retval NULL
  */
void CANTP_RecievPacket( volatile u8* packet,volatile u8* len);
/**
  * @brief  This function releases all memory to the heap.
  * @param  (DATA) pointer to stack head structure
  * @param  (ptr) Status returned while performing this operation
  * @retval NULL
  */
void CANTP_RxAsy(volatile u8 **DATA,volatile u8 *ptr );
/**
  * @brief  This function to be called when received interrupt flag from CAN
  * @param  (fun) pointer to Function
  * @retval NULL
  */
void CANTP_voidCallBack(Statue_2_t(*fun)(void));


#endif
