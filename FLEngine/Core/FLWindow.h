#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace FLCore
{
    class FLWindow
    {
    public:
        void init(uint32_t width, uint32_t height, GLFWframebuffersizefun resizeCallback);
        void toggleFullscreen(bool bFullscreen);
        void createSurface(VkInstance instance);
        void cleanup();
        const bool shouldClose() const { return !glfwWindowShouldClose(window); }
        GLFWwindow* getWindow() const { return window; }
        VkSurfaceKHR getSurface() const { return surface; }
        void getWindowSize(int& width, int& height) const { return glfwGetWindowSize(window, &width, &height); }
    private:
        GLFWwindow* window;
        VkSurfaceKHR surface;
        int windowPosX;
        int windowPosY;
        int windowedWidth;
        int windowedHeight;
    };
}
