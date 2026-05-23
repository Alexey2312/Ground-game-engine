#include <glad/glad.h>
#include "application.hpp"
#include "GLFW/glfw3.h"

void Ground::Application::run()
{
    is_running = true;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

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
            glfwTerminate();
            return;
        }
    }
    glfwTerminate();
}
