#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/system/logging/Logger.h"
#include "src/utils/FierceStrings.h"
#include "src/core/Exceptions.h"
#include "VK_Device.h"

/* SystemIncludes*/
#include "vulkan/vulkan.h"
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class VK_Helper_Device{
public:
	static void getAllPhysicalDevices(VkInstance instance,std::vector<VkPhysicalDevice>* devices) {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0) {
            CHECK_VK(VK_ERROR_INCOMPATIBLE_DRIVER, "No graphics card with vulkan support found.");
        }
        devices->resize(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices->data());
	}

    static void getDeviceData(VkPhysicalDevice device, VkSurfaceKHR surface, VK_Device::DeviceData* data) {
        vkGetPhysicalDeviceProperties(device, &data->deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &data->deviceFeatures);
        vkGetPhysicalDeviceMemoryProperties(device, &data->deviceMemoryProperties);
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        data->queueFamilies.resize(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, data->queueFamilies.data());

        CHECK_VK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &data->surfaceCapabilities), "Failed to get surface capabilities.");
        uint32_t formatCount;
        CHECK_VK(vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr), "Failed to get surface formats.");
        data->surfaceFormats.resize(formatCount);
        CHECK_VK(vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, data->surfaceFormats.data()), "Failed to get surface formats.");
        uint32_t presentModeCount;
        CHECK_VK(vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr), "Failed to get present modes.");
        data->presentModes.resize(presentModeCount);
        CHECK_VK(vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, data->presentModes.data()), "Failed to get present modes.");
    }

    static bool checkGeneralDeviceSupport(VkPhysicalDevice device, VK_Device::DeviceData* data) {
        return true;
    }

    static VkBool32 supportsPresent(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface,int queueIndex) {
        VkBool32 presentSupport = false;
        CHECK_VK(vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueIndex, surface, &presentSupport), "Failed to check presentation support.");
        return presentSupport;
    }

    static bool checkQueueSupport(VkPhysicalDevice device, VkSurfaceKHR surface,VK_Device::DeviceData* data) {
        int i = 0;
        for (VkQueueFamilyProperties queueFamily : data->queueFamilies) {
            if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && supportsPresent(device, surface,i)) {
                data->queueFamilyIndex = i;
                return true;
            }
            i++;
        }

        Loggers::VK->warn("No compatible queue family found.");
        data->isCompatible = false;

        return true;
    }

    static bool checkSwapchainSupport(VkPhysicalDevice device, VK_Device::DeviceData* data) {
        //Check surface format
        for (const auto& availableFormat : data->surfaceFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                data->swapchainFormat = availableFormat;
            }
        }

        //Check present mode
        for (const auto& availablePresentMode : data->presentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                data->swapchainPresentMode = availablePresentMode;
            }
        }

        //Check swapchain extent
        data->swapchainExtent = data->surfaceCapabilities.currentExtent;
        data->swapchainExtent.width = max(data->swapchainExtent.width, data->surfaceCapabilities.minImageExtent.width);
        data->swapchainExtent.width = min(data->swapchainExtent.width, data->surfaceCapabilities.maxImageExtent.width);
        data->swapchainExtent.height = max(data->swapchainExtent.height, data->surfaceCapabilities.minImageExtent.height);
        data->swapchainExtent.height = min(data->swapchainExtent.height, data->surfaceCapabilities.maxImageExtent.height);

        //Check number of images
        data->imageCount = data->surfaceCapabilities.minImageCount + 1;
        if (data->surfaceCapabilities.maxImageCount > 0 && data->imageCount > data->surfaceCapabilities.maxImageCount) {
            data->imageCount = data->surfaceCapabilities.maxImageCount;
        }

        data->swapchainTransform = data->surfaceCapabilities.currentTransform;

        return true;
    }

    static void printDeviceProperties(VK_Device::DeviceData* data) {
        std::string deviceType;
        switch (data->deviceProperties.deviceType) {
        case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_OTHER:
            deviceType = "Other";
            break;
        case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            deviceType = "Integrated GPU";
            break;
        case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            deviceType = "Discrete GPU";
            break;
        case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            deviceType = "Virtual GPU";
            break;
        case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU:
            deviceType = "CPU";
            break;
        }
        Loggers::VK->info("Device: %s (%s)", data->deviceProperties.deviceName, deviceType.c_str());
    }

    static void printDeviceFeatures(VK_Device::DeviceData* data) {
        Loggers::VK->info("Features:");
        Loggers::VK->info("AlpahToOne: %d", data->deviceFeatures.alphaToOne);
        Loggers::VK->info("DepthBiasClamp: %d", data->deviceFeatures.depthBiasClamp);
        Loggers::VK->info("DepthBounds: %d", data->deviceFeatures.depthBounds);
        Loggers::VK->info("DepthClamp: %d", data->deviceFeatures.depthClamp);
        Loggers::VK->info("DrawIndirectFirstInstance: %d", data->deviceFeatures.drawIndirectFirstInstance);
        Loggers::VK->info("DualSrcBlend: %d", data->deviceFeatures.dualSrcBlend);
        Loggers::VK->info("FillModeNonSolid: %d", data->deviceFeatures.fillModeNonSolid);
        Loggers::VK->info("FragmentStoresAndAtomics: %d", data->deviceFeatures.fragmentStoresAndAtomics);
        Loggers::VK->info("FullDrawIndexUint32: %d", data->deviceFeatures.fullDrawIndexUint32);
        Loggers::VK->info("GeometryShader: %d", data->deviceFeatures.geometryShader);
        Loggers::VK->info("ImageCubeArray: %d", data->deviceFeatures.imageCubeArray);
        Loggers::VK->info("IndependentBlend: %d", data->deviceFeatures.independentBlend);
        Loggers::VK->info("InheritedQueries: %d", data->deviceFeatures.inheritedQueries);
        Loggers::VK->info("LargePoints: %d", data->deviceFeatures.largePoints);
        Loggers::VK->info("LogicOp: %d", data->deviceFeatures.logicOp);
        Loggers::VK->info("MultiDrawIndirect: %d", data->deviceFeatures.multiDrawIndirect);
        Loggers::VK->info("MultiViewport: %d", data->deviceFeatures.multiViewport);
        Loggers::VK->info("OcclusionQueryPrecise: %d", data->deviceFeatures.occlusionQueryPrecise);
        Loggers::VK->info("PipelineStatisticsQuery: %d", data->deviceFeatures.pipelineStatisticsQuery);
        Loggers::VK->info("RobustBufferAccess: %d", data->deviceFeatures.robustBufferAccess);
        Loggers::VK->info("SamplerAnisotropy: %d", data->deviceFeatures.samplerAnisotropy);
        Loggers::VK->info("SampleRateShading: %d", data->deviceFeatures.sampleRateShading);
        Loggers::VK->info("ShaderClipDistance: %d", data->deviceFeatures.shaderClipDistance);
        Loggers::VK->info("ShaderCullDistance: %d", data->deviceFeatures.shaderCullDistance);
        Loggers::VK->info("ShaderFloat64: %d", data->deviceFeatures.shaderFloat64);
        Loggers::VK->info("ShaderImageGatherExtended: %d", data->deviceFeatures.shaderImageGatherExtended);
        Loggers::VK->info("ShaderInt16: %d", data->deviceFeatures.shaderInt16);
        Loggers::VK->info("ShaderInt64: %d", data->deviceFeatures.shaderInt64);
        Loggers::VK->info("ShaderResourceMinLod: %d", data->deviceFeatures.shaderResourceMinLod);
        Loggers::VK->info("ShaderResourceResidency: %d", data->deviceFeatures.shaderResourceResidency);
        Loggers::VK->info("ShaderSampledImageArrayDynamicIndexing: %d", data->deviceFeatures.shaderSampledImageArrayDynamicIndexing);
        Loggers::VK->info("ShaderStorageBufferArrayDynamicIndexing: %d", data->deviceFeatures.shaderStorageBufferArrayDynamicIndexing);
        Loggers::VK->info("ShaderStorageImageArrayDynamicIndexing: %d", data->deviceFeatures.shaderStorageImageArrayDynamicIndexing);
        Loggers::VK->info("ShaderStorageImageExtendedFormats: %d", data->deviceFeatures.shaderStorageImageExtendedFormats);
        Loggers::VK->info("ShaderStorageImageMultisample: %d", data->deviceFeatures.shaderStorageImageMultisample);
        Loggers::VK->info("ShaderStorageImageReadWithoutFormat: %d", data->deviceFeatures.shaderStorageImageReadWithoutFormat);
        Loggers::VK->info("ShaderStorageImageWriteWithoutFormat: %d", data->deviceFeatures.shaderStorageImageWriteWithoutFormat);
        Loggers::VK->info("ShaderTessellationAndGeometryPointSize: %d", data->deviceFeatures.shaderTessellationAndGeometryPointSize);
        Loggers::VK->info("ShaderUniformBufferArrayDynamicIndexing: %d", data->deviceFeatures.shaderUniformBufferArrayDynamicIndexing);
        Loggers::VK->info("SparseBinding: %d", data->deviceFeatures.sparseBinding);
        Loggers::VK->info("SparseResidency2Samples: %d", data->deviceFeatures.sparseResidency2Samples);
        Loggers::VK->info("SparseResidency4Samples: %d", data->deviceFeatures.sparseResidency4Samples);
        Loggers::VK->info("SparseResidency8Samples: %d", data->deviceFeatures.sparseResidency8Samples);
        Loggers::VK->info("SparseResidency16Samples: %d", data->deviceFeatures.sparseResidency16Samples);
        Loggers::VK->info("SparseResidencyAliased: %d", data->deviceFeatures.sparseResidencyAliased);
        Loggers::VK->info("SparseResidencyBuffer: %d", data->deviceFeatures.sparseResidencyBuffer);
        Loggers::VK->info("SparseResidencyImage2D: %d", data->deviceFeatures.sparseResidencyImage2D);
        Loggers::VK->info("SparseResidencyImage3D: %d", data->deviceFeatures.sparseResidencyImage3D);
        Loggers::VK->info("TessellationShader: %d", data->deviceFeatures.tessellationShader);
        Loggers::VK->info("TextureCompressionASTC_LDR: %d", data->deviceFeatures.textureCompressionASTC_LDR);
        Loggers::VK->info("TextureCompressionBC: %d", data->deviceFeatures.textureCompressionBC);
        Loggers::VK->info("TextureCompressionETC2: %d", data->deviceFeatures.textureCompressionETC2);
        Loggers::VK->info("VariableMultisampleRate: %d", data->deviceFeatures.variableMultisampleRate);
        Loggers::VK->info("VertexPipelineStoresAndAtomics: %d", data->deviceFeatures.vertexPipelineStoresAndAtomics);
        Loggers::VK->info("WideLines: %d", data->deviceFeatures.wideLines);
    }

    static void printDeviceMemoryProperties(VK_Device::DeviceData* data) {
        Loggers::VK->info("Memory properties:");
        for (int i = 0;i< data->deviceMemoryProperties.memoryHeapCount;i++) {
            Loggers::VK->info("\tHeap %i:",i);
            Loggers::VK->info("\tSize: %llu GB", data->deviceMemoryProperties.memoryHeaps[i].size/100000000);
            std::string flags = "";
            if (data->deviceMemoryProperties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
                flags.append(" DEVICE_LOCAL_BIT");
            }
            if (data->deviceMemoryProperties.memoryHeaps[i].flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT) {
                flags.append(" MULTI_INSTANCE_BIT");
            }
            Loggers::VK->info("\tFlags: %s", flags.c_str());
            Loggers::VK->info("");
        }
        for (int i = 0; i < data->deviceMemoryProperties.memoryTypeCount; i++) {
            Loggers::VK->info("\tType %i:", i);
            Loggers::VK->info("\tHeap %i:", data->deviceMemoryProperties.memoryTypes[i].heapIndex);
            std::string flags = "";
            if (data->deviceMemoryProperties.memoryTypes[i].propertyFlags&VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) {
                flags.append(" DEVICE_LOCAL_BIT");
            }
            if (data->deviceMemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
                flags.append(" HOST_VISIBLE_BIT");
            }
            if (data->deviceMemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
                flags.append(" HOST_COHERENT_BIT");
            }
            if (data->deviceMemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) {
                flags.append(" HOST_CACHED_BIT");
            }
            if (data->deviceMemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT) {
                flags.append(" LAZILY_ALLOCATED_BIT");
            }
            if (data->deviceMemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_PROTECTED_BIT) {
                flags.append(" PROTECTED_BIT");
            }
            if (data->deviceMemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD) {
                flags.append(" VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD");
            }
            if (data->deviceMemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD) {
                flags.append(" VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD");
            }
            Loggers::VK->info("\tFlags %s:", flags.c_str());
            Loggers::VK->info("");
        }
    }

    static void printDeviceData(VK_Device::DeviceData* data) {
        Loggers::VK->info("##### Device Data #####");
        printDeviceProperties(data);
        printDeviceFeatures(data);
        printDeviceMemoryProperties(data);
        Loggers::VK->info("#######################");
    }
};