#ifndef __READ_CONFIG_H__
#define __READ_CONFIG_H__

#include <stdio.h>
#include "loglevel.h"

/* these are here because both the parser and the logmngr need the structs */
typedef struct Pair
{
  LogLevel  m_level;
  char      m_moduleName[20];
  char      m_filePath[50];
} Pair;

typedef struct Config
{
  LogLevel  m_defaultLevel;
  char      m_path[50];
  char      m_filePath[50];

  int       m_numOfPairs;
  Pair      m_pairs[20];
}Config;

Config*   Config_ReadCurrent(const char* _configFileName);
void      Config_Destroy(Config* _configs);
LogLevel  LogLevel_Convert(char* _level);

#endif
