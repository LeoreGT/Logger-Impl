#ifndef __LOGMNGR_H__
#define __LOGMNGR_H__

#include <sys/types.h>
#include <unistd.h>
#include "logger.h"
#include "loglevel.h"

/*
    @brief   : a major function that do all the initializations
    @derails : calls the parsing to get information about all the
               modules.  stores all the file loggers in Vector.
    @param   : configuration file that the user can edit outside.
               with information how to treat every module.
    @return  : pointer to ZLog
*/
void Zlog_Init(const char* _configFileName);
/*
    @brief   : at the end of main propably, this function will close all
    @details : iterate throw all the loggers in the vector and close
               all opened log file. destroy all loggers.
*/
void Zlog_Close();
/*
    @brief   : finds the logger that holds the information on the module
    @derails : no need for the parameter ZLod because we have one of it
               here and we can use it here directly.
    @param   : configuration file that the user can edit outside.
               with information how to treat every module.
    @return  : pointer to ZLog
*/
Logger* ZLog_Get(char* _moduleName);
void    LoggerWrite(char* _moduleName, LogLevel _level, char* info);
FILE*  WriteToLogger(char* _moduleName, LogLevel _level);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros" /* received from classmates */

#define ZLOG(MODULE_NAME, LEVEL, MESSAGE,...)                                 \
{                                                                             \
  FILE* fp = WriteToLogger((MODULE_NAME), (LEVEL));                     \
  if (fp)                                                               \
  {                                                                     \
    fprintf(fp, "%d: %s, %s level#%d %s %s: line #%d "#MESSAGE " \n",   \
    getpid(), __DATE__, __TIME__, LEVEL, MODULE_NAME,                   \
    __extension__ __FUNCTION__, __LINE__, __VA_ARGS__);                 \
  }                                                                     \
}

#pragma GCC diagnostic pop

#endif /* __LOGMNGR_H__ */
