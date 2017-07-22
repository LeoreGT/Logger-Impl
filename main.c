#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "loglevel.h"
#include "logmngr.h"
#include "logger.h"

void test();
/* process id, date, time, level result, module name, line num, message */
int main( )
{
  Zlog_Init("log_config");

  ZLOG("default ", LOG_FATAL, "MESSAGE: %d", 1);
  ZLOG("File    ", LOG_FATAL, "MESSAGE: %d", 2);
  ZLOG("Module 2", LOG_FATAL, "MESSAGE: %d", 3);
  ZLOG("Module 3", LOG_FATAL, "MESSAGE: %d", 4);
  ZLOG("File    ", LOG_FATAL, "MESSAGE: %d", 5);

  test(); /* send to outer function to test */

  Zlog_Close();

  ZLOG("Other   ", LOG_ERROR,  "SEE IF WORKS AFTER CLOSED: %d", 1);
  ZLOG("File    ", LOG_DEBUG,  "SEE IF WORKS AFTER CLOSED: %d", 2);
  ZLOG("Module 2", LOG_TRACE,  "SEE IF WORKS AFTER CLOSED: %d", 3);
  ZLOG("Module 3", LOG_NONE,   "SEE IF WORKS AFTER CLOSED: %d", 4);
  ZLOG("Module 3", LOG_TRACE,  "SEE IF WORKS AFTER CLOSED: %d", 5);
  ZLOG("default ", LOG_INFO,   "SEE IF WORKS AFTER CLOSED: %d", 6);
  ZLOG("Other   ", LOG_SEVERE, "SEE IF WORKS AFTER CLOSED: %d", 7);
  ZLOG("default ", LOG_DEBUG,  "SEE IF WORKS AFTER CLOSED: %d", 8);

  Zlog_Close();
  printf("Finished!\n");
  return 0;
}

void test()
{

  ZLOG("default ", LOG_TRACE,    "IN-FUNC: %d", 1);
  ZLOG("Other   ", LOG_TRACE,    "IN-FUNC: %d", 2);
  ZLOG("Def     ", LOG_WARNING,  "IN-FUNC: %d", 3);
  ZLOG("default ", LOG_CRITICAL, "IN-FUNC: %d", 4);
  ZLOG("Other   ", LOG_NONE,     "IN-FUNC: %d", 5);
  ZLOG("default ", LOG_INFO,     "IN-FUNC: %d", 6);

  printf("Out of our Test Function!\n");
}
