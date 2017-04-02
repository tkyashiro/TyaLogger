#include "Logger.h"

#include <sstream>

#include <spdlog/logger.h>

namespace TYA {

template <typename... Args> void Logger::trace(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args)
{
    log(LogLevel::Trace, file, func, line, fmt, args...);
}

template <typename... Args> void Logger::debug(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args){
    log(LogLevel::Debug, file, func, line, fmt, args...);
}

template <typename... Args> void Logger::info(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args){
    log(LogLevel::Info, file, func, line, fmt, args...);
}

template <typename... Args> void Logger::warn(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args){
    log(LogLevel::Warn, file, func, line, fmt, args...);
}

template <typename... Args> void Logger::error(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args){
    log(LogLevel::Error, file, func, line, fmt, args...);
}

template <typename... Args> void Logger::critical(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args){
    log(LogLevel::Critical, file, func, line, fmt, args...);
}

template <typename... Args>
void Logger::log(LogLevel level, const char *file, const char *func, uint32_t line, const char* fmt, const Args&... args)
{
    logger_->log(map(level), format(file, func, line, fmt).c_str(), args... );
}


}
