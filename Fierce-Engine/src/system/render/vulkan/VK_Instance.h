#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/utils/FierceStrings.h"
#include "VK_Helper_Extensions_ValidationLayers.h"
#include "VK_CompatibilityChecks.h"

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

struct EngineSettings;

class VK_Instance{
public:
	VK_Instance(EngineSettings* settings);
	~VK_Instance();

public:
	void addCheck(VK_CompatibilityCheck_Device* check) { checks.push_back(check); }
	
	void create();
	VkInstance getId() {return instance;}

private:
	bool checkInstanceCompatibility(ExtensionValidationLayerData* data, DeviceData* deviceData, SurfaceData* surfaceData);

	PFN_vkCreateDebugUtilsMessengerEXT loadCreateFunctionPointer(VkInstance instance);
	PFN_vkDestroyDebugUtilsMessengerEXT loadDestroyFunctionPointer(VkInstance instance);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

private:
	VkInstance instance;

	ExtensionValidationLayerData extensionLayerData;

	std::vector<VK_CompatibilityCheck_Device*> checks;

	bool isDebugSupported=false;
	PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
	PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
	VkDebugUtilsMessengerEXT debugMessenger;

private:
	uint32_t API_VERSION;
	std::string APP_NAME = "FIERCE-APP";
	uint32_t APP_VERSION= VK_MAKE_VERSION(1, 0, 0);
	std::string ENGINE_NAME = "FIERCE-ENGINE";
	uint32_t ENGINE_VERSION = VK_MAKE_VERSION(1, 0, 0);
};