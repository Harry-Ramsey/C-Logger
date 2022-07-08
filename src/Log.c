#include "Log.h"

static FILE *LOG_FILE = NULL;

static LogLevel LOG_LEVEL = TRACE;

void log_write(LogLevel level, char *file, int line, char *msg, ...)
{
    if (level <= LOG_LEVEL)
    {
        /* Generate a timestamp. */
        time_t t = time(0);
        struct tm *stamp = localtime(&t);
        fprintf(stdout, "%d-%d-%d %d:%d:%d\t", (stamp->tm_year + 1900), (stamp->tm_mon + 1), stamp->tm_mday, stamp->tm_hour, stamp->tm_min, stamp->tm_sec);

        /* Print verbose logger information . */
        fprintf(stdout, "%s\t%s:%d\t", LevelNames[level - 1], file, line);
        /* Print variable arguement list formatted. */
        va_list list;
        va_start(list, msg);
        vfprintf(stdout, msg, list);
        va_end(list);

        fprintf(stdout, "\n");

        if (LOG_FILE != NULL)
        {
            fprintf(LOG_FILE, "%d-%d-%d %d:%d:%d\t", (stamp->tm_year + 1900), (stamp->tm_mon + 1), stamp->tm_mday, stamp->tm_hour, stamp->tm_min, stamp->tm_sec);
            fprintf(LOG_FILE, "%s\t%s:%d\t", LevelNames[level - 1], file, line);
            /* New va_list as previous was consumed.*/
            va_start(list, msg);
            vfprintf(LOG_FILE, msg, list);
            va_end(list);

            fprintf(LOG_FILE, "\n");
            /* Force stream to be written to file in case of crash. */
            fflush(LOG_FILE);
        }
    }
}

void log_set_level(LogLevel level)
{
    LOG_LEVEL = level;
}

LogLevel log_get_level(void)
{
    return LOG_LEVEL;
}

void log_set_file(FILE *file)
{
    /* LOG_FILE can be null to disable logging to a file. */
    LOG_FILE = file;
}