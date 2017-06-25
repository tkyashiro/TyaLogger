#include "Logger.h"

#include <sstream>

#include <spdlog/sinks/file_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

static const bool bInitialized = []() {
    spdlog::set_pattern("[%H:%M:%S %z][%t][%n][%l] %v");
    spdlog::set_async_mode(2 ^ 16, spdlog::async_overflow_policy::block_retry,
        nullptr, std::chrono::milliseconds(500));
    return true;
};

namespace TYA {

std::string Logger::theLogFilePath_ = "./log.txt";
static const char* loggerName = "tya";

Logger::Logger()
    : logger_(spdlog::get(loggerName))
{
    if (!logger_) {
#if 1
        const int maxNumOfFile = 10;
        const int maxSize = 10 /*MB*/ * 1024 * 1024;
        auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(theLogFilePath_, maxSize, maxNumOfFile);

        auto stdoutSink = std::make_shared<spdlog::sinks::stdout_sink_mt>();

        logger_ = spdlog::create(loggerName, { fileSink, stdoutSink });
#else
        logger_ = spdlog::rotating_logger_mt("default", theLogFilePath_, maxSize, maxNumOfFile);
#endif
        logger_->flush_on(spdlog::level::info);
    }
}

void Logger::setLogLevel(LogLevel l)
{
    spdlog::set_level(map(l));
}

void Logger::setLogFilePath(const std::string& path)
{
    theLogFilePath_ = path;
}

void Logger::trace(const char* file, const char* func, uint32_t line, const char* message)
{
    log(LogLevel::Trace, file, func, line, message);
}

void Logger::debug(const char* file, const char* func, uint32_t line, const char* message)
{
    log(LogLevel::Debug, file, func, line, message);
}

void Logger::info(const char* file, const char* func, uint32_t line, const char* message)
{
    log(LogLevel::Info, file, func, line, message);
}

void Logger::warn(const char* file, const char* func, uint32_t line, const char* message)
{
    log(LogLevel::Warn, file, func, line, message);
}

void Logger::error(const char* file, const char* func, uint32_t line, const char* message)
{
    log(LogLevel::Error, file, func, line, message);
}

void Logger::critical(const char* file, const char* func, uint32_t line, const char* message)
{
    log(LogLevel::Critical, file, func, line, message);
}

std::string Logger::format(const char* file, const char* func, uint32_t line, const char* message)
{
    std::stringstream ss;
    ss << "[" << file << "]"
       << "[" << func << "]"
       << "[" << line << "]"
       << message;
    return ss.str();
}

spdlog::level::level_enum Logger::map(LogLevel l)
{
    const static std::map<LogLevel, spdlog::level::level_enum> sMap = {
        { LogLevel::Trace, spdlog::level::trace },
        { LogLevel::Debug, spdlog::level::debug },
        { LogLevel::Info, spdlog::level::info },
        { LogLevel::Warn, spdlog::level::warn },
        { LogLevel::Error, spdlog::level::err },
        { LogLevel::Critical, spdlog::level::critical },
    };
    return sMap.at(l);
}

void Logger::log(LogLevel level, const char* file, const char* func, uint32_t line, const char* message)
{
    logger_->log(map(level), format(file, func, line, message).c_str());
}

void Logger::flush()
{
    logger_->flush();
}
}
