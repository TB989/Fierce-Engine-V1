#include "VK_Context.h"

#include "src/core/Core.h"
#include "VK_Instance.h"
#include "VK_Surface.h"
#include "VK_Device.h"

VK_Context::VK_Context(Core* core){
	instance = new VK_Instance(&(core->m_settings));
	instance->addRequiredExtension(VK_KHR_SURFACE_EXTENSION_NAME);
	instance->addRequiredExtension("VK_KHR_win32_surface");
	instance->addDesiredExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	instance->addDesiredValidationLayer("VK_LAYER_KHRONOS_validation");
	instance->create();
	instance->printEnabledExtensions();
	instance->printEnabledValidationLayers();

	surface = new VK_Surface(core,instance->getId());
	surface->create();

	device = new VK_Device(instance->getId(),surface->getId());
	device->create();
}

VK_Context::~VK_Context(){
	delete device;
	delete surface;
	delete instance;
}