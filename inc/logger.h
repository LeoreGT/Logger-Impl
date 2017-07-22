#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "loglevel.h"

typedef struct Logger Logger;

Logger*    Logger_Create(LogLevel _level, char* _moduleName, char* filePath);
void       Logger_Destroy(Logger* _logger);
LogLevel   Get_LoggerLevel(Logger* _logger);
char*      Get_ModuleName(Logger* _logger);
FILE*      Get_FilePtr(Logger* _logger);

#endif
