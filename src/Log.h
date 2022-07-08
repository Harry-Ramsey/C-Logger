#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define LOG_TRACE(...)  log_write(TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)   log_write(INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...)  log_write(DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)   log_write(WARN, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...)  log_write(ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...)  log_write(FATAL, __FILE__, __LINE__, __VA_ARGS__)

typedef enum {
    OFF,
    FATAL,
    ERROR,
    WARN,
    DEBUG,
    INFO,
    TRACE
} LogLevel;

const char* LevelNames[] = {"FATAL", "ERROR", "WARN", "DEBUG", "INFO", "TRACE"};

static const char* LevelColours [] = {"\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"};

void log_write(LogLevel level, char *file, int line, char *msg, ...);
void log_set_level(LogLevel level);
void log_set_file(FILE *file);
LogLevel log_get_level(void);

#endif