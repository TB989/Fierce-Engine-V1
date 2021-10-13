#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "VK_Device.h"

/* SystemIncludes*/
#include "vulkan/vulkan.h"
#include <Windows.h>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class VK_Swapchain{
public:
	VK_Swapchain(VK_Device* device,VkSurfaceKHR surface);
	~VK_Swapchain();

	void create();
	VkSwapchainKHR getId() { return m_swapchain; }

private:
	VK_Device* m_device=nullptr;
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;

	VkSwapchainKHR m_swapchain=VK_NULL_HANDLE;
};