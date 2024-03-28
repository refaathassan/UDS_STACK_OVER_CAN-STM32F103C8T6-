/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :30-12-2022                                                            */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/

#ifndef    _AFIO_PRIVATE_H
#define    _AFIO_PRIVATE_H

//struct have AFIO REGISTERS 
typedef  struct {
	volatile u32 EVCR;  
	volatile u32 MAPR;
	volatile u32 EXTICR[4]; //THAT SELECTED WHO PORT WILL ENABLE IN LINE 
	volatile u32 MAPR2;	
}AFIO_t;  

//POINTER TO POINT TO ALL REGISTER IN AFIO 
#define    AFIO     ((volatile  AFIO_t*)0x40010000)


#endif
