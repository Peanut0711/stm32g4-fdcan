#ifndef HW_DEF_H_
#define HW_DEF_H_



#include "bsp.h"


#define _DEF_FIRMWARE_VERSION    "B251209R1"
#define _DEF_BOARD_NAME          "STM32G4-RELAY-BOOT"




#define _USE_HW_FLASH
#define _USE_HW_FAULT
#define _USE_HW_MINI_PRINTF
#include "mini-printf.h"


#define _USE_HW_LED
#define      HW_LED_MAX_CH          4
#define      HW_LED_CH_DEBUG_LED    _DEF_LED1
#define      HW_LED_CH_TEST_LED     _DEF_LED4

#define _USE_HW_UART
#define      HW_UART_MAX_CH        1
#define      HW_UART_CH_DEBUG       _DEF_UART1

#define _USE_HW_LOG
#define      HW_LOG_CH              _DEF_UART1
#define      HW_LOG_BOOT_BUF_MAX    1024
#define      HW_LOG_LIST_BUF_MAX    1024

#define _USE_HW_SWTIMER
#define      HW_SWTIMER_MAX_CH      4

#define _USE_HW_GPIO
#define      HW_GPIO_MAX_CH         4

#define _USE_HW_RESET
#define      HW_RESET_BOOT          1

#define _USE_HW_RTC
#define      HW_RTC_BOOT_MODE       RTC_BKP_DR3
#define      HW_RTC_RESET_BITS      RTC_BKP_DR4

#define _USE_HW_CMD
#define      HW_CMD_MAX_DATA_LENGTH 1024

#define _USE_HW_CAN
#define      HW_CAN_MAX_CH          1
#define      HW_CAN_MSG_RX_BUF_MAX  32


#define FLASH_SIZE_TAG              0x400
#define FLASH_SIZE_VER              0x400
#define FLASH_SIZE_FIRM             (104*1024)

#define FLASH_ADDR_BOOT             0x08000000
#define FLASH_ADDR_FIRM             0x08006000

#define FLASH_ADDR_UPDATE           0x08006000 // 0x08013000

typedef enum
{
  GPIO_MODEL_0 = 0,
  GPIO_MODEL_1,
  GPIO_MODEL_2,
  GPIO_MODEL_3,  
  GPIO_PIN_MAX
} GpioPinName_t;

typedef struct
{
  uint8_t can_id;
} hw_info_t;

#endif