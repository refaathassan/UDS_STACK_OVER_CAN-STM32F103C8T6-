/*
 * Interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ñRefaat Mobarak
 */
#include"STD_TYPES.h"
#ifndef INTERFACE_H_
#define INTERFACE_H_

typedef enum u32 {
	 APP=0x41505000,
	NAPP=0x4E415050,
	REQ=0x52455100,
	NREQ=0x4E524551,
}APP_STATUES;

typedef enum u8 {
	 ERROR_OCCUR=0x01,
	NO_ERROR=0x02
}ERROR_STATUES;

#endif /* INTERFACE_H_ */
