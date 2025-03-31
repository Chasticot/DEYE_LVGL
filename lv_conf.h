#ifndef LV_CONF_H
#define LV_CONF_H

/* Set this to 1 to enable content */
#define LV_CONF_SKIP 0

/* Color depth: 1 (1 byte per pixel), 8 (RGB332), 16 (RGB565), 32 (ARGB8888) */
#define LV_COLOR_DEPTH 16

/* Use a custom tick source */
#define LV_TICK_CUSTOM 1
#define LV_TICK_CUSTOM_INCLUDE "Arduino.h"
#define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())

/* Memory settings */
#define LV_MEM_SIZE (32 * 1024U)  /* 32KB */

/* Logging */
//#define LV_USE_LOG 0

#endif /*LV_CONF_H*/