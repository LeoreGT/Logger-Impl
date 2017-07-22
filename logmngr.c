#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "vector.h"
#include "logmngr.h"

static void     ParsedDataToLogManager(Config* _dataAfterParsing);
static void     Default_LogManager_Create();
static Logger*  LogManager_GetLog(char* _moduleName);

/*
 *  ( ) We need only 1 instance of this struct throughout the program.
 *  (1) When the macro ZLOG called, m_defaultLog logger will be the one
 *      returned if something went wrong (incorrect module name, etc)
 *  (2) Can choose other Data Structure, maybe hash or linked list
 *  (3) All log files go to the same directory in this program. it can be changed
 *      so then every logger will have other path. but, the FILE* fp is the one..
 */
typedef struct LogManager
{   /*^^^^^^^^^^^^^^^*/
   Logger*    m_defaultLog;
   LogLevel   m_defaultLevel;
   char*      m_defaultFile;

   Vector*    m_loggers; /* should be void* ? */
   char*      m_path;
}LogManager;

LogManager CurrentLogManager; /* our global LogManager used through the file */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Zlog_Init(const char* _configFileName)  {

  Config*  parsedData = Config_ReadCurrent(_configFileName);

  if (NULL != parsedData)
  {
    /* if we have parsed data, send it to the log manager */
    ParsedDataToLogManager(parsedData);
    Config_Destroy(parsedData);
  }
  else
  {
    /* if no parsed data, create the default log manager */
    Default_LogManager_Create();
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Zlog_Close()
{
  /* first destroy the vector of logs, use the logger_destroy function */
  Vector_Destroy (&(CurrentLogManager.m_loggers),  Logger_Destroy);

  /* free the default log */
  if (CurrentLogManager.m_defaultLog)
  {
    Logger_Destroy(CurrentLogManager.m_defaultLog);
    CurrentLogManager.m_defaultLog = NULL;
  }

  /* free the path */
  if (CurrentLogManager.m_path)
  {
    free(CurrentLogManager.m_path);
    CurrentLogManager.m_path = NULL;
  }

  /* free the default file */
  if (CurrentLogManager.m_defaultFile)
  {
    free(CurrentLogManager.m_defaultFile);
    CurrentLogManager.m_defaultFile = NULL;
  }

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Function is for the ZLOG macro */
FILE*  WriteToLogger(char* _moduleName, LogLevel _level)
{

  Logger* logger = LogManager_GetLog(_moduleName);

  if(NULL != logger)
  {
    /* get the _level and convert it */
    if (LogLevel_Convert(logger) <= _level)
    {
      /* opens up the file */
      return Get_FilePtr(logger);
    }
  }

  return NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Logger*  LogManager_GetLog(char* _moduleName)
{
  Logger* logger;
  int i = 1;
  /* check if worked */
  while(VECTOR_SUCCESS == Vector_Get(CurrentLogManager.m_loggers, i++, (void**)&logger))
  {
    /* compare _moduleName to the logger's module name member */
    if(0 == strcmp(_moduleName, Get_ModuleName(logger)))
    {
      return logger;
    }
  }

  /* if didn't work return the default */
  return CurrentLogManager.m_defaultLog;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void  ParsedDataToLogManager(Config* _dataAfterParsing)
{
  Logger* currentLogger;
  int i, numOfLoggers = _dataAfterParsing->m_numOfPairs;

  /* create the default logger and  give it the parsed data's members */
  CurrentLogManager.m_defaultLog = Logger_Create(_dataAfterParsing->m_defaultLevel,
                                         "default",
                                         _dataAfterParsing->m_filePath);
  /* return if thtere are no loggers */
  if (0 == numOfLoggers)
  {
    return;
  }

  /* if there are 1 or more loggers, create a vector for them */
  CurrentLogManager.m_loggers = Vector_Create(numOfLoggers, 0);
  /* for each of the vector's loggers, create and apply the given members to its pair */
  for(i = 0; i < numOfLoggers; i++)
  {
    currentLogger = Logger_Create(_dataAfterParsing->m_pairs[i].m_level,
                                  _dataAfterParsing->m_pairs[i].m_moduleName,
                                  _dataAfterParsing->m_pairs[i].m_filePath);

    if(NULL != currentLogger)
    {
      /* check if there are more vectors. If there are, append them to the vector*/
      Vector_Append(CurrentLogManager.m_loggers, currentLogger);
    }
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void  Default_LogManager_Create()
{
  CurrentLogManager.m_defaultLog = Logger_Create(LOG_ERROR, "default", "defaultLogger.log");
  /* the default doesn't have a vector of loggers */
  CurrentLogManager.m_loggers = NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
