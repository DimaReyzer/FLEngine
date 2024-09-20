#pragma once
#include <vulkan/vulkan_core.h>

#include "../FLWindow.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_vulkan.h"

namespace FLUI
{
    class FLUI
    {
    public:
        
    public:
        void init(FLCore::FLWindow* inWindow, VkInstance inInstance, VkDevice inDevice, VkPhysicalDevice inPhysicalDevice,
            VkQueue inVkQueue, VkCommandPool inCommandPool, VkDescriptorPool inDescriptorPool, VkRenderPass inRenderPass, uint32_t inImageCount);
        void applyStyle();
        void pushMainDockspace();
        void preferedColorPushDrawCommands();
        void pushDrawCommands(VkCommandBuffer commandBuffer);
        // Input data
        const ImGuiIO& getGuiIO() const;
        void onFramebufferResized();
        // Function to adjust colors by applying coefficients
        static ImVec4 AdjustColor(ImVec4 base, float coeff, float alpha = 1.0f) {
            return ImVec4(base.x * coeff, base.y * coeff, base.z * coeff, alpha);
        }
        void cleanup();

    private:
        FLCore::FLWindow* window;
        VkInstance instance;
        VkDevice device;
        VkPhysicalDevice physicalDevice;
        VkQueue graphicsQueue;
        VkCommandPool commandPool;
        VkDescriptorPool descriptorPool;
        VkRenderPass renderPass;
        uint32_t imageCount;

        ImVec4 preferedColor = ImVec4(0.000f, 0.063f, 0.125f, 1.000f); // Preferred base color
        ImVec2 viewportPos;
        ImVec2 viewportSize;
        bool bFullscreenMode;
        bool bFramebufferResized;
        //FLAssetManager assetManagerWidget{};
    };
}
