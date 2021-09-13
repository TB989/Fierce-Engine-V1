#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/utils/FierceStrings.h"
#include "VK_Helper_Extensions_ValidationLayers.h"

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
//class VK_Renderpass;
//class VK_Framebuffers;
//class VK_Pipeline;

class VK_Device{
public:
	VK_Device(VkInstance instance, VkSurfaceKHR surface);
	~VK_Device();

public:
	void addRequiredExtension(const char* extension) { requiredExtensions.push_back(extension); }
	void addDesiredExtension(const char* extension) { desiredExtensions.push_back(extension); }
	void addRequiredValidationLayer(const char* layer) { requiredValidationLayers.push_back(layer); }
	void addDesiredValidationLayer(const char* layer) { desiredValidationLayers.push_back(layer); }

	void create();
	VkDevice getDevice() { return device; }
	VkQueue getQueue() { return graphicsQueue; }

	void printSupportedExtensions() { VK_Helper_Extensions_ValidationLayers::printExtensions(false, "supported", &supportedExtensions); }
	void printEnabledExtensions() { VK_Helper_Extensions_ValidationLayers::printExtensions(false, "enabled", &enabledExtensions); }
	void printSupportedValidationLayers() { VK_Helper_Extensions_ValidationLayers::printValidationLayers(false, "supported", &supportedValidationLayers); }
	void printEnabledValidationLayers() { VK_Helper_Extensions_ValidationLayers::printValidationLayers(false, "enabled", &enabledValidationLayers); }

public:
	struct DeviceData {
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
		std::vector<VkQueueFamilyProperties> queueFamilies;

		VkSurfaceCapabilitiesKHR surfaceCapabilities;
		std::vector<VkSurfaceFormatKHR> surfaceFormats;
		std::vector<VkPresentModeKHR> presentModes;

		bool isCompatible = true;
		int queueFamilyIndex = -1;

		VkSurfaceFormatKHR swapchainFormat;
		VkPresentModeKHR swapchainPresentMode;
		VkExtent2D swapchainExtent;
		int imageCount;
		VkSurfaceTransformFlagBitsKHR swapchainTransform;
	};
private:
	void pickPhysicalDevice();
	void checkDeviceCompatibility(VkPhysicalDevice device, DeviceData* deviceData);

	void createLogicalDevice();

private:
	void checkExtensionSupport() { VK_Helper_Extensions_ValidationLayers::checkExtensionSupport(&supportedExtensions, &enabledExtensions, &requiredExtensions, &desiredExtensions); }
	void checkValidationLayerSupport() { VK_Helper_Extensions_ValidationLayers::checkValidationLayerSupport(&supportedValidationLayers, &enabledValidationLayers, &requiredValidationLayers, &desiredValidationLayers); }

private:
	VkInstance m_instance=VK_NULL_HANDLE;
	VkSurfaceKHR m_surface=VK_NULL_HANDLE;
	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
	int queueFamilyIndex=-1;
	VkDevice device;
	VkQueue graphicsQueue;

private:
	std::vector<VkExtensionProperties> supportedExtensions;
	std::vector<const char*> requiredExtensions;
	std::vector<const char*> desiredExtensions;
	std::vector<const char*> enabledExtensions;

	std::vector<VkLayerProperties> supportedValidationLayers;
	std::vector<const char*> requiredValidationLayers;
	std::vector<const char*> desiredValidationLayers;
	std::vector<const char*> enabledValidationLayers;
};