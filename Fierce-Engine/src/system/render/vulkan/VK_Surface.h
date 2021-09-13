#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

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
class Core;
struct WindowSendHandleEvent;

class VK_Surface{
public:
	VK_Surface(Core* core, VkInstance instance);
	~VK_Surface();

	void create();
	VkSurfaceKHR getId() { return surface; }

private:
	VkInstance m_instance=VK_NULL_HANDLE;
	HWND windowHandle = nullptr;
	VkSurfaceKHR surface=VK_NULL_HANDLE;

private:
	void onHandleReceived(WindowSendHandleEvent* evt);
};