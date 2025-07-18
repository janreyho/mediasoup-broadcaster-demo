#ifndef __HX_LOG_H__
#define __HX_LOG_H__

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
// #include "IHx5gSDKTypeDef.hpp"

namespace HxLog {
enum LogLevel {
    hxDEBUG,
    hxINFO,
    hxWARNING,
    hxERROR,
    hxNONE,
};
}

#define HX_DEBUG  // 开启则启动本地、远端渲染，关闭则输出远端 YUV

#define LOG_MESSAGE(levelStr, format, ...) \
    logMessageExt(levelStr, __FILE__, __LINE__, format, ##__VA_ARGS__)

void setLogLevel(HxLog::LogLevel level, const char* filePath);
void logMessageExt(HxLog::LogLevel level, const char *file, int line,  const char *format, ...);
void initLogFile(const char* filePath);
void closeLogFile();

#endif