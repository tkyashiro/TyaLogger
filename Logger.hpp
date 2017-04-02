#include "Logger.h"

#include <sstream>

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>

namespace TYA {

const static std::map<LogLevel, spdlog::level::level_enum> sMap = {
    { LogLevel::Trace   , spdlog::level::trace },
    { LogLevel::Debug   , spdlog::level::debug },
    { LogLevel::Info    , spdlog::level::info },
    { LogLevel::Warn    , spdlog::level::warn },
    { LogLevel::Error   , spdlog::level::err },
    { LogLevel::Critical, spdlog::level::critical },
};

static const bool bInitialized = [](){
    spdlog::set_pattern("[%H:%M:%S %z][%t][%n][%l] %v");
    return true;
};

class Logger::Impl
{
public:
    Impl(const std::string &name)
        : logger_(spdlog::get(name))
    {
        if (!logger_) {
#if 0
            const int maxNumOfFile = 10;
            const int maxSize = 10 /*MB*/ * 1024 * 1024;
            const std::string filename("./log.txt");
            logger_ = spdlog::rotating_logger_mt(name, filename, maxSize, maxNumOfFile); ///@todo parameterize filename, size and file number
#else
            logger_ = spdlog::stdout_logger_mt(name);
#endif
        }
    }

    std::shared_ptr<spdlog::logger> logger_;
};

Logger::Logger(const std::string &name) : impl_(new Impl(name))
{
}

Logger Logger::get(const std::string &name)
{
    return Logger(name);
}

void Logger::setLogLevel(LogLevel l)
{
    spdlog::set_level(sMap.at(l));
}

void Logger::trace(const char *file, const char *func, uint32_t line, const char *message)
{
    log(LogLevel::Trace, file, func, line, message);
}

void Logger::debug(const char *file, const char *func, uint32_t line, const char *message)
{
    log(LogLevel::Debug, file, func, line, message);
}

void Logger::info(const char *file, const char *func, uint32_t line, const char *message)
{
    log(LogLevel::Info, file, func, line, message);
}

void Logger::warn(const char *file, const char *func, uint32_t line, const char *message)
{
    log(LogLevel::Warn, file, func, line, message);
}

void Logger::error(const char *file, const char *func, uint32_t line, const char *message)
{
    log(LogLevel::Error, file, func, line, message);
}

void Logger::critical(const char *file, const char *func, uint32_t line, const char *message)
{
    log(LogLevel::Critical, file, func, line, message);
}

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

void Logger::log(LogLevel level, const char *file, const char *func, uint32_t line, const char *message)
{
    std::stringstream ss;
    ss << "[" << file << "]"
       << "[" << func << "]"
       << "[" << line << "]"
       << message;

    impl_->logger_->log(sMap.at(level), ss.str().c_str());
}

template <typename... Args>
void Logger::log(LogLevel level, const char *file, const char *func, uint32_t line, const char* fmt, const Args&... args)
{
    std::stringstream ss;
    ss << "[" << file << "]"
       << "[" << func << "]"
       << "[" << line << "]"
       << fmt;

    impl_->logger_->log(sMap.at(level), ss.str().c_str(), args... );
}


void Logger::flush()
{
    impl_->logger_->flush();
}


}