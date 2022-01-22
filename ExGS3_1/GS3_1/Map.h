#include "USER.h"
#ifndef __MAPPING_H__
#define __MAPPING_H__

// Function Definitions
typedef void (*pgObjPlayerKiller) (OBJECTSTRUCT*, OBJECTSTRUCT*);
extern pgObjPlayerKiller gObjPlayerKiller;

typedef BOOL (*pPkCheck) (OBJECTSTRUCT*, OBJECTSTRUCT*);
extern pPkCheck PkCheck;

#endif