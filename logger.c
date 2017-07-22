#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Logger.h"
#include "parser.h"

/*-------------------------------------*/

struct Logger
{
	LogLevel m_level;
	char* m_module[40];
	FILE* m_fp;
};

/*-------------------------------------*/

Logger* Logger_Create(LogLevel _level, char* _moduleName, char* filePath)
{
  Logger* Logger = NULL;

  Logger = malloc(sizeof(Logger));
  if(NULL == Logger)
  {
    return NULL;
  }

  strcpy((char*)Logger->m_module, _moduleName);

  Logger->m_level = _level;
  if (NULL == (Logger->m_fp = fopen(filePath, "a+"))) /* look over */
  {
    free(Logger);
    return NULL;
  }

  return Logger;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Logger_Destroy(Logger* _logger)
{
  if (NULL == _logger)
  {
    return;
  }

  if (NULL != _logger->m_fp)
  {
    fclose(_logger->m_fp);
  }

  /*free(_logger->m_module);
  free(_logger->m_fileName);*/
  free(_logger);
  /*_logger = NULL; */
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char* Get_ModuleName(Logger* _logger)
{
  return (char*)_logger->m_module;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

FILE* Get_FilePtr(Logger* _logger)
{
  if(NULL == _logger->m_fp)
  {
    _logger->m_fp = fopen("_logger->m_fileName", "r");
  }

  return _logger->m_fp;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

LogLevel Get_LoggerLevel(Logger* _logger)
{
	return _logger->m_level;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
