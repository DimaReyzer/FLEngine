#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>
#include <glm/vec2.hpp>

#include "UI/FLUI.h"

namespace FLCore
{
    class FLInputManager
    {
    public:
        void init(const FLUI::FLUI* inUI);
        void SetupInputManager(GLFWwindow* inActiveWindow);
        void UpdateInputManager(GLFWwindow* window);

        GLFWwindow* getActiveWindow() const { return  activeWindow; }
        const FLUI::FLUI* getUI() const { return UI; }
    private:
        const FLUI::FLUI* UI;
        GLFWwindow* activeWindow;
        glm::vec2 lastMousePosition;
    };
}
