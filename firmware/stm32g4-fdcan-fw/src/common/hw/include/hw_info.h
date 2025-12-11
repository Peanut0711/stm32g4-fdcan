#ifndef HW_INFO_H_
#define HW_INFO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hw_def.h"


bool hwInfoInit(void);
void hwInfoUpdate(void);
uint8_t hwInfoGetId(void);



#ifdef __cplusplus
}
#endif

#endif 