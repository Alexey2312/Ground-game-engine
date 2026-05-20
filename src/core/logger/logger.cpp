#include "../colors/colors.hpp"
#include "logger.hpp"
#include <iostream>

void Ground::Core::Logger::StandardOutput::printLog(Ground::Core::Logger::Log log)
{
    std::array<std::string_view, 3> types_names = {"ERROR", "WARNING", "INFO"};
    std::cout << log.color << "[" << types_names.at((int)log.type) << "]" << " " << log.message << Ground::Core::CLI::Colors::RESET << "\n";
}

void Ground::Core::Logger::ErrorOutput::printLog(Ground::Core::Logger::Log log)
{
    std::array<std::string_view, 3> types_names = {"ERROR", "WARNING", "INFO"};
    std::cerr << log.color << "[" << types_names.at((int)log.type) << "]" << " " << log.message << Ground::Core::CLI::Colors::RESET << "\n";
}

void Ground::Core::Logger::EngineLogger::log(Log log)
{
    OutputDevice old_device = device;
    logs.emplace_back(log);
    if (log.type == Ground::Core::Logger::EngineLogType::Error)
    {
        device = ErrorOutput();
    }

    std::visit([&](auto& output)
    {
        output.printLog(log);
    }, device);

    device = old_device;
}

void Ground::Core::Logger::EngineLogger::printAllLogs()
{
    std::visit([&](auto& output)
    {
        for (auto& log : logs)
        {
            output.printLog(log);
        }
    }, device);
}
