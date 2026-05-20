#include <glad/glad.h>
#include "application.hpp"

void Ground::Application::run()
{
    is_running = true;

    while (is_running && !windows.empty())
    {
        glfwPollEvents();

        for (auto it = windows.begin(); it != windows.end();)
        {
            if ((*it)->shouldClose())
            {
                (*it)->close();
                it = windows.erase(it);
            }
            else
            {
                (*it)->update();
                ++it;
            }
        }

        if (windows.empty())
        {
            is_running = false;
            return;
        }
    }
}
