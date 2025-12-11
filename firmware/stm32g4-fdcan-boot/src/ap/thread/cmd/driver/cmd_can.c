#include "cmd_can.h"


static bool     open_(void *args);
static bool     close_(void *args);
static uint32_t available(void *args);
static bool     flush(void *args);
static uint8_t  read(void *args);
static uint32_t write(void *args, uint8_t *p_data, uint32_t length);
static void     infoPrint(void);

static bool    is_init   = false;
static bool    is_open   = false;
static uint8_t can_ch    = _DEF_CAN1;
static uint8_t can_tx_id = 0xFF;

static qbuffer_t rx_q;
static uint8_t   rx_q_buf[2048];

bool cmdCanInitDriver(cmd_driver_t *p_driver)
{
  qbufferCreate(&rx_q, rx_q_buf, 2048);

  p_driver->open      = open_;
  p_driver->close     = close_;
  p_driver->available = available;
  p_driver->flush     = flush;
  p_driver->read      = read;
  p_driver->write     = write;

  is_init = true;

  return true;
}

bool open_(void *args)
{
  bool ret;

  ret = canOpen(can_ch, CAN_NORMAL, CAN_FD_NO_BRS, CAN_500K, CAN_500K);
  canConfigFilter(can_ch, 0, CAN_EXT, hwInfoGetId(), 0xFF);
  canConfigFilter(can_ch, 1, CAN_EXT, 0x00, 0xFF);
  canConfigFilter(can_ch, 2, CAN_EXT, 0xFF, 0xFF);

  infoPrint();

  return ret;
}

bool close_(void *args)
{
  if (is_open == false) return true;

  is_open = false;

  return true;
}

uint32_t available(void *args)
{
  uint32_t ret;


  canUpdate();

  if (canMsgAvailable(can_ch))
  {
    can_msg_t msg;
    uint8_t   can_type;

    canMsgRead(can_ch, &msg);

    can_type = (msg.id >> 16) & 0xFF;
    ;
    if (can_type == CAN_TYPE_BYPASS)
    {
      can_tx_id = (msg.id >> 8) & 0xFF;
      qbufferWrite(&rx_q, msg.data, msg.length);
    }
  }

  ret = qbufferAvailable(&rx_q);

  return ret;
}

bool flush(void *args)
{
  return true;
}

uint8_t read(void *args)
{
  uint8_t ret = 0;

  qbufferRead(&rx_q, &ret, 1);

  // logPrintf("can rx : 0x%02x\n", ret);

  return ret;
}

uint32_t write(void *args, uint8_t *p_data, uint32_t length)
{
  can_msg_t msg;
  uint32_t  sent_len;
  uint32_t  can_id;


  can_id = (CAN_TYPE_BYPASS << 16) | ((hwInfoGetId()) << 8) | (can_tx_id << 0);

  msg.frame   = CAN_FD_BRS;
  msg.id_type = CAN_EXT;
  msg.id      = can_id;


  sent_len = 0;

  while (sent_len < length)
  {
    uint16_t tx_len;
    CanDlc_t dlc;

    dlc    = canGetDlc(length - sent_len);
    tx_len = canGetLen(dlc);

    msg.dlc = dlc;
    memcpy(msg.data, &p_data[sent_len], tx_len);

    if (canMsgWrite(can_ch, &msg, 10))
    {
      sent_len += tx_len;
    }
    else
    {
      break;
    }
  }

  return sent_len;
}

void infoPrint(void)
{
  can_info_t can_info;


  canGetInfo(can_ch, &can_info);

  logPrintf("[  ] canOpen()\n");
  logPrintf("[  ]   baud  : ");
  switch (can_info.baud)
  {
    case CAN_100K:
      logPrintf("100K\n");
      break;
    case CAN_125K:
      logPrintf("125K\n");
      break;
    case CAN_250K:
      logPrintf("250K\n");
      break;
    case CAN_500K:
      logPrintf("500K\n");
      break;
    case CAN_1M:
      logPrintf("1M\n");
      break;
    default:
      break;
  }

  logPrintf("[  ]   baud data : ");
  switch (can_info.baud_data)
  {
    case CAN_100K:
      logPrintf("100K\n");
      break;
    case CAN_125K:
      logPrintf("125K\n");
      break;
    case CAN_250K:
      logPrintf("250K\n");
      break;
    case CAN_500K:
      logPrintf("500K\n");
      break;
    case CAN_1M:
      logPrintf("1M\n");
      break;
    case CAN_2M:
      logPrintf("2M\n");
      break;
    case CAN_4M:
      logPrintf("4M\n");
      break;
    case CAN_5M:
      logPrintf("5M\n");
      break;
  }

  logPrintf("[  ]   mode  : ");
  switch (can_info.mode)
  {
    case CAN_NORMAL:
      logPrintf("NORMAL\n");
      break;
    case CAN_MONITOR:
      logPrintf("MONITOR\n");
      break;
    case CAN_LOOPBACK:
      logPrintf("LOOPBACK\n");
      break;
  }

  logPrintf("[  ]   frame : ");
  switch (can_info.frame)
  {
    case CAN_CLASSIC:
      logPrintf("CAN_CLASSIC\n");
      break;
    case CAN_FD_NO_BRS:
      logPrintf("CAN_FD_NO_BRS\n");
      break;
    case CAN_FD_BRS:
      logPrintf("CAN_FD_BRS\n");
      break;
  }
}
