#pragma once

#include "FLTickable.h"

namespace FLCore
{
    class FLCamera : FLTickable
    {
    public:
        void Tick(const float deltaTime) override;
        void SetupInputManager(FLInputManager* inInputManager) override;
        glm::mat4 GetViewMatrix();
        
    private:
        float speed = 2.0f;
        float sensitivity = 0.1f;
    };
}
