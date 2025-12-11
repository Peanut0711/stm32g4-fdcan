#include "hw_info.h"
#include "gpio.h"
#include "cli.h"



static hw_info_t hw_info;

#ifdef _USE_HW_CLI
static void cliCmd(cli_args_t *args);
#endif



bool hwInfoInit(void)
{
  hwInfoUpdate();
  printf("hwInfo Init - ID %d\n", hw_info.can_id);

  #ifdef _USE_HW_CLI
  cliAdd("hwinfo", cliCmd);
  #endif
  return true;
}

void hwInfoUpdate(void)
{ 
  uint8_t id = 0;

  id |= (gpioPinRead(GPIO_MODEL_3) & 0x01) << 3;
  id |= (gpioPinRead(GPIO_MODEL_2) & 0x01) << 2;
  id |= (gpioPinRead(GPIO_MODEL_1) & 0x01) << 1;
  id |= (gpioPinRead(GPIO_MODEL_0) & 0x01) << 0;

  hw_info.can_id = id;
}
 

uint8_t hwInfoGetId(void)
{
  hwInfoUpdate();

  return hw_info.can_id;
}


hw_info_t *hwInfo(void)
{
  return &hw_info;
}

#ifdef _USE_HW_CLI
void cliCmd(cli_args_t *args)
{
  bool ret = false;

  if (args->argc == 1 && args->isStr(0, "info"))
  {
    cliPrintf("hwinfo - can id : %d\n", hw_info.can_id);
    ret = true;
  } 

  if (args->argc == 1 && args->isStr(0, "update"))
  {
    uint8_t prev_can_id = hw_info.can_id;
    
    hwInfoUpdate();

    cliPrintf("hwinfo update - can id : %d -> %d\n", prev_can_id, hw_info.can_id);
    ret = true;
  }

  if (ret == false)
  {
    cliPrintf("hwinfo info\n");
    cliPrintf("hwinfo update\n");
  }
}
#endif