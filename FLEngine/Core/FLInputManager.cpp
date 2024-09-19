#include "FLInputManager.h"

namespace FLCore
{
    void FLInputManager::init(const FLUI::FLUI* inUI)
    {
        UI = inUI;
    }

    void FLInputManager::SetupInputManager(GLFWwindow* inActiveWindow)
    {
        activeWindow = inActiveWindow;
    }

    void FLInputManager::UpdateInputManager(GLFWwindow* window)
    {
        activeWindow = window;
    }
}
