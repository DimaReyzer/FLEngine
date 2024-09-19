#include "FLWindow.h"

#include "stb_image.h"
#include <stdexcept>

namespace FLCore
{
    void FLWindow::init(uint32_t width, uint32_t height, GLFWframebuffersizefun resizeCallback)
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(width, height, "FLEngine", nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, resizeCallback);


        // Set the window icon
        int iconWidth, iconHeight, channels;
        unsigned char* pixels = stbi_load("G:/DEVPROJECTS/FLEngine/FLEngine/Textures/FLEngine.png", &iconWidth, &iconHeight, &channels, STBI_rgb_alpha);
        // Load your icon image (you can use any image-loading library like stb_image)
        GLFWimage images[1];
        images[0].pixels = pixels; // You need to load the image pixels manually
        images[0].width = iconWidth;  // Set width of the icon
        images[0].height = iconHeight; // Set height of the icon

        // Set the icon for the GLFW window
        glfwSetWindowIcon(window, 1, images);
    }

    void FLWindow::createSurface(VkInstance instance)
    {
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void FLWindow::cleanup()
    {
        glfwDestroyWindow(window);
    }
}
