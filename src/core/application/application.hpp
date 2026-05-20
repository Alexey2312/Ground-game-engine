#pragma once
#include <memory>
#include <vector>
#include "../window/window.hpp"

namespace Ground
{

class Application
{
    bool is_running = false;
    std::vector<std::unique_ptr<Ground::Core::Window>> windows = {};
public:
    void addWindow(std::unique_ptr<Ground::Core::Window> new_window) {windows.emplace_back(std::move(new_window));}
    void run();

    bool isRunning() const {return is_running;}
    void setIsRunning(bool running) {is_running = running;}
    void close();

    Application() {}
};

}; // namespace Ground
