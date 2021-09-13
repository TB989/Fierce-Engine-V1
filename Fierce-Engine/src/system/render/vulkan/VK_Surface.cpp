#include "VK_Surface.h"

#include "src/core/Core.h"
#include "src/core/Exceptions.h"
#include "src/system/event/EventSystem.h"
#include "src/system/event/Event.h"

VK_Surface::VK_Surface(Core* core, VkInstance instance){
	m_instance = instance;

	core->eventSystem->addListener(this, &VK_Surface::onHandleReceived);
	core->eventSystem->postEvent(new WindowRequestHandleEvent(false));
	if (windowHandle == nullptr) {
		CHECK_VK(VK_ERROR_INITIALIZATION_FAILED, "Failed to get valid window handles for vulkan surface.");
	}
}

VK_Surface::~VK_Surface(){
	vkDestroySurfaceKHR(m_instance, surface, nullptr);
}

void VK_Surface::create(){
	VkWin32SurfaceCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.hwnd = windowHandle;
	createInfo.hinstance = GetModuleHandle(nullptr);

	CHECK_VK(vkCreateWin32SurfaceKHR(m_instance, &createInfo, nullptr, &surface), "Failed to create vulkan surface.");
}

void VK_Surface::onHandleReceived(WindowSendHandleEvent* evt) {
	windowHandle = evt->m_handle;
}