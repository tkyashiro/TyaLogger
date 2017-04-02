#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <memory>

namespace TYA {

enum class LogLevel
{
    Trace = 0x01,
    Debug = 0x02,
    Info  = 0x04,
    Warn  = 0x08,
    Error = 0x10,
    Critical = 0x20,
};

#define TYA_TRACE(logger, message, ...)    logger.trace(__FILE__, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define TYA_DEBUG(logger, message, ...)    logger.debug(__FILE__, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define TYA_INFO(logger, message, ...)     logger.info(__FILE__, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define TYA_WARN(logger, message, ...)     logger.warn(__FILE__, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define TYA_ERROR(logger, message, ...)    logger.error(__FILE__, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define TYA_CRITICAL(logger, message, ...) logger.critical(__FILE__, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)

class Logger
{
public:
    static Logger get(const std::string &name = std::string());
    static void setLogLevel(LogLevel l);

    inline void trace(const char *file, const char *func, uint32_t line, const char *message);
    inline void debug(const char *file, const char *func, uint32_t line, const char *message);
    inline void info(const char *file, const char *func, uint32_t line, const char *message);
    inline void warn(const char *file, const char *func, uint32_t line, const char *message);
    inline void error(const char *file, const char *func, uint32_t line, const char *message);
    inline void critical(const char *file, const char *func, uint32_t line, const char *message);

    template <typename... Args> void trace(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args);
    template <typename... Args> void debug(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args);
    template <typename... Args> void info(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args);
    template <typename... Args> void warn(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args);
    template <typename... Args> void error(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args);
    template <typename... Args> void critical(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args);

    void flush();

protected:
    void log(LogLevel level, const char *file, const char *func, uint32_t line, const char *message);
    template <typename... Args> void log(LogLevel level, const char *file, const char *func, uint32_t line, const char* fmt, const Args&... args);
private:
    Logger(const std::string &name = std::string());
private:
    class Impl;
    std::shared_ptr<Impl> impl_;
};

}

#include "Logger.hpp"

#endif
