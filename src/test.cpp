#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <stdio.h>
#include <iostream>

#define DEBUG_BUILD true

class Test {
private:
    VkInstance _instance;

public:
    Test() {

    }
    ~Test() {

    }
    void initVulkan() {
        createInstance();
        setupDebug();
    }
    void createInstance() {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Test";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.apiVersion = VK_API_VERSION_1_1;

        std::vector<const char*> enabledLayers;
        std::vector<const char*> enabledExtensions;

        enabledExtensions.push_back("VK_KHR_surface");
        enabledLayers.push_back("VK_LAYER_LUNARG_standard_validation");
        enabledExtensions.push_back("VK_EXT_debug_report");

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(enabledExtensions.size());
        createInfo.ppEnabledExtensionNames = enabledExtensions.data();
        createInfo.enabledLayerCount = static_cast<uint32_t>(enabledLayers.size());
        createInfo.ppEnabledLayerNames = enabledLayers.data();

        VkInstance instance = VK_NULL_HANDLE;
        VkResult result = vkCreateInstance(&createInfo, nullptr, &_instance);

        if( result != VK_SUCCESS ){
            throw std::runtime_error("could not create vulkan-instance!");   
        } else {
            printf("successfully created vulkan-instance!\n");
        }
    }

    void setupDebug() {
        PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT = 
            reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>
                (vkGetInstanceProcAddr(_instance, "vkCreateDebugReportCallbackEXT"));
        
        PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT =
            reinterpret_cast<PFN_vkDebugReportMessageEXT>
                (vkGetInstanceProcAddr(_instance, "vkDebugReportMessageEXT"));
        
        PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT =
            reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>
                (vkGetInstanceProcAddr(_instance, "vkDestroyDebugReportCallbackEXT"));
    


        VkDebugReportCallbackCreateInfoEXT callbackCreateInfo;
        callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
        callbackCreateInfo.pNext = nullptr;
        callbackCreateInfo.flags = 
            VK_DEBUG_REPORT_ERROR_BIT_EXT |
            VK_DEBUG_REPORT_WARNING_BIT_EXT |
            VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
            VK_DEBUG_REPORT_INFORMATION_BIT_EXT;
        callbackCreateInfo.pfnCallback = &debugCallback;
        callbackCreateInfo.pUserData = nullptr;

        VkDebugReportCallbackEXT callback;
        VkResult result = vkCreateDebugReportCallbackEXT(_instance, &callbackCreateInfo, nullptr, &callback); 
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugReportFlagsEXT       flags,
        VkDebugReportObjectTypeEXT  objectType,
        uint64_t                    object,
        size_t                      location,
        int32_t                     messageCode,
        const char*                 playerPrefix,
        const char*                 pMessage,
        void*                       pUserData)
    {
        std::cerr << pMessage << std::endl;
        return VK_FALSE;
    }
};