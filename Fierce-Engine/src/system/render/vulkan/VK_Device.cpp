#include "VK_Device.h"

#include "src/core/Exceptions.h"
#include "src/system/logging/Logger.h"
#include "src/system/render/vulkan/VK_Helper_Device.h"

//#include "src/system/render/vulkan/VK_Renderpass.h"
//#include "src/system/render/vulkan/VK_Framebuffers.h"
//#include "src/system/render/vulkan/VK_Pipeline.h"

VK_Device::VK_Device(VkInstance instance, VkSurfaceKHR surface){
    m_instance = instance;
    m_surface = surface;
    VK_Helper_Extensions_ValidationLayers::getExtensions(m_physicalDevice, &supportedExtensions);
    VK_Helper_Extensions_ValidationLayers::getValidationLayers(m_physicalDevice, &supportedValidationLayers);
}

VK_Device::~VK_Device() {
    //vkDestroyDevice(device, nullptr);
}

void VK_Device::pickPhysicalDevice() {
    std::vector<VkPhysicalDevice> supportedDevices;
    VK_Helper_Device::getAllPhysicalDevices(m_instance,&supportedDevices);

    for (VkPhysicalDevice device:supportedDevices) {
        DeviceData data = {};
        VK_Helper_Device::getDeviceData(device,m_surface,&data);
        VK_Helper_Device::printDeviceData(&data);
        checkDeviceCompatibility(device,&data);
    }
}

void VK_Device::checkDeviceCompatibility(VkPhysicalDevice device, DeviceData* deviceData) {
    checkExtensionSupport();
    checkValidationLayerSupport();
    VK_Helper_Device::checkGeneralDeviceSupport(device, deviceData);
    VK_Helper_Device::checkQueueSupport(device,m_surface,deviceData);
    //Check if extension is turned on
    VK_Helper_Device::checkSwapchainSupport(device, deviceData);
}

void VK_Device::create() {
    pickPhysicalDevice();
    //createLogicalDevice();
    //vkGetDeviceQueue(device, queueFamilyIndex, 0, &graphicsQueue);
}

void VK_Device::createLogicalDevice(){
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
    queueCreateInfo.queueCount = 1;
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.pEnabledFeatures = &deviceFeatures;
    if (enabledExtensions.empty()) {
        createInfo.enabledExtensionCount = 0;
        createInfo.ppEnabledExtensionNames = nullptr;
    }
    else {
        createInfo.enabledExtensionCount = static_cast<uint32_t>(enabledExtensions.size());
        createInfo.ppEnabledExtensionNames = enabledExtensions.data();
    }
    if (enabledValidationLayers.empty()) {
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
    }
    else {
        createInfo.enabledLayerCount = static_cast<uint32_t>(enabledValidationLayers.size());
        createInfo.ppEnabledLayerNames = enabledValidationLayers.data();
    }

    CHECK_VK(vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &device), "Failed to create logical device.");
}