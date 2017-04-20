#include <stdbool.h>
#include "contiki.h"
#include "dev/watchdog.h"
#include "clock.h"
#include "em_cmu.h"
#include "em_wdog.h"

#define DEBUG 1
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

/*---------------------------------------------------------------------------*/
void
watchdog_reboot(void)
{
  // Use Software Reset instead of watchdog
  NVIC_SystemReset();
}

#ifndef NO_WATCHDOG
/*---------------------------------------------------------------------------*/
void
watchdog_start(void)
{
  WDOG_Enable(true);
}
/*---------------------------------------------------------------------------*/
void
watchdog_stop(void)
{
  WDOG_Enable(false);
}
/*---------------------------------------------------------------------------*/
/**
 * \brief
 *   Feed the watchdog.
 *
 * \details
 *   When the watchdog is activated, it must be fed (ie clearing the counter)
 *   before it reaches the defined timeout period. Otherwise, the watchdog
 *   will generate a reset.
 */
void
watchdog_periodic(void)
{
  /* This function is called periodically to reset the watchdog
     timer. */
  WDOG_Feed();
}

#ifdef CONFIG_PM
/*---------------------------------------------------------------------------*/
int watchdog_suspend(void)
{
	watchdog_stop();
	return 0;
}
/*---------------------------------------------------------------------------*/
/*
 * LPOsc was stopped during PM8, restart watchdog
 */
int watchdog_resume(void)
{
	watchdog_start();
	return 0;
}
/*---------------------------------------------------------------------------*/

static pm_ops_struct watchdog_pm_ops = {
	.suspend = watchdog_suspend,
	.resume = watchdog_resume,
};
#endif

/*---------------------------------------------------------------------------*/
/**
 * \brief   Initialize watchdog
 *
 * This function initialize efm32 internal watchdog for max period : 256s
 *
 * \details
 * It also locks configuration :
 *  after initialization, Software can't disable watchdog or the mother clock
 *  Only next reset will reset configuration.
 */
void
watchdog_init(void)
{
  // Default is max period (256s)
  WDOG_Init_TypeDef init = WDOG_INIT_DEFAULT;

  CMU_ClockEnable(cmuClock_CORELE, true);

#ifdef CONFIG_PM
  // Allow counting PM2 and PM3
  init.em2Run = true;
  init.em3Run = true;
#endif

#ifndef NO_WATCHDOG
  // Lock configuration
  init.lock = true;
  init.swoscBlock = true;
#endif

  WDOG_Init(&init);
}
#else
void watchdog_init(void) { return; }
void watchdog_start(void){ return; }
void watchdog_stop(void){ return; }
void watchdog_periodic(void){ return; }

#endif

/** @} */
