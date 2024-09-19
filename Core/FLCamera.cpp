#include "FLCamera.h"
#include "FLInputManager.h"

namespace FLCore
{
    void FLCamera::Tick(const float deltaTime)
    {
        // Camera movement
        if (glfwGetKey(inputManager->getActiveWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            transform.position += transform.getForwardVector() * speed * deltaTime;
        }
        if (glfwGetKey(inputManager->getActiveWindow(), GLFW_KEY_S) == GLFW_PRESS) {
            transform.position += transform.getBackwardVector() * speed * deltaTime;
        }
        if (glfwGetKey(inputManager->getActiveWindow(), GLFW_KEY_D) == GLFW_PRESS) {
            transform.position += transform.getRightVector() * speed * deltaTime;
        }
        if (glfwGetKey(inputManager->getActiveWindow(), GLFW_KEY_A) == GLFW_PRESS) {
            transform.position += transform.getLeftVector() * speed * deltaTime;
        }
        if (glfwGetKey(inputManager->getActiveWindow(), GLFW_KEY_SPACE) == GLFW_PRESS ||
            glfwGetKey(inputManager->getActiveWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
            transform.position += transform.getUpVector() * speed * deltaTime;
            }
        if (glfwGetKey(inputManager->getActiveWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
            glfwGetKey(inputManager->getActiveWindow(), GLFW_KEY_E) == GLFW_PRESS) {
            transform.position += transform.getDownVector() * speed * deltaTime;
            }
        if (glfwGetKey(inputManager->getActiveWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
            transform.rotation.z -= sensitivity * deltaTime;
        }
        if (glfwGetKey(inputManager->getActiveWindow(), GLFW_KEY_E) == GLFW_PRESS) {
            transform.rotation.z += sensitivity * deltaTime;
        }
        // Mouse look
        // Adjust the camera's yaw and pitch based on the mouse delta
        
        ImVec2 deltaMouse = inputManager->getUI()->getGuiIO().MouseDelta;
        transform.rotation.z -= deltaMouse.x * sensitivity; // Yaw (rotate around Y axis)
        transform.rotation.x -= deltaMouse.y * sensitivity; // Pitch (rotate around X axis)
        // Clamp the pitch to prevent the camera from flipping over
        if (transform.rotation.x > 90.0f) {
            transform.rotation.x = 90.0f;
        }
        if (transform.rotation.x < -90.0f) {
            transform.rotation.x = -90.0f;
        }
    }

    void FLCamera::SetupInputManager(FLInputManager* inInputManager)
    {
        FLTickable::SetupInputManager(inInputManager);
    }

    glm::mat4 FLCamera::GetViewMatrix()
    {
        return lookAt(transform.position, transform.position + transform.getForwardVector(), transform.getUpVector());
    }
}
