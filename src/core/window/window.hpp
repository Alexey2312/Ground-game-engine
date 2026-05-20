#pragma once

#include "GLFW/glfw3.h"
#include <cstdint>
#include <string>

namespace Ground::Core
{

enum class WindowBackend
{
    OpenGL = 0,
    Vulkan = 1
};

struct WindowData
{
    int width;
    int height;
    std::string title;

    WindowBackend backend = WindowBackend::OpenGL;

    WindowData(std::string t = "Ground Engine", int w = 1280, int h = 720, WindowBackend this_backend = WindowBackend::OpenGL) : title(t), width(w), height(h), backend(this_backend) {}
};

class Window
{
    bool is_available_for_rendering = false;
    WindowData data;
    GLFWwindow* native_window = nullptr;
public:
    void updateOpenGlWindow();
    void update(); // You should call this method every frame!
    void init();

    void close();

    bool shouldClose() {return glfwWindowShouldClose(native_window);}

    int32_t width() const {return data.width;}
    void setWidth(int32_t new_width) {data.width = new_width;}

    int32_t height() const {return data.height;}
    void setHeight(int32_t new_height) {data.height = new_height;}

    bool isAvailableForRendering() const {return is_available_for_rendering;}
    void setAvailableForRendering(bool available) {is_available_for_rendering = available;}

    GLFWwindow* nativeWindow() const {return native_window;}

    Window(WindowData this_data, bool available_for_rendering) : data(this_data), is_available_for_rendering(available_for_rendering) {init();}

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&& other) noexcept : native_window(other.native_window), data(std::move(other.data)), is_available_for_rendering(other.is_available_for_rendering) {other.native_window = nullptr;}
    Window& operator=(Window&& other) noexcept = default;

    ~Window()
    {
        if (native_window)
        {
            glfwDestroyWindow(native_window);
            native_window = nullptr;
        }
    }
};

}; // namespace Ground::Core
