#include "VK_Instance.h"

#include "src/core/EngineSettings.h"
#include "src/core/Exceptions.h"
#include "src/system/logging/Logger.h"

#include <algorithm>

VK_Instance::VK_Instance(EngineSettings* settings) {
    API_VERSION= VK_MAKE_VERSION(settings->apiVersionMajor, settings->apiVersionMinor, 0);
}

VK_Instance::~VK_Instance() {
    if (isDebugSupported) {
        vkDestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }
    vkDestroyInstance(instance, nullptr);
}

void VK_Instance::create(){
    extensionLayerData = {};
    VK_Helper_Extensions_ValidationLayers::getExtensions(nullptr, &extensionLayerData.supportedExtensions);
    VK_Helper_Extensions_ValidationLayers::getValidationLayers(nullptr, &extensionLayerData.supportedValidationLayers);

    if (!checkInstanceCompatibility(&extensionLayerData, nullptr, nullptr)) {
        CHECK_VK(VK_ERROR_INCOMPATIBLE_DRIVER,"Instance is incompatible.");
    }

    isDebugSupported = VK_Helper_Extensions_ValidationLayers::isExtensionSupported(VK_EXT_DEBUG_UTILS_EXTENSION_NAME,&extensionLayerData.enabledExtensions);

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = APP_NAME.c_str();
    appInfo.applicationVersion = APP_VERSION;
    appInfo.pEngineName = ENGINE_NAME.c_str();
    appInfo.engineVersion = ENGINE_VERSION;
    appInfo.apiVersion = API_VERSION;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.pApplicationInfo = &appInfo;
    if (extensionLayerData.enabledExtensions.empty()) {
        createInfo.enabledExtensionCount = 0;
        createInfo.ppEnabledExtensionNames = nullptr;
    }
    else {
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionLayerData.enabledExtensions.size());
        createInfo.ppEnabledExtensionNames = extensionLayerData.enabledExtensions.data();
    }
    if (extensionLayerData.enabledValidationLayers.empty()) {
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
    }
    else {
        createInfo.enabledLayerCount = static_cast<uint32_t>(extensionLayerData.enabledValidationLayers.size());
        createInfo.ppEnabledLayerNames = extensionLayerData.enabledValidationLayers.data();
    }

    if (isDebugSupported) {
        Loggers::VK->info("Debug messenger is active.");

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugCreateInfo.pNext = nullptr;
        debugCreateInfo.flags = 0;
        debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugCreateInfo.pfnUserCallback = debugCallback;
        debugCreateInfo.pUserData = nullptr;

        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        CHECK_VK(vkCreateInstance(&createInfo, nullptr, &instance), "Failed to create instance.");

        vkCreateDebugUtilsMessengerEXT = loadCreateFunctionPointer(instance);
        vkDestroyDebugUtilsMessengerEXT = loadDestroyFunctionPointer(instance);

        CHECK_VK(vkCreateDebugUtilsMessengerEXT(instance, &debugCreateInfo, nullptr, &debugMessenger), "Failed to create debug messenger.");
    }
    else {
        Loggers::VK->info("Debug messenger is not active.");
        CHECK_VK(vkCreateInstance(&createInfo, nullptr, &instance), "Failed to create instance.");
    }
}

bool VK_Instance::checkInstanceCompatibility(ExtensionValidationLayerData* data, DeviceData* deviceData, SurfaceData* surfaceData){
    for (auto mcheck : checks) {
        if (!mcheck->check(data, deviceData, surfaceData)) {
            return false;
        }
    }

    return true;
}

PFN_vkCreateDebugUtilsMessengerEXT VK_Instance::loadCreateFunctionPointer(VkInstance instance) {
    PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

    if (func == nullptr) {
        CHECK_VK(VK_ERROR_EXTENSION_NOT_PRESENT, "Failed to load function pointer for vkCreateDebugUtilsMessengerEXT.");
        return nullptr;
    }
    return func;
}

PFN_vkDestroyDebugUtilsMessengerEXT VK_Instance::loadDestroyFunctionPointer(VkInstance instance) {
    PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

    if (func == nullptr) {
        CHECK_VK(VK_ERROR_EXTENSION_NOT_PRESENT, "Failed to load function pointer for vkDestroyDebugUtilsMessengerEXT.");
        return nullptr;
    }
    return func;
}

VKAPI_ATTR VkBool32 VKAPI_CALL VK_Instance::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    Loggers::VK->error("%s", pCallbackData->pMessage);
    return VK_FALSE;
}