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

    static void getSampleCounts(VkSampleCountFlags flags,std::string *samples) {
        samples->clear();
        if (flags & VK_SAMPLE_COUNT_1_BIT) {
            samples->assign("VK_SAMPLE_COUNT_1_BIT");
        }
        if (flags & VK_SAMPLE_COUNT_2_BIT) {
            samples->assign("VK_SAMPLE_COUNT_2_BIT");
        }
        if (flags & VK_SAMPLE_COUNT_4_BIT) {
            samples->assign("VK_SAMPLE_COUNT_4_BIT");
        }
        if (flags & VK_SAMPLE_COUNT_8_BIT) {
            samples->assign("VK_SAMPLE_COUNT_8_BIT");
        }
        if (flags & VK_SAMPLE_COUNT_16_BIT) {
            samples->assign("VK_SAMPLE_COUNT_16_BIT");
        }
        if (flags & VK_SAMPLE_COUNT_32_BIT) {
            samples->assign("VK_SAMPLE_COUNT_32_BIT");
        }
        if (flags & VK_SAMPLE_COUNT_64_BIT) {
            samples->assign("VK_SAMPLE_COUNT_64_BIT");
        }
    }

    static void printDeviceLimits(VK_Device::DeviceData* data) {
        std::string flags = "";
        Loggers::VK->info("Limits:");
        Loggers::VK->info("\tBufferImageGranularity: %llu", data->deviceProperties.limits.bufferImageGranularity);
        Loggers::VK->info("\tDiscreteQueuePriorities: %lu", data->deviceProperties.limits.discreteQueuePriorities);
        getSampleCounts(data->deviceProperties.limits.framebufferColorSampleCounts,&flags);
        Loggers::VK->info("\tFramebufferColorSampleCounts: %s", flags.c_str());
        getSampleCounts(data->deviceProperties.limits.framebufferDepthSampleCounts, &flags);
        Loggers::VK->info("\tFramebufferDepthSampleCounts: %s", flags.c_str());
        getSampleCounts(data->deviceProperties.limits.framebufferNoAttachmentsSampleCounts, &flags);
        Loggers::VK->info("\tFramebufferNoAttachmentsSampleCounts: %s", flags.c_str());
        getSampleCounts(data->deviceProperties.limits.framebufferStencilSampleCounts, &flags);
        Loggers::VK->info("\tFramebufferStencilSampleCounts: %s", flags.c_str());
        Loggers::VK->info("\tLineWidthGranularity: %1.3f", data->deviceProperties.limits.lineWidthGranularity);
        Loggers::VK->info("\tLineWidthRange: %1.3f", data->deviceProperties.limits.lineWidthRange);
        Loggers::VK->info("\tMaxBoundDescriptorSets: %lu", data->deviceProperties.limits.maxBoundDescriptorSets);
        Loggers::VK->info("\tMaxClipDistances: %lu", data->deviceProperties.limits.maxClipDistances);
        Loggers::VK->info("\tMaxColorAttachments: %lu", data->deviceProperties.limits.maxColorAttachments);
        Loggers::VK->info("\tMaxCombinedClipAndCullDistances: %lu", data->deviceProperties.limits.maxCombinedClipAndCullDistances);
        Loggers::VK->info("\tMaxComputeSharedMemorySize: %lu", data->deviceProperties.limits.maxComputeSharedMemorySize);
        Loggers::VK->info("\tMaxComputeWorkGroupCount: %lu", data->deviceProperties.limits.maxComputeWorkGroupCount);
        Loggers::VK->info("\tMaxComputeWorkGroupInvocations: %lu", data->deviceProperties.limits.maxComputeWorkGroupInvocations);
        Loggers::VK->info("\tMaxComputeWorkGroupSize: %lu", data->deviceProperties.limits.maxComputeWorkGroupSize);
        Loggers::VK->info("\tMaxCullDistances: %lu", data->deviceProperties.limits.maxCullDistances);
        Loggers::VK->info("\tMaxDescriptorSetInputAttachments: %lu", data->deviceProperties.limits.maxDescriptorSetInputAttachments);
        Loggers::VK->info("\tMaxDescriptorSetSampledImages: %lu", data->deviceProperties.limits.maxDescriptorSetSampledImages);
        Loggers::VK->info("\tMaxDescriptorSetSamplers: %lu", data->deviceProperties.limits.maxDescriptorSetSamplers);
        Loggers::VK->info("\tMaxDescriptorSetStorageBuffers: %lu", data->deviceProperties.limits.maxDescriptorSetStorageBuffers);
        Loggers::VK->info("\tMaxDescriptorSetStorageBuffersDynamic: %lu", data->deviceProperties.limits.maxDescriptorSetStorageBuffersDynamic);
        Loggers::VK->info("\tMaxDescriptorSetStorageImages: %lu", data->deviceProperties.limits.maxDescriptorSetStorageImages);
        Loggers::VK->info("\tMaxDescriptorSetUniformBuffers: %lu", data->deviceProperties.limits.maxDescriptorSetUniformBuffers);
        Loggers::VK->info("\tMaxDescriptorSetUniformBuffersDynamic: %lu", data->deviceProperties.limits.maxDescriptorSetUniformBuffersDynamic);
        Loggers::VK->info("\tMaxDrawIndexedIndexValue: %lu", data->deviceProperties.limits.maxDrawIndexedIndexValue);
        Loggers::VK->info("\tMaxDrawIndirectCount: %lu", data->deviceProperties.limits.maxDrawIndirectCount);
        Loggers::VK->info("\tMaxFragmentCombinedOutputResources: %lu", data->deviceProperties.limits.maxFragmentCombinedOutputResources);
        Loggers::VK->info("\tMaxFragmentDualSrcAttachments: %lu", data->deviceProperties.limits.maxFragmentDualSrcAttachments);
        Loggers::VK->info("\tMaxFragmentInputComponents: %lu", data->deviceProperties.limits.maxFragmentInputComponents);
        Loggers::VK->info("\tMaxFragmentOutputAttachments: %lu", data->deviceProperties.limits.maxFragmentOutputAttachments);
        Loggers::VK->info("\tMaxFramebufferHeight: %lu", data->deviceProperties.limits.maxFramebufferHeight);
        Loggers::VK->info("\tMaxFramebufferLayers: %lu", data->deviceProperties.limits.maxFramebufferLayers);
        Loggers::VK->info("\tMaxFramebufferWidth: %lu", data->deviceProperties.limits.maxFramebufferWidth);
        Loggers::VK->info("\tMaxGeometryInputComponents: %lu", data->deviceProperties.limits.maxGeometryInputComponents);
        Loggers::VK->info("\tMaxGeometryOutputComponents: %lu", data->deviceProperties.limits.maxGeometryOutputComponents);
        Loggers::VK->info("\tMaxGeometryOutputVertices: %lu", data->deviceProperties.limits.maxGeometryOutputVertices);
        Loggers::VK->info("\tMaxGeometryShaderInvocations: %lu", data->deviceProperties.limits.maxGeometryShaderInvocations);
        Loggers::VK->info("\tMaxGeometryTotalOutputComponents: %lu", data->deviceProperties.limits.maxGeometryTotalOutputComponents);
        Loggers::VK->info("\tMaxImageArrayLayers: %lu", data->deviceProperties.limits.maxImageArrayLayers);
        Loggers::VK->info("\tMaxImageDimension1D: %lu", data->deviceProperties.limits.maxImageDimension1D);
        Loggers::VK->info("\tMaxImageDimension2D: %lu", data->deviceProperties.limits.maxImageDimension2D);
        Loggers::VK->info("\tMaxImageDimension3D: %lu", data->deviceProperties.limits.maxImageDimension3D);
        Loggers::VK->info("\tMaxImageDimensionCube: %lu", data->deviceProperties.limits.maxImageDimensionCube);
    }

    static void printDeviceFeatures(VK_Device::DeviceData* data) {
        Loggers::VK->info("Features:");
        Loggers::VK->info("\tAlpahToOne: %s", data->deviceFeatures.alphaToOne?"true":"false");
        Loggers::VK->info("\tDepthBiasClamp: %s", data->deviceFeatures.depthBiasClamp ? "true" : "false");
        Loggers::VK->info("\tDepthBounds: %s", data->deviceFeatures.depthBounds ? "true" : "false");
        Loggers::VK->info("\tDepthClamp: %s", data->deviceFeatures.depthClamp ? "true" : "false");
        Loggers::VK->info("\tDrawIndirectFirstInstance: %s", data->deviceFeatures.drawIndirectFirstInstance ? "true" : "false");
        Loggers::VK->info("\tDualSrcBlend: %s", data->deviceFeatures.dualSrcBlend ? "true" : "false");
        Loggers::VK->info("\tFillModeNonSolid: %s", data->deviceFeatures.fillModeNonSolid ? "true" : "false");
        Loggers::VK->info("\tFragmentStoresAndAtomics: %s", data->deviceFeatures.fragmentStoresAndAtomics ? "true" : "false");
        Loggers::VK->info("\tFullDrawIndexUint32: %s", data->deviceFeatures.fullDrawIndexUint32 ? "true" : "false");
        Loggers::VK->info("\tGeometryShader: %s", data->deviceFeatures.geometryShader ? "true" : "false");
        Loggers::VK->info("\tImageCubeArray: %s", data->deviceFeatures.imageCubeArray ? "true" : "false");
        Loggers::VK->info("\tIndependentBlend: %s", data->deviceFeatures.independentBlend ? "true" : "false");
        Loggers::VK->info("\tInheritedQueries: %s", data->deviceFeatures.inheritedQueries ? "true" : "false");
        Loggers::VK->info("\tLargePoints: %s", data->deviceFeatures.largePoints ? "true" : "false");
        Loggers::VK->info("\tLogicOp: %s", data->deviceFeatures.logicOp ? "true" : "false");
        Loggers::VK->info("\tMultiDrawIndirect: %s", data->deviceFeatures.multiDrawIndirect ? "true" : "false");
        Loggers::VK->info("\tMultiViewport: %s", data->deviceFeatures.multiViewport ? "true" : "false");
        Loggers::VK->info("\tOcclusionQueryPrecise: %s", data->deviceFeatures.occlusionQueryPrecise ? "true" : "false");
        Loggers::VK->info("\tPipelineStatisticsQuery: %s", data->deviceFeatures.pipelineStatisticsQuery ? "true" : "false");
        Loggers::VK->info("\tRobustBufferAccess: %s", data->deviceFeatures.robustBufferAccess ? "true" : "false");
        Loggers::VK->info("\tSamplerAnisotropy: %s", data->deviceFeatures.samplerAnisotropy ? "true" : "false");
        Loggers::VK->info("\tSampleRateShading: %s", data->deviceFeatures.sampleRateShading ? "true" : "false");
        Loggers::VK->info("\tShaderClipDistance: %s", data->deviceFeatures.shaderClipDistance ? "true" : "false");
        Loggers::VK->info("\tShaderCullDistance: %s", data->deviceFeatures.shaderCullDistance ? "true" : "false");
        Loggers::VK->info("\tShaderFloat64: %s", data->deviceFeatures.shaderFloat64 ? "true" : "false");
        Loggers::VK->info("\tShaderImageGatherExtended: %s", data->deviceFeatures.shaderImageGatherExtended ? "true" : "false");
        Loggers::VK->info("\tShaderInt16: %s", data->deviceFeatures.shaderInt16 ? "true" : "false");
        Loggers::VK->info("\tShaderInt64: %s", data->deviceFeatures.shaderInt64 ? "true" : "false");
        Loggers::VK->info("\tShaderResourceMinLod: %s", data->deviceFeatures.shaderResourceMinLod ? "true" : "false");
        Loggers::VK->info("\tShaderResourceResidency: %s", data->deviceFeatures.shaderResourceResidency ? "true" : "false");
        Loggers::VK->info("\tShaderSampledImageArrayDynamicIndexing: %s", data->deviceFeatures.shaderSampledImageArrayDynamicIndexing ? "true" : "false");
        Loggers::VK->info("\tShaderStorageBufferArrayDynamicIndexing: %s", data->deviceFeatures.shaderStorageBufferArrayDynamicIndexing ? "true" : "false");
        Loggers::VK->info("\tShaderStorageImageArrayDynamicIndexing: %s", data->deviceFeatures.shaderStorageImageArrayDynamicIndexing ? "true" : "false");
        Loggers::VK->info("\tShaderStorageImageExtendedFormats: %s", data->deviceFeatures.shaderStorageImageExtendedFormats ? "true" : "false");
        Loggers::VK->info("\tShaderStorageImageMultisample: %s", data->deviceFeatures.shaderStorageImageMultisample ? "true" : "false");
        Loggers::VK->info("\tShaderStorageImageReadWithoutFormat: %s", data->deviceFeatures.shaderStorageImageReadWithoutFormat ? "true" : "false");
        Loggers::VK->info("\tShaderStorageImageWriteWithoutFormat: %s", data->deviceFeatures.shaderStorageImageWriteWithoutFormat ? "true" : "false");
        Loggers::VK->info("\tShaderTessellationAndGeometryPointSize: %s", data->deviceFeatures.shaderTessellationAndGeometryPointSize ? "true" : "false");
        Loggers::VK->info("\tShaderUniformBufferArrayDynamicIndexing: %s", data->deviceFeatures.shaderUniformBufferArrayDynamicIndexing ? "true" : "false");
        Loggers::VK->info("\tSparseBinding: %s", data->deviceFeatures.sparseBinding ? "true" : "false");
        Loggers::VK->info("\tSparseResidency2Samples: %s", data->deviceFeatures.sparseResidency2Samples ? "true" : "false");
        Loggers::VK->info("\tSparseResidency4Samples: %s", data->deviceFeatures.sparseResidency4Samples ? "true" : "false");
        Loggers::VK->info("\tSparseResidency8Samples: %s", data->deviceFeatures.sparseResidency8Samples ? "true" : "false");
        Loggers::VK->info("\tSparseResidency16Samples: %s", data->deviceFeatures.sparseResidency16Samples ? "true" : "false");
        Loggers::VK->info("\tSparseResidencyAliased: %s", data->deviceFeatures.sparseResidencyAliased ? "true" : "false");
        Loggers::VK->info("\tSparseResidencyBuffer: %s", data->deviceFeatures.sparseResidencyBuffer ? "true" : "false");
        Loggers::VK->info("\tSparseResidencyImage2D: %s", data->deviceFeatures.sparseResidencyImage2D ? "true" : "false");
        Loggers::VK->info("\tSparseResidencyImage3D: %s", data->deviceFeatures.sparseResidencyImage3D ? "true" : "false");
        Loggers::VK->info("\tTessellationShader: %s", data->deviceFeatures.tessellationShader ? "true" : "false");
        Loggers::VK->info("\tTextureCompressionASTC_LDR: %s", data->deviceFeatures.textureCompressionASTC_LDR ? "true" : "false");
        Loggers::VK->info("\tTextureCompressionBC: %s", data->deviceFeatures.textureCompressionBC ? "true" : "false");
        Loggers::VK->info("\tTextureCompressionETC2: %s", data->deviceFeatures.textureCompressionETC2 ? "true" : "false");
        Loggers::VK->info("\tVariableMultisampleRate: %s", data->deviceFeatures.variableMultisampleRate ? "true" : "false");
        Loggers::VK->info("\tVertexPipelineStoresAndAtomics: %s", data->deviceFeatures.vertexPipelineStoresAndAtomics ? "true" : "false");
        Loggers::VK->info("\tWideLines: %s", data->deviceFeatures.wideLines ? "true" : "false");
    }

    static void printDeviceMemoryProperties(VK_Device::DeviceData* data) {
        Loggers::VK->info("Memory properties:");
        for (int i = 0;i< data->deviceMemoryProperties.memoryHeapCount;i++) {
            Loggers::VK->info("\tHeap %i:",i);
            Loggers::VK->info("\tMemory size: %llu GB", data->deviceMemoryProperties.memoryHeaps[i].size/100000000);
            std::string flags = "";
            if (data->deviceMemoryProperties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
                flags.append(" DEVICE_LOCAL_BIT");
            }
            if (data->deviceMemoryProperties.memoryHeaps[i].flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT) {
                flags.append(" MULTI_INSTANCE_BIT");
            }
            Loggers::VK->info("\tHeap flags: %s", flags.c_str());

            for (int j = 0; j < data->deviceMemoryProperties.memoryTypeCount; j++) {
                if (data->deviceMemoryProperties.memoryTypes[j].heapIndex==i) {
                    Loggers::VK->info("\tMemory type %i:", j);
                    std::string flags = "";
                    if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) {
                        flags.append(" DEVICE_LOCAL_BIT");
                    }
                    if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
                        flags.append(" HOST_VISIBLE_BIT");
                    }
                    if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
                        flags.append(" HOST_COHERENT_BIT");
                    }
                    if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) {
                        flags.append(" HOST_CACHED_BIT");
                    }
                    if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT) {
                        flags.append(" LAZILY_ALLOCATED_BIT");
                    }
                    if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_PROTECTED_BIT) {
                        flags.append(" PROTECTED_BIT");
                    }
                    if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD) {
                        flags.append(" VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD");
                    }
                    if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD) {
                        flags.append(" VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD");
                    }
                    Loggers::VK->info("\tMemory flags %s", flags.c_str());
                }
            }
            Loggers::VK->info("");
        }
    }

    static void printDeviceData(VK_Device::DeviceData* data) {
        Loggers::VK->info("##### Device Data #####");
        printDeviceProperties(data);
        printDeviceLimits(data);
        //printDeviceFeatures(data);
        //printDeviceMemoryProperties(data);
        Loggers::VK->info("#######################");
    }
};