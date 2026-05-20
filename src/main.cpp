#include "core/application/application.hpp"
#include "core/window/window.hpp"
#include <memory>

int main()
{
    Ground::Application app;
    auto window1 = std::make_unique<Ground::Core::Window>(Ground::Core::WindowData("Ground Engine"), true);
    auto window2 = std::make_unique<Ground::Core::Window>(Ground::Core::WindowData("Ground Engine 2"), true);
    app.addWindow(std::move(window1));
    app.addWindow(std::move(window2));

    app.run();

    return 0;
}
