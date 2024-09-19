#include "FLUI.h"

#include "../FLApp.h"

namespace FLUI
{
    void FLUI::init(FLCore::FLWindow* inWindow, VkInstance inInstance, VkDevice inDevice,
        VkPhysicalDevice inPhysicalDevice, VkQueue inGraphicsQueue, VkCommandPool inCommandPool,
        VkDescriptorPool inDescriptorPool, VkRenderPass inRenderPass, uint32_t inImageCount)
    {
        window = inWindow;
        instance = inInstance;
        device = inDevice;
        physicalDevice = inPhysicalDevice;
        graphicsQueue = inGraphicsQueue;
        commandPool = inCommandPool;
        descriptorPool = inDescriptorPool;
        renderPass = inRenderPass;
        imageCount = inImageCount;

        // Create ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();  // Retrieve the IO handle (for setting flags, input, etc.)
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable keyboard controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking
        io.Fonts->Clear();
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-Regular.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-Bold.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-BoldItalic.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-ExtraLight.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-ExtraLightItalic.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-Italic.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-Light.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-LightItalic.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-Medium.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-MediumItalic.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-SemiBold.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-SemiBoldItalic.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-Thin.ttf", 14);
        io.Fonts->AddFontFromFileTTF("G:/DEVPROJECTS/FLEngine/FLEngine/Fonts/RobotoMono/static/RobotoMono-ThinItalic.ttf", 14);
        io.Fonts->Build();

        ImGui_ImplGlfw_InitForVulkan(window->getWindow(), true);
        
        // ImGui initialization
        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = instance;  // Your Vulkan instance
        init_info.PhysicalDevice = physicalDevice;  // Your Vulkan physical device
        init_info.Device = device;  // Your Vulkan logical device
        init_info.QueueFamily = FLCore::FLApp::findQueueFamilies(physicalDevice, window->getSurface()).graphicsFamily.value();  // Queue family used for the graphics commands
        init_info.Queue = graphicsQueue;  // Vulkan queue for graphics commands
        init_info.DescriptorPool = descriptorPool;  // Descriptor pool to allocate descriptors for imgui
        init_info.RenderPass = renderPass;
        init_info.Allocator = nullptr;  // Optional allocator callbacks for Vulkan

        // Specify the number of in-flight frames (swapchain image count)
        init_info.MinImageCount = FLCore::FLApp::querySwapChainSupport(physicalDevice, window->getSurface()).capabilities.minImageCount;  
        init_info.ImageCount = imageCount;  // Image count for swapchain
        
        // Initialize Vulkan ImGui backend
        vkDeviceWaitIdle(device);
        ImGui_ImplVulkan_Init(&init_info);
        applyStyle();
    }

