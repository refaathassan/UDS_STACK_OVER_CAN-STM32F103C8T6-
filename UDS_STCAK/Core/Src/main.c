#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include"RCC_interface.h"
#include"GPIO_interfac.h"
#include"USRTM_interface.h"
#include"UDSM_interface.h"
#include"CANTP_interface.h"


 /*flag to indicate that we received Request*/
volatile u8 Request_Flage=0;



int main(void)
{
    /*initialisation*/
	RCC_voidIintSysClock();              // to enable clock for system
	UDSM_voidInit();                              // initiate UDS Manager

	/*request flag set when receive request*/

    /* Loop forever */
	while(1)
	{
		/*pull in request flag to check if received Request*/
		 if(Request_Flage!=0)
		 {
			 /*response to the request */
			 UDSM_voidResponse();
			 /*clear the flag after response*/
			 Request_Flage=0;
		 }

	}
}
