/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :30-12-2022                                                            */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/

#ifndef    _AFIO_INTERFACE_H
#define    _AFIO_INTERFACE_H


//types of port you want to config in line
#define    PORTA        0b0000
#define    PORTB        0b0001
#define    PORTC	    0b0010

void MAFIO_AFIOLineConfig(u8 COPY_u8Line,u8 COPY_u8PORT);

#endif
