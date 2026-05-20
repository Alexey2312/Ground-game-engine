#include <glad/glad.h>
#include "window.hpp"
#include "../logger/logger.hpp"
#include "GLFW/glfw3.h"
#include "../colors/colors.hpp"
#include <cstddef>
#include <iostream>

void Ground::Core::Window::init()
{
    if (!glfwInit())
    {
         std::cerr << "CRITICAL: GLFW not initialized before creating window!" << std::endl;
         return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    native_window = glfwCreateWindow(data.width, data.height, data.title.c_str(), NULL, NULL);

    if (!native_window)
    {
        std::cerr << "ERROR: Window creation failed! Hardware might not support OpenGL 4.5" << std::endl;
        return;
    }

    glfwMakeContextCurrent(native_window);

    static bool glad_initialized = false;
    if (!glad_initialized)
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "ERROR: Failed to initialize GLAD. Is the context valid? Current window: " << native_window << "\n";
            return;
        }
        glad_initialized = true;
    }
}


void Ground::Core::Window::updateOpenGlWindow()
{
    glfwPollEvents();
    glfwMakeContextCurrent(native_window);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

    if (!glfwWindowShouldClose(native_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(native_window);
        glfwPollEvents();
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
            std::cerr << Ground::Core::CLI::Colors::RED << "Vulkan backend didn't implemented! \n" << Ground::Core::CLI::Colors::RESET;
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
