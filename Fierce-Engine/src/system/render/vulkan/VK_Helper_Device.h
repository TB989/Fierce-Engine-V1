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

    static void getDeviceData(VkPhysicalDevice device, VkSurfaceKHR surface, DeviceData* data) {
        vkGetPhysicalDeviceProperties(device, &data->deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &data->deviceFeatures);
        vkGetPhysicalDeviceMemoryProperties(device, &data->deviceMemoryProperties);
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        data->queueFamilies.resize(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, data->queueFamilies.data());

        data->presentSupport.clear();
        data->presentSupport.resize(queueFamilyCount);
        for (int i = 0;i< queueFamilyCount;i++) {
            VkBool32 supported;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &supported);

            if (supported) {
                data->presentSupport[i] = true;
            }
        }
    }

    static void getSurfaceData(VkPhysicalDevice device, VkSurfaceKHR surface, SurfaceData* data) {
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

    static void printDeviceProperties(DeviceData* data) {
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

    static void printDeviceLimits(DeviceData* data) {
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
        Loggers::VK->info("\tMaxInterpolationOffset: %1.3f", data->deviceProperties.limits.maxInterpolationOffset);
        Loggers::VK->info("\tMaxMemoryAllocationCount: %lu", data->deviceProperties.limits.maxMemoryAllocationCount);
        Loggers::VK->info("\tMaxPerStageDescriptorInputAttachments: %lu", data->deviceProperties.limits.maxPerStageDescriptorInputAttachments);
        Loggers::VK->info("\tMaxPerStageDescriptorSampledImages: %lu", data->deviceProperties.limits.maxPerStageDescriptorSampledImages);
        Loggers::VK->info("\tMaxPerStageDescriptorSamplers: %lu", data->deviceProperties.limits.maxPerStageDescriptorSamplers);
        Loggers::VK->info("\tMaxPerStageDescriptorStorageBuffers: %lu", data->deviceProperties.limits.maxPerStageDescriptorStorageBuffers);
        Loggers::VK->info("\tMaxPerStageDescriptorStorageImages: %lu", data->deviceProperties.limits.maxPerStageDescriptorStorageImages);
        Loggers::VK->info("\tMaxPerStageDescriptorUniformBuffers: %lu", data->deviceProperties.limits.maxPerStageDescriptorUniformBuffers);
        Loggers::VK->info("\tMaxPerStageResources: %lu", data->deviceProperties.limits.maxPerStageResources);
        Loggers::VK->info("\tMaxPushConstantsSize: %lu", data->deviceProperties.limits.maxPushConstantsSize);
        Loggers::VK->info("\tMaxSampleMaskWords: %lu", data->deviceProperties.limits.maxSampleMaskWords);
        Loggers::VK->info("\tMaxSamplerAllocationCount: %lu", data->deviceProperties.limits.maxSamplerAllocationCount);
        Loggers::VK->info("\tMaxSamplerAnisotropy: %1.3f", data->deviceProperties.limits.maxSamplerAnisotropy);
        Loggers::VK->info("\tMaxSamplerLodBias: %1.3f", data->deviceProperties.limits.maxSamplerLodBias);
        Loggers::VK->info("\tMaxStorageBufferRange: %lu", data->deviceProperties.limits.maxStorageBufferRange);
        Loggers::VK->info("\tMaxTessellationControlPerPatchOutputComponents: %lu", data->deviceProperties.limits.maxTessellationControlPerPatchOutputComponents);
        Loggers::VK->info("\tMaxTessellationControlPerVertexInputComponents: %lu", data->deviceProperties.limits.maxTessellationControlPerVertexInputComponents);
        Loggers::VK->info("\tMaxTessellationControlPerVertexOutputComponents: %lu", data->deviceProperties.limits.maxTessellationControlPerVertexOutputComponents);
        Loggers::VK->info("\tMaxTessellationControlTotalOutputComponents: %lu", data->deviceProperties.limits.maxTessellationControlTotalOutputComponents);
        Loggers::VK->info("\tMaxTessellationEvaluationInputComponents: %lu", data->deviceProperties.limits.maxTessellationEvaluationInputComponents);
        Loggers::VK->info("\tMaxTessellationEvaluationOutputComponents: %lu", data->deviceProperties.limits.maxTessellationEvaluationOutputComponents);
        Loggers::VK->info("\tMaxTessellationGenerationLevel: %lu", data->deviceProperties.limits.maxTessellationGenerationLevel);
        Loggers::VK->info("\tMaxTessellationPatchSize: %lu", data->deviceProperties.limits.maxTessellationPatchSize);
        Loggers::VK->info("\tMaxTexelBufferElements: %lu", data->deviceProperties.limits.maxTexelBufferElements);
        Loggers::VK->info("\tMaxTexelGatherOffset: %lu", data->deviceProperties.limits.maxTexelGatherOffset);
        Loggers::VK->info("\tMaxTexelOffset: %lu", data->deviceProperties.limits.maxTexelOffset);
        Loggers::VK->info("\tMaxUniformBufferRange: %lu", data->deviceProperties.limits.maxUniformBufferRange);
        Loggers::VK->info("\tMaxVertexInputAttributeOffset: %lu", data->deviceProperties.limits.maxVertexInputAttributeOffset);
        Loggers::VK->info("\tMaxVertexInputAttributes: %lu", data->deviceProperties.limits.maxVertexInputAttributes);
        Loggers::VK->info("\tMaxVertexInputBindings: %lu", data->deviceProperties.limits.maxVertexInputBindings);
        Loggers::VK->info("\tMaxVertexInputBindingStride: %lu", data->deviceProperties.limits.maxVertexInputBindingStride);
        Loggers::VK->info("\tMaxVertexOutputComponents: %lu", data->deviceProperties.limits.maxVertexOutputComponents);
        Loggers::VK->info("\tMaxViewportDimensions: %lu", data->deviceProperties.limits.maxViewportDimensions);
        Loggers::VK->info("\tMaxViewports: %lu", data->deviceProperties.limits.maxViewports);
        Loggers::VK->info("\tMinInterpolationOffset: %1.3f", data->deviceProperties.limits.minInterpolationOffset);
        Loggers::VK->info("\tMinMemoryMapAlignment: %lu", data->deviceProperties.limits.minMemoryMapAlignment);
        Loggers::VK->info("\tMinStorageBufferOffsetAlignment: %lu", data->deviceProperties.limits.minStorageBufferOffsetAlignment);
        Loggers::VK->info("\tMipmapPrecisionBits: %lu", data->deviceProperties.limits.mipmapPrecisionBits);
        Loggers::VK->info("\tNonCoherentAtomSize: %lu", data->deviceProperties.limits.nonCoherentAtomSize);
        Loggers::VK->info("\tOptimalBufferCopyOffsetAlignment: %lu", data->deviceProperties.limits.optimalBufferCopyOffsetAlignment);
        Loggers::VK->info("\tOptimalBufferCopyRowPitchAlignment: %lu", data->deviceProperties.limits.optimalBufferCopyRowPitchAlignment);
        Loggers::VK->info("\tPointSizeGranularity: %1.3f", data->deviceProperties.limits.pointSizeGranularity);
        Loggers::VK->info("\tPointSizeRange: %1.3f", data->deviceProperties.limits.pointSizeRange);
        getSampleCounts(data->deviceProperties.limits.sampledImageColorSampleCounts, &flags);
        Loggers::VK->info("\tSampledImageColorSampleCounts: %s", flags.c_str());
        getSampleCounts(data->deviceProperties.limits.sampledImageDepthSampleCounts, &flags);
        Loggers::VK->info("\tSampledImageDepthSampleCounts: %s", flags.c_str());
        getSampleCounts(data->deviceProperties.limits.sampledImageIntegerSampleCounts, &flags);
        Loggers::VK->info("\tSampledImageIntegerSampleCounts: %s", flags.c_str());
        getSampleCounts(data->deviceProperties.limits.sampledImageStencilSampleCounts, &flags);
        Loggers::VK->info("\tSampledImageStencilSampleCounts: %s", flags.c_str());
        Loggers::VK->info("\tSparseAddressSpaceSize: %lu", data->deviceProperties.limits.sparseAddressSpaceSize);
        Loggers::VK->info("\tStandardSampleLocations: %s", data->deviceProperties.limits.standardSampleLocations ? "true" : "false");
        getSampleCounts(data->deviceProperties.limits.storageImageSampleCounts, &flags);
        Loggers::VK->info("\tStorageImageSampleCounts: %s", flags.c_str());
        Loggers::VK->info("\tStrictLines: %s", data->deviceProperties.limits.strictLines ? "true" : "false");
        Loggers::VK->info("\tSubPixelInterpolationOffsetBits: %lu", data->deviceProperties.limits.subPixelInterpolationOffsetBits);
        Loggers::VK->info("\tSubPixelPrecisionBits: %lu", data->deviceProperties.limits.subPixelPrecisionBits);
        Loggers::VK->info("\tSubTexelPrecisionBits: %lu", data->deviceProperties.limits.subTexelPrecisionBits);
        Loggers::VK->info("\tTimestampComputeAndGraphics: %s", data->deviceProperties.limits.timestampComputeAndGraphics ? "true" : "false");
        Loggers::VK->info("\tTimestampPeriod: %1.3f", data->deviceProperties.limits.timestampPeriod);
        Loggers::VK->info("\tViewportBoundsRange: %1.3f", data->deviceProperties.limits.viewportBoundsRange);
        Loggers::VK->info("\tViewportSubPixelBits: %lu", data->deviceProperties.limits.viewportSubPixelBits);
    }

    static void printDeviceFeatures(DeviceData* data) {
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

    static void printDeviceMemoryProperties(DeviceData* data) {
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

    static void printDeviceQueueFamilies(DeviceData* data) {
        int counter = 0;
        Loggers::VK->info("Queue families:");
        for (VkQueueFamilyProperties family:data->queueFamilies) {
            std::string flags = "";
            Loggers::VK->info("\tFamily #%i:",counter);
            Loggers::VK->info("\tQueueCount: %i", family.queueCount);
            if (family.queueFlags & VK_QUEUE_COMPUTE_BIT) {
                flags.append(" COMPUTE_BIT");
            }
            if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                flags.append(" GRAPHICS_BIT");
            }
            if (family.queueFlags & VK_QUEUE_TRANSFER_BIT) {
                flags.append(" TRANSFER_BIT");
            }
            if (family.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) {
                flags.append(" SPARSE_BINDING_BIT");
            }
            Loggers::VK->info("\tQueueFlags: %s", flags.c_str());
            Loggers::VK->info("");
            counter++;
        }
    }

    static void printDeviceData(DeviceData* data,bool printProperties, bool printLimits, bool printFeatures, bool printMemoryProperties, bool printQueueFamilies) {
        Loggers::VK->info("##### Device Data #####");
        if(printProperties)
            printDeviceProperties(data);
        if(printLimits)
            printDeviceLimits(data);
        if(printFeatures)
            printDeviceFeatures(data);
        if(printMemoryProperties)
            printDeviceMemoryProperties(data);
        if (printQueueFamilies)
            printDeviceQueueFamilies(data);
        Loggers::VK->info("#######################");
    }

    static void printSurfaceData(SurfaceData* data) {
        Loggers::VK->info("##### Surface Data #####");
        Loggers::VK->info("\tMin extent: [%ul/%lu]", data->surfaceCapabilities.minImageExtent.width, data->surfaceCapabilities.minImageExtent.height);
        Loggers::VK->info("\tMax extent: [%ul/%lu]", data->surfaceCapabilities.maxImageExtent.width, data->surfaceCapabilities.maxImageExtent.height);
        Loggers::VK->info("\tFormats:");
        for (VkSurfaceFormatKHR format:data->surfaceFormats) {
            switch (format.format) {
            case VK_FORMAT_B8G8R8A8_UNORM:
                Loggers::VK->info("\tVK_FORMAT_B8G8R8A8_UNORM VK_COLOR_SPACE_SRGB_NONLINEAR_KHR");
                break;
            case VK_FORMAT_B8G8R8A8_SRGB:
                Loggers::VK->info("\tVK_FORMAT_B8G8R8A8_SRGB VK_COLOR_SPACE_SRGB_NONLINEAR_KHR");
                break;
            case VK_FORMAT_A2B10G10R10_UNORM_PACK32:
                Loggers::VK->info("\tVK_FORMAT_A2B10G10R10_UNORM_PACK32 VK_COLOR_SPACE_SRGB_NONLINEAR_KHR");
                break;
            default:
                Loggers::VK->info("\t%i %i",format.format, format.colorSpace);
                break;
            }
            
        }
        Loggers::VK->info("\tPresent modes:");
        for (VkPresentModeKHR mode : data->presentModes) {
            switch (mode) {
            case VK_PRESENT_MODE_IMMEDIATE_KHR:
                Loggers::VK->info("\tVK_PRESENT_MODE_IMMEDIATE_KHR");
                break;
            case VK_PRESENT_MODE_MAILBOX_KHR:
                Loggers::VK->info("\tVK_PRESENT_MODE_MAILBOX_KHR");
                break;
            case VK_PRESENT_MODE_FIFO_KHR:
                Loggers::VK->info("\tVK_PRESENT_MODE_FIFO_KHR");
                break;
            case VK_PRESENT_MODE_FIFO_RELAXED_KHR:
                Loggers::VK->info("\tVK_PRESENT_MODE_FIFO_RELAXED_KHR");
                break;
            }
        }
        Loggers::VK->info("#######################");
    }
};