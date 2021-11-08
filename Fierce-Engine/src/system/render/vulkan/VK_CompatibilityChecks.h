#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/system/logging/Logger.h"

/* SystemIncludes*/
#include <vector>
#include "vulkan/vulkan.h"

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

struct ExtensionValidationLayerData {
	std::vector<VkExtensionProperties> supportedExtensions;
	std::vector<const char*> enabledExtensions;

	std::vector<VkLayerProperties> supportedValidationLayers;
	std::vector<const char*> enabledValidationLayers;
};

struct DeviceData {
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
	std::vector<VkQueueFamilyProperties> queueFamilies;
	std::vector<bool> presentSupport;

	int graphicsQueueIndex = -1;
	int transferQueueIndex = -1;
	int computeQueueIndex = -1;
};

struct SurfaceData {
	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	std::vector<VkSurfaceFormatKHR> surfaceFormats;
	std::vector<VkPresentModeKHR> presentModes;

	VkSurfaceFormatKHR swapchainFormat;
	VkPresentModeKHR swapchainPresentMode;
};

class VK_CompatibilityCheck_Device{
public:
	virtual bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3)=0;
};

class VK_Check_Device_Extensions :public VK_CompatibilityCheck_Device {
public:
	VK_Check_Device_Extensions(bool required, std::vector<const char*> extensions) {
		m_required = required;
		m_extensions = extensions;
	}

	bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);

private:
	bool m_required;
	std::vector<const char*> m_extensions;

	bool isExtensionSupported(const char* extensionName, std::vector<VkExtensionProperties>* supportedExtensions);
};

class VK_Check_Device_ValidationLayers :public VK_CompatibilityCheck_Device {
public:
	VK_Check_Device_ValidationLayers(bool required, std::vector<const char*> layers) {
		m_required = required;
		m_layers = layers;
	}

	bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);

private:
	bool m_required;
	std::vector<const char*> m_layers;

	bool isValidationLayerSupported(const char* layerName, std::vector<VkLayerProperties>* supportedLayers);
};

class VK_Check_Device_General:public VK_CompatibilityCheck_Device{
public:
	VK_Check_Device_General() {};

	bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);
};

class VK_Check_Device_Queues :public VK_CompatibilityCheck_Device {
public:
	VK_Check_Device_Queues() {};

	bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);
};

class VK_Check_Device_Surface_Format :public VK_CompatibilityCheck_Device {
public:
	VK_Check_Device_Surface_Format(std::vector<VkFormat> formats) {
		m_formats=formats;
	};

	bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);

private:
	std::vector<VkFormat> m_formats;
};

class VK_Check_Device_Surface_PresentMode :public VK_CompatibilityCheck_Device {
public:
	VK_Check_Device_Surface_PresentMode(std::vector<VkPresentModeKHR> presentModes) {
		m_presentModes = presentModes;
	};

	bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);

private:
	std::vector<VkPresentModeKHR> m_presentModes;
};