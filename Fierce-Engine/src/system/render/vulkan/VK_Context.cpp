#include "VK_Context.h"

#include "src/core/Core.h"
#include "VK_Instance.h"
#include "VK_Surface.h"
#include "VK_Device.h"

#include "VK_CompatibilityChecks.h"

VK_Context::VK_Context(Core* core){
	Loggers::VK->info("Creating instance.");
	instance = new VK_Instance(&(core->m_settings));
	instance->addCheck(new VK_Check_Device_Extensions(true, { VK_KHR_SURFACE_EXTENSION_NAME, "VK_KHR_win32_surface" }));
	instance->addCheck(new VK_Check_Device_Extensions(false, { VK_EXT_DEBUG_UTILS_EXTENSION_NAME }));
	instance->addCheck(new VK_Check_Device_ValidationLayers(false, { "VK_LAYER_KHRONOS_validation" }));
	instance->create();

	Loggers::VK->info("Creating window surface.");
	surface = new VK_Surface(core,instance->getId());
	surface->create();

	Loggers::VK->info("Creating device.");
	device = new VK_Device(instance->getId(),surface->getId());
	device->addCheck(new VK_Check_Device_Extensions(true, { VK_KHR_SWAPCHAIN_EXTENSION_NAME }));
	device->addCheck(new VK_Check_Device_ValidationLayers(false, { "VK_LAYER_KHRONOS_validation" }));
	device->addCheck(new VK_Check_Device_General());
	device->addCheck(new VK_Check_Device_Queues());
	device->addCheck(new VK_Check_Device_Surface_Format({ VK_FORMAT_B8G8R8A8_SRGB }));
	device->addCheck(new VK_Check_Device_Surface_PresentMode({ VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR }));
	device->create();

	Loggers::VK->info("Creating swapchain.");
	swapchain = new VK_Swapchain(device,surface->getId());
	swapchain->create();
}

VK_Context::~VK_Context(){
	delete swapchain;
	delete device;
	delete surface;
	delete instance;
}