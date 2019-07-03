#include <stdio.h>
#include <stdexcept>
#include <cstring>

#include "Instance.hpp"

/**
 * proxy-function(s)
 */
VkResult createDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if(func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}



/**
 * constructors, destructors
 */

Instance::Instance() {}
Instance::~Instance() {}





/**
 * void-methods
 */

void Instance::initVulkan() {
    createInstance();
    setupDebugMessenger();
}

void Instance::createInstance() {
    if(_enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    std::vector<const char*> requiredExtensions = getRequiredExtensions();

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Sapere";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_1;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();
    createInfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
    createInfo.ppEnabledLayerNames = _validationLayers.data();

    if(vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    // uint32_t extensionCount = 0;
    // vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    // std::vector<VkExtensionProperties> extensions(extensionCount);
    // vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    // printf("available extensions:\n");
    // for(const VkExtensionProperties extension : extensions) {
    //     printf("\t %s\n", extension.extensionName);
    // }
}

void Instance::setupDebugMessenger() {
    if(!_enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = 
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = 
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = nullptr; 

    if(createDebugUtilsMessengerEXT(_instance, &createInfo, nullptr, &_debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to setup debug-messenger!");
    }
}

void Instance::cleanup() {
    vkDestroyInstance(_instance, nullptr);
}







/**
 * Boolean-methods
 */

bool Instance::checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    for(const VkLayerProperties layerProperties : availableLayers) {
        printf("layer: %s available!\n", layerProperties.layerName);
    }

    for(const char* layerName : _validationLayers) {
        bool layerFound = false;

        for(const VkLayerProperties layerProperties : availableLayers) {
            if(strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        
        if(!layerFound) { return false; }
    }

    return true;
}





/**
 * aggregate-methods
 */

std::vector<const char*> Instance::getRequiredExtensions() {
    std::vector<const char*> extensions;

    if(_enableValidationLayers) { 
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME); 
        extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    }
    extensions.push_back("VK_KHR_surface");

    return extensions;
}



/**
 * static methods
 */

VKAPI_ATTR VkBool32 VKAPI_CALL Instance::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
) {
    fprintf(stderr, "validation-layer: %s\n", pCallbackData->pMessage);
    return VK_FALSE;
}