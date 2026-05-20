#pragma once

#include <string>
#include <variant>
#include <vector>

namespace Ground::Core::Logger
{

#ifndef NDEBUG
    #define LOG_INFO(...)  Ground::Core::EngineLogger::Get().log(Ground::Core::EngineLogType::Info, __VA_ARGS__)
    #define LOG_WARN(...)  Ground::Core::EngineLogger::Get().log(Ground::Core::EngineLogType::Warning, __VA_ARGS__)
    #define LOG_ERROR(...) Ground::Core::EngineLogger::Get().log(Ground::Core::EngineLogType::Error, __VA_ARGS__)
#else
    #define LOG_INFO(...)
    #define LOG_WARN(...)
    #define LOG_ERROR(...)
#endif

enum class EngineLogType
{
    Error = 0,
    Warning = 1,
    Info = 2,
};

struct Log
{
    EngineLogType type;
    std::string message;
    std::string color;
};

class StandardOutput
{
public:
    void printLog(Log log);
};

class ErrorOutput
{
public:
    void printLog(Log log);
};

using OutputDevice = std::variant<StandardOutput, ErrorOutput>;

class EngineLogger
{
    static inline OutputDevice device;
    static inline std::vector<Log> logs{};
public:
    static OutputDevice& currentDevice() {return device;}
    static void setDevice(OutputDevice new_device) {device = new_device;}

    static std::vector<Log>& allLogs() {return logs;}
    static void clearLogs() {logs.clear();}

    static void log(Log log);
    static void printAllLogs();
};

}; // namespace Ground::Core::Logger