    void FLUI::applyStyle()
    {
        ImGuiStyle& GuiStyle = ImGui::GetStyle();
        ImVec4* colors = GuiStyle.Colors;
        colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
        colors[ImGuiCol_Border]                 = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg]                = AdjustColor(preferedColor, 0.2f, 0.50f);
        colors[ImGuiCol_FrameBgHovered]         = AdjustColor(preferedColor, 0.4f, 0.75f);
        colors[ImGuiCol_FrameBgActive]          = AdjustColor(preferedColor, 0.5f, 0.75f);
        colors[ImGuiCol_TitleBg]                = AdjustColor(preferedColor, 0.2f, 0.94f);
        colors[ImGuiCol_TitleBgActive]          = AdjustColor(preferedColor, 0.22f, 0.94f);
        colors[ImGuiCol_TitleBgCollapsed]       = AdjustColor(preferedColor, 0.2f, 0.50f);
        colors[ImGuiCol_MenuBarBg]              = AdjustColor(preferedColor, 0.15f, 0.50f);
        colors[ImGuiCol_ScrollbarBg]            = AdjustColor(preferedColor, 0.15f, 0.50f);
        colors[ImGuiCol_ScrollbarGrab]          = AdjustColor(preferedColor, 0.65f, 0.75f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = AdjustColor(preferedColor, 0.72f, 0.94f);
        colors[ImGuiCol_ScrollbarGrabActive]    = AdjustColor(preferedColor, 0.80f, 1.00f);
        colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrab]             = AdjustColor(preferedColor, 0.85f, 1.00f);
        colors[ImGuiCol_SliderGrabActive]       = AdjustColor(preferedColor, 0.90f, 1.00f);
        colors[ImGuiCol_Button]                 = AdjustColor(preferedColor, 0.75f, 0.40f);
        colors[ImGuiCol_ButtonHovered]          = AdjustColor(preferedColor, 1.0f, 1.00f);
        colors[ImGuiCol_ButtonActive]           = AdjustColor(preferedColor, 0.90f, 1.00f);
        colors[ImGuiCol_Header]                 = AdjustColor(preferedColor, 1.0f, 0.31f);
        colors[ImGuiCol_HeaderHovered]          = AdjustColor(preferedColor, 1.0f, 0.80f);
        colors[ImGuiCol_HeaderActive]           = AdjustColor(preferedColor, 1.0f, 1.00f);
        colors[ImGuiCol_Separator]              = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
        colors[ImGuiCol_SeparatorHovered]       = AdjustColor(preferedColor, 0.5f, 0.78f);
        colors[ImGuiCol_SeparatorActive]        = AdjustColor(preferedColor, 0.5f, 1.00f);
        colors[ImGuiCol_ResizeGrip]             = AdjustColor(preferedColor, 1.0f, 0.20f);
        colors[ImGuiCol_ResizeGripHovered]      = AdjustColor(preferedColor, 1.0f, 0.67f);
        colors[ImGuiCol_ResizeGripActive]       = AdjustColor(preferedColor, 1.0f, 0.95f);
        colors[ImGuiCol_TabHovered]             = AdjustColor(preferedColor, 1.0f, 0.80f);
        colors[ImGuiCol_Tab]                    = AdjustColor(preferedColor, 0.75f, 0.86f);
        colors[ImGuiCol_TabSelected]            = AdjustColor(preferedColor, 0.80f, 1.00f);
        colors[ImGuiCol_TabSelectedOverline]    = AdjustColor(preferedColor, 1.0f, 1.00f);
        colors[ImGuiCol_TabDimmed]              = AdjustColor(preferedColor, 0.35f, 0.97f);
        colors[ImGuiCol_TabDimmedSelected]      = AdjustColor(preferedColor, 0.55f, 1.00f);
        colors[ImGuiCol_TabDimmedSelectedOverline]  = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered]       = AdjustColor(preferedColor, 1.0f, 1.00f);
        colors[ImGuiCol_PlotHistogram]          = ImVec4(1.000f, 0.753f, 0.000f, 0.753f);
        colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg]          = AdjustColor(preferedColor, 0.1f, 0.80f);
        colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
        colors[ImGuiCol_TableBorderLight]       = AdjustColor(preferedColor, 0.5f, 0.25f);
        colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.03f);
        colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.02f);
        colors[ImGuiCol_TextLink]               = AdjustColor(preferedColor, 1.0f, 1.00f);
        colors[ImGuiCol_TextSelectedBg]         = AdjustColor(preferedColor, 1.0f, 0.35f);
        colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        // Rounding(disable rounding)
        GuiStyle.ChildRounding                  = 0.0f;
        GuiStyle.FrameRounding                  = 0.0f;
        GuiStyle.GrabRounding                   = 0.0f;
        GuiStyle.PopupRounding                  = 0.0f;
        GuiStyle.ScrollbarRounding              = 0.0f;
        GuiStyle.TabRounding                    = 0.0f;
        GuiStyle.WindowRounding                 = 0.0f;
        // Paddings
        GuiStyle.WindowPadding                  = ImVec2(8,4);
        GuiStyle.FramePadding                   = ImVec2(4,2);
        GuiStyle.ItemSpacing                    = ImVec2(4,2);
        GuiStyle.ItemInnerSpacing               = ImVec2(2,2);
        GuiStyle.IndentSpacing                  = 8;
        GuiStyle.ScrollbarSize                  = 14;
        GuiStyle.GrabMinSize                    = 12;
        GuiStyle.CellPadding                    = ImVec2(2,2);
        GuiStyle.TableAngledHeadersAngle        = 50;
        GuiStyle.TableAngledHeadersTextAlign    = ImVec2(0.5f,0.0f);
        GuiStyle.SeparatorTextBorderSize        = 1;
        GuiStyle.SeparatorTextPadding           = ImVec2(20,2);
    }

    void FLUI::pushViewportDrawCommands()
    {
        return; // Disable
        // Create a new ImGui window to render the 3D viewport
        ImGui::Begin("3D Viewport");

        // Get window position (top-left corner)
        viewportPos = ImGui::GetWindowPos();

        // Get window size (width and height)
        viewportSize = ImGui::GetWindowSize();

        // Vulkan 3D rendering to offscreen image or swapchain
        //ImGui::Image((void*)(intptr_t)imguiTextureDescriptorSet, viewportPanelSize);

        ImGui::End();
    }

    void FLUI::preferedColorPushDrawCommands()
    {
        // Create an ImGui window for recording command buffer
        if (ImGui::Begin("Command Buffer Recording")) 
        {
            // Show color picker for preferedColor
            if (ImGui::ColorEdit4("Preferred Color", (float*)&preferedColor)) 
            {
                // Optional: Perform some action when the color changes
                // For example, update the command buffer
                applyStyle();
            }

            // Proceed with recording command buffer...
        }
        ImGui::End();
    }

    void FLUI::pushDrawCommands(VkCommandBuffer commandBuffer)
    {
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();  // If using GLFW
        ImGui::NewFrame();

        pushViewportDrawCommands();
        preferedColorPushDrawCommands();
        ImGui::ShowDemoWindow();
        
        ImGui::Render();  // Render ImGui elements
        // Record ImGui commands in the command buffer
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
    }

    const ImGuiIO& FLUI::getGuiIO() const
    {
        return ImGui::GetIO();
    }

    void FLUI::cleanup()
    {
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
