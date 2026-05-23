#include <glad/glad.h>
#include "window.hpp"
#include "../logger/logger.hpp"
#include "GLFW/glfw3.h"
#include "../colors/colors.hpp"
#include <cstddef>

void Ground::Core::Window::init()
{
    if (!glfwInit())
    {
        Logger::EngineLogger::log({Logger::EngineLogType::Error, "GLFW not initialized before creating window!", CLI::Colors::RED});
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    native_window = glfwCreateWindow(data.width, data.height, data.title.c_str(), NULL, NULL);

    if (!native_window)
    {
        Logger::EngineLogger::log({Logger::EngineLogType::Error, "Window creation failed! Hardware might not support OpenGL 4.5", CLI::Colors::RED});
        return;
    }

    glfwMakeContextCurrent(native_window);

    static bool glad_initialized = false;
    if (!glad_initialized)
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            Logger::EngineLogger::EngineLogger::log({Logger::EngineLogType::Error, "Failed to initialize GLAD!", CLI::Colors::RED});
            return;
        }
        glad_initialized = true;
    }
}


void Ground::Core::Window::updateOpenGlWindow()
{
    glfwMakeContextCurrent(native_window);

    if (!glfwWindowShouldClose(native_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(native_window);
    }

    return;
}

void Ground::Core::Window::update()
{
    switch (data.backend)
    {
        case Ground::Core::WindowBackend::OpenGL:
            updateOpenGlWindow();
            break;

        case Ground::Core::WindowBackend::Vulkan:
            Logger::EngineLogger::log({Logger::EngineLogType::Error, "Vulkan backend not implemented!", CLI::Colors::RED});
            break;
    }
}

void Ground::Core::Window::close()
{
    if (native_window)
    {
        glfwDestroyWindow(native_window);
        native_window = nullptr;
    }
}
