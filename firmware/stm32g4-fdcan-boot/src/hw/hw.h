#ifndef HW_H_
#define HW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hw_def.h"

#include "qbuffer.h"
#include "led.h"
#include "cli.h"
#include "log.h"
#include "uart.h"
#include "swtimer.h"
#include "can.h"
#include "gpio.h"
#include "flash.h"
#include "rtc.h"
#include "reset.h"
#include "cmd.h"
#include "util.h"
#include "fault.h"
#include "hw_info.h"


bool hwInit(void);


#ifdef __cplusplus
}
#endif

#endif