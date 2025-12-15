#include "cmd_thread.h"
#include "driver/cmd_can.h"
#include "driver/cmd_uart.h"
#include "process/cmd_boot.h"

enum
{
  CMD_DRV_UART,
  CMD_DRV_CAN,
  CMD_DRV_MAX
};

#define CMD_DRIVER_MAX_CH CMD_DRV_MAX


static cmd_t        cmd[CMD_DRIVER_MAX_CH];
static cmd_driver_t cmd_drvier[CMD_DRIVER_MAX_CH];

bool cmdThreadInit(void)
{
  cmdUartInitDriver(&cmd_drvier[CMD_DRV_UART], HW_UART_CH_DEBUG, 115200);
  cmdInit(&cmd[CMD_DRV_UART], &cmd_drvier[CMD_DRV_UART]);
  cmdOpen(&cmd[CMD_DRV_UART]);

  cmdCanInitDriver(&cmd_drvier[CMD_DRV_CAN]);
  cmdInit(&cmd[CMD_DRV_CAN], &cmd_drvier[CMD_DRV_CAN]);
  cmdOpen(&cmd[CMD_DRV_CAN]);

  return true;
}

bool cmdThreadUpdate(void)
{
  bool rx_ret = false;

  for (int i = 0; i < CMD_DRIVER_MAX_CH; i++)
  {
    if (cmd[i].is_init == true)
    {
      if (cmdReceivePacket(&cmd[i]) == true)
      {
        bool ret  = true;
        ret      &= cmdBootProcess(&cmd[i]);

        if (ret != true)
        {
          cmdSendResp(&cmd[i], cmd[i].packet.cmd, ERR_CMD_NO_CMD, NULL, 0);
        }

        rx_ret = true;
      }
    }
  }

  return rx_ret;
}
