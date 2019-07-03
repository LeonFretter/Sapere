#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class Instance {
private:
    VkInstance _instance;
    VkDebugUtilsMessengerEXT _debugMessenger;

    const std::vector<const char*> _validationLayers = {
        "VK_LAYER_LUNARG_standard_validation"
    };
    const bool _enableValidationLayers = true;
public:
    Instance();
    ~Instance();

    void initVulkan();
    void createInstance();
    void cleanup();
    void setupDebugMessenger();

    bool checkValidationLayerSupport();

    std::vector<const char*> getRequiredExtensions();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    );
private:
};