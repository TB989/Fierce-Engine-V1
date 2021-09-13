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

struct EngineSettings;

class VK_Instance{
public:
	VK_Instance(EngineSettings* settings);
	~VK_Instance();

public:
	void addRequiredExtension(const char* extension) {requiredExtensions.push_back(extension);}
	void addDesiredExtension(const char* extension) {desiredExtensions.push_back(extension);}
	void addRequiredValidationLayer(const char* layer) {requiredValidationLayers.push_back(layer);}
	void addDesiredValidationLayer(const char* layer) {desiredValidationLayers.push_back(layer);}

	void create();
	VkInstance getId() {return instance;}

	void printSupportedExtensions() { VK_Helper_Extensions_ValidationLayers::printExtensions(true, "supported",&supportedExtensions); }
	void printEnabledExtensions() { VK_Helper_Extensions_ValidationLayers::printExtensions(true, "enabled", &enabledExtensions); }
	void printSupportedValidationLayers() { VK_Helper_Extensions_ValidationLayers::printValidationLayers(true,"supported",&supportedValidationLayers); }
	void printEnabledValidationLayers() { VK_Helper_Extensions_ValidationLayers::printValidationLayers(true,"enabled",&enabledValidationLayers); }

private:
	void checkExtensionSupport() { VK_Helper_Extensions_ValidationLayers::checkExtensionSupport(&supportedExtensions,&enabledExtensions,&requiredExtensions,&desiredExtensions); }
	void checkValidationLayerSupport() { VK_Helper_Extensions_ValidationLayers::checkValidationLayerSupport(&supportedValidationLayers, &enabledValidationLayers, &requiredValidationLayers, &desiredValidationLayers); }

	PFN_vkCreateDebugUtilsMessengerEXT loadCreateFunctionPointer(VkInstance instance);
	PFN_vkDestroyDebugUtilsMessengerEXT loadDestroyFunctionPointer(VkInstance instance);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

private:
	VkInstance instance;

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