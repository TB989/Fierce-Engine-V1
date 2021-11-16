#include "VK_Device.h"

#include "src/core/Exceptions.h"
#include "src/system/logging/Logger.h"
#include "src/system/render/vulkan/VK_Helper_Device.h"
#include "VK_CommandBuffer.h"

VK_Device::VK_Device(VkInstance instance, VkSurfaceKHR surface){
    m_instance = instance;
    m_surface = surface;
}

VK_Device::~VK_Device() {
    vkDestroyCommandPool(device, commandPool, nullptr);
    vkDestroyDevice(device, nullptr);
}

VK_CommandBuffer* VK_Device::getCommandBuffer(){
    return new VK_CommandBuffer(device,commandPool);
}

void VK_Device::pickPhysicalDevice() {
    std::vector<VkPhysicalDevice> supportedDevices;
    VK_Helper_Device::getAllPhysicalDevices(m_instance,&supportedDevices);

    for (VkPhysicalDevice device:supportedDevices) {
        deviceData = {};
        surfaceData = {};
        extensionLayerData = {};

        VK_Helper_Extensions_ValidationLayers::getExtensions(device, &extensionLayerData.supportedExtensions);
        VK_Helper_Extensions_ValidationLayers::getValidationLayers(device, &extensionLayerData.supportedValidationLayers);
        VK_Helper_Device::getSurfaceData(device, m_surface, &surfaceData);
        VK_Helper_Device::getDeviceData(device,m_surface,&deviceData);

        if (checkDeviceCompatibility(&extensionLayerData, &deviceData, &surfaceData)) {
            m_physicalDevice = device;
            return;
        }
    }

    CHECK_VK(VK_ERROR_INCOMPATIBLE_DRIVER,"No compatible device found.");
}

bool VK_Device::checkDeviceCompatibility(ExtensionValidationLayerData* data, DeviceData* deviceData, SurfaceData* surfaceData) {
    for (auto mcheck : checks) {
        if (!mcheck->check(data, deviceData, surfaceData)) {
            return false;
        }
    }

    return true;
}

void VK_Device::create() {
    pickPhysicalDevice();
    createLogicalDevice();
    vkGetDeviceQueue(device, deviceData.graphicsQueueIndex, 0, &graphicsQueue);
    transferQueue = graphicsQueue;
    createCommandPool();
}

void VK_Device::createLogicalDevice(){

    VK_Helper_Extensions_ValidationLayers::printExtensions(false,"", &extensionLayerData.enabledExtensions);

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = deviceData.graphicsQueueIndex;
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

    CHECK_VK(vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &device), "Failed to create logical device.");
}

void VK_Device::createCommandPool() {
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.pNext = nullptr;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = deviceData.graphicsQueueIndex;

    CHECK_VK(vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool), "Failed to create command pool.");
}