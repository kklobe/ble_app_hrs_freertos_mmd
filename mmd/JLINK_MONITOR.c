/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*       (c) 1995 - 2015  SEGGER Microcontroller GmbH & Co. KG        *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
 
----------------------------------------------------------------------
File    : JLINK_MONITOR.c
Purpose : Implementation of debug monitor for J-Link monitor mode debug on Cortex-M devices.
--------  END-OF-HEADER  ---------------------------------------------
*/

#if CONFIG_JLINK_MONITOR_ENABLED

#include "JLINK_MONITOR.h"

#include "FreeRTOS.h"
#include "task.h"

/*********************************************************************
*
*       Configuration
*
**********************************************************************
*/

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

volatile int MAIN_MonCnt;   // Incremented in JLINK_MONITOR_OnPoll() while CPU is in debug mode

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/********************************************************************* 
* 
*       JLINK_MONITOR_OnExit()
* 
*  Function description 
*    Called from DebugMon_Handler(), once per debug exit.
*    May perform some target specific operations to be done on debug mode exit.
* 
*  Notes 
*    (1) Must not keep the CPU busy for more than 100 ms
*/ 
static volatile UBaseType_t uxInterruptWoken;

void JLINK_MONITOR_OnExit(void) {
  taskEXIT_CRITICAL_FROM_ISR(uxInterruptWoken);
}

/********************************************************************* 
* 
*       JLINK_MONITOR_OnEnter()
* 
*  Function description 
*    Called from DebugMon_Handler(), once per debug entry.
*    May perform some target specific operations to be done on debug mode entry
* 
*  Notes 
*    (1) Must not keep the CPU busy for more than 100 ms
*/ 
void JLINK_MONITOR_OnEnter(void) {
  uxInterruptWoken = taskENTER_CRITICAL_FROM_ISR();
}

/********************************************************************* 
* 
*       JLINK_MONITOR_OnPoll()
* 
*  Function description 
*    Called periodically from DebugMon_Handler(), to perform some actions that need to be performed periodically during debug mode.
* 
*  Notes 
*    (1) Must not keep the CPU busy for more than 100 ms
*/
void JLINK_MONITOR_OnPoll(void) {
  //
  // Add custom code here
  //
#if CONFIG_WATCHDOG_ENABLED
    nrf_drv_wdt_channel_feed(s_watchdog_channel);
#endif

  MAIN_MonCnt++;
//  _Delay(500000);
}
#endif
/****** End Of File *************************************************/
