#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "ADTErr.h"
#include "logger.h"

#define CAPACITY 30
#define STR_LENGTH 128
#define OK 1
#define FAIL -1
#define CHECK_PARAMS(input, inputAgainst, output) if(inputAgainst == input) \
                              { \
                              return output; \
                              }

static int IsNotNext(FILE* fp, char* str);
LogLevel LogLevel_Convert(char* _level);

/*--------------------------------------------------------------------------*/

static int Config_ReadDefault(Config* parsser, FILE *fp)
{
  char level[20];
  char fileName[30];
  char filePath[50];

  if (IsNotNext(fp, "[#]") || IsNotNext(fp, "Level") || IsNotNext(fp, "=") )
  {
    return FAIL;
  }
  fscanf(fp, "%s", level);

  if (IsNotNext(fp, "Path") || IsNotNext(fp, "=") )
  {
    return FAIL;
  }
  fscanf(fp, "%s", parsser->m_path);

  if (IsNotNext(fp, "File") || IsNotNext(fp, "=") )
  {
    return FAIL;
  }
  fscanf(fp, "%s", fileName);

  parsser->m_defaultLevel = LogLevel_Convert(level);
  strcpy(filePath, parsser->m_path);
  strcat(filePath, fileName);
  strcpy(parsser->m_filePath, filePath);
  return OK;
}

static int Config_ReadNext(Config* parsser, FILE *fp, int i)
{
  char modulName[20];
  char level[20];
  char fileName[30];
  char filePath[50];
  int len;

  fscanf(fp, "%s", modulName);
  len = strlen(modulName);
  if (len <= 2 || '[' != modulName[0]  || ']' != modulName[len-1] )
  {
    return FAIL;
  }
  modulName[len-1] = '\0';
  strcpy( parsser->m_pairs[i].m_moduleName, modulName+1);

  if (IsNotNext(fp, "Level") || IsNotNext(fp, "=") )
  {
    return FAIL;
  }
  fscanf(fp, "%s", level);

  if (IsNotNext(fp, "File") || IsNotNext(fp, "=") )
  {
    return FAIL;
  }
  fscanf(fp, "%s", fileName);

  parsser->m_pairs[i].m_level = LogLevel_Convert(level);
  strcpy(filePath, parsser->m_path);
  strcat(filePath, fileName);
  strcpy(parsser->m_pairs[i].m_filePath, filePath);
  return OK;
}

static int IsNotNext(FILE* fp, char* str)
{
  char word[20];
  fscanf(fp, "%s", word);
  return strcmp(word, str);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Config_Destroy(Config* _configs)
{
  if (_configs)
  {
    free(_configs);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Config* Config_ReadCurrent(const char* _configFileName)
{
  Config* config = malloc(sizeof(config));
  int i = 0;
  FILE* filePtr;
  CHECK_PARAMS(NULL, config, NULL);
  CHECK_PARAMS(NULL, (filePtr = fopen(_configFileName, "r+")), NULL);

  if (FAIL == Config_ReadDefault(config, filePtr))
  {
    fclose(filePtr);
    free(config);
    return NULL;
  }

  while (FAIL != Config_ReadNext(config, filePtr, i))
  {
    i++;
  }

  config->m_numOfPairs = i;
  fclose(filePtr);
  return config;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

LogLevel LogLevel_Convert(char* _level)
{
  if ( 0 == strcmp(_level,"LOG_TRACE"))
  {
    return LOG_TRACE;
  }
  if ( 0 == strcmp(_level,"LOG_DEBUG"))
  {
    return LOG_DEBUG;
  }
  if ( 0 == strcmp(_level,"LOG_INFO"))
  {
    return LOG_INFO;
  }
  if ( 0 == strcmp(_level,"LOG_WARNING"))
  {
    return LOG_WARNING;
  }
  if ( 0 == strcmp(_level,"LOG_ERROR"))
  {
    return LOG_ERROR;
  }
  if ( 0 == strcmp(_level,"LOG_CRITICAL"))
  {
    return LOG_CRITICAL;
  }
  if ( 0 == strcmp(_level,"LOG_SEVERE"))
  {
    return LOG_SEVERE;
  }
  if ( 0 == strcmp(_level,"LOG_FATAL"))
  {
    return LOG_FATAL;
  }
  if ( 0 == strcmp(_level,"LOG_NONE"))
  {
    return LOG_NONE;
  }
  return LOG_ERROR;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
