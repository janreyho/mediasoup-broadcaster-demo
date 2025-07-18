
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h>
    #include <time.h>
#else
    #include <sys/time.h>  // 用于 gettimeofday 获取毫秒
#endif
#include "hx_log.hpp"

FILE *logFile = NULL;
static HxLog::LogLevel currentLogLevel = HxLog::hxDEBUG;
static HxLog::LogLevel printLogLevel = HxLog::hxINFO;
char logFilePath[256] = "./log/hx5gSDK.asn";  // 存储日志文件的路径
char timeFormat[64] = "%Y-%m-%d %H:%M:%S";  // 默认时间格式

// 设置当前日志等级的函数
void setLogLevel(HxLog::LogLevel level, const char* filePath) {
    currentLogLevel = level;
    strncpy(logFilePath, filePath, sizeof(logFilePath) - 1);
    logFilePath[sizeof(logFilePath) - 1] = '\0';  // 确保字符串以空字符结尾
    initLogFile(logFilePath);
}

void initLogFile(const char* filePath) {
    if (logFile == NULL) {
        logFile = fopen(filePath, "a");
        if (logFile == NULL) {
            printf("initLogFile Error opening log file: %s\n", filePath);
        }
    }
}

// 关闭日志文件
void closeLogFile() {
    if (logFile != NULL) {
        fclose(logFile);
        logFile = NULL;
    }
}

// 获取当前时间字符串，包括毫秒
void getCurrentTimeWithMillis(char* buffer, size_t size) {
#ifdef _WIN32
    SYSTEMTIME st;
    GetLocalTime(&st);  // 获取本地时间，包括毫秒

    // 格式化时间部分
    char timeBuffer[64];
    struct tm timeinfo;
    time_t rawtime = time(NULL);
    localtime_s(&timeinfo, &rawtime);  // 线程安全的 localtime 版本

    // 格式化时间部分（不包括毫秒）
    strftime(timeBuffer, sizeof(timeBuffer), timeFormat, &timeinfo);

    // 加上毫秒部分
    snprintf(buffer, size, "%s.%03d", timeBuffer, st.wMilliseconds);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);  // 获取当前时间，包括秒和微秒

    struct tm* timeinfo;
    timeinfo = localtime(&tv.tv_sec);  // 将秒部分转为本地时间

    // 格式化时间部分（不包括毫秒）
    char timeBuffer[64];
    strftime(timeBuffer, sizeof(timeBuffer), timeFormat, timeinfo);

    // 加上毫秒部分
    int milliseconds = tv.tv_usec / 1000;
    snprintf(buffer, size, "%s.%03d", timeBuffer, milliseconds);
#endif
}

void logMessageExt(HxLog::LogLevel level, const char *file, int line,  const char *format, ...) {
    const char* pos = strstr(file, PROJECT_ROOT);
    if (pos != NULL) {
        // 计算相对路径的开始位置
        file = pos + strlen(PROJECT_ROOT);
    }

    const char *levelStr;
    if (level >= currentLogLevel) {
        switch (level) {
            case HxLog::hxDEBUG: levelStr = "debug"; break;
            case HxLog::hxINFO: levelStr = "info"; break;
            case HxLog::hxWARNING: levelStr = "warning"; break;
            case HxLog::hxERROR: levelStr = "error"; break;
            case HxLog::hxNONE: levelStr = "none"; break;
            default: levelStr = "UNKNOWN"; break;
        }
    }
    else 
        return;

    va_list args;
    va_start(args, format);

    char currentTime[64]={0};
    getCurrentTimeWithMillis(currentTime, sizeof(currentTime));
    if (logFile != NULL) {
        fprintf(logFile, "[%s] [%s] (%s:%d) ", currentTime, levelStr, file, line);
        vfprintf(logFile, format, args);
        fprintf(logFile, "\n");
    } else {
        printf("logMessageExt Error opening log file: %s\n", logFilePath);
    }
    if(level >= printLogLevel){
        printf("[%s] [%s] (%s:%d) ", currentTime, levelStr, file, line);
        vprintf(format, args);
        printf("\n");
    }
    fflush(logFile);
    va_end(args);
}
