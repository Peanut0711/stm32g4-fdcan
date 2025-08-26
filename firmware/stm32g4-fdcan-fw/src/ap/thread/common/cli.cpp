#include "cli.h"

#include "thread.h"
#include "common/event.h"
#include "manage/mode.h"


static bool cliThreadInit(void);
static bool cliThreadUpdate(void);
static bool cliThreadEvent(event_t *p_event);


__attribute__((section(".thread"))) 
static volatile thread_t thread_obj = 
  {
    .name = "cli",
    .is_enable = true,
    .init = cliThreadInit,
    .update = cliThreadUpdate,
  };




bool cliThreadInit(void)
{
  (void)thread_obj;

  #ifdef _USE_HW_CLI
  cliOpen(_DEF_UART1, 115200);
  #endif  

  eventNodeAdd(cliThreadEvent);
  return true;
}

bool cliThreadEvent(event_t *p_event)
{
  return true;
}

bool cliThreadUpdate(void)
{  
  #ifdef _USE_HW_CLI 
  cliMain();
  #endif

  return true;
}

