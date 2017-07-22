#ifndef __LOGLEVEL_H__
#define __LOGLEVEL_H__
typedef enum
{
  LOG_TRACE = 0,
  LOG_DEBUG,
  LOG_INFO,
  LOG_WARNING,
  LOG_ERROR,
  LOG_CRITICAL,
  LOG_SEVERE,
  LOG_FATAL,
  LOG_NONE
}LogLevel;

#endif /* __LOGLEVEL_H__ */
