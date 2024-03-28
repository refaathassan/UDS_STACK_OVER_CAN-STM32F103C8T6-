/*************************************************************************************************/
/*           AUTHOR       : Refaat Hassan                                                        */
/*           DATE         :23-12-2022                                                            */
/*           VERSION      :V01                                                                   */
/*************************************************************************************************/

#ifndef     BIT_MAHT_H
#define     BIT_MATH_H


#define    SET_BIT(VAR,BIT)        (VAR|=(1<<BIT))
#define    CLR_BIT(VAR,BIT)        (VAR&=(~(1<<BIT)))
#define    GET_BIT(VAR,BIT)        ((VAR>>BIT)&1)
#define    TOG_BIT(VAR,BIT)        (VAR^=(1<<BIT))



#endif
