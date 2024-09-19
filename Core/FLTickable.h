#pragma once

#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "FLInputManager.h"

namespace FLCore
{
    struct FLTransform {
        glm::vec3 position;
        glm::vec3 rotation; // Store rotation in Euler angles (pitch, yaw, roll)
        glm::vec3 scale;

        FLTransform()
            : position(0.0f, 0.0f, 0.0f),
              rotation(0.0f, 0.0f, 0.0f),
              scale(1.0f, 1.0f, 1.0f) {}

        glm::mat4 getRotationMatrix() const {
            // Convert Euler angles (rotation) to a rotation matrix
            glm::quat quaternion = glm::quat(radians(rotation));
            return toMat4(quaternion);
        }
        glm::vec3 getForwardVector() const {
            // Forward direction is -Z in OpenGL's right-handed coordinate system
            //return glm::vec3(0.0f, 1.0f, 0.0f);
            return normalize(getRotationMatrix() * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
        }
        glm::vec3 getRightVector() const {
            // Right direction is +X
            return normalize(getRotationMatrix() * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
        }
        glm::vec3 getUpVector() const {
            // Up direction is +Y
            return normalize(getRotationMatrix() * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
        }
        glm::vec3 getBackwardVector() const { return -getForwardVector(); }
        glm::vec3 getLeftVector() const { return -getRightVector(); }
        glm::vec3 getDownVector() const { return -getUpVector(); }
    };
    
    class FLTickable
    {
    public:
        virtual void SetupInputManager(FLInputManager* inInputManager);
        virtual void Tick(const float deltaTime) = 0;
        const FLTransform& getTransform() const { return transform; }
    protected:
        FLTransform transform;
        FLInputManager* inputManager;
    };
}
