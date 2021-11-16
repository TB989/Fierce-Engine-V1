#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/system/render/abstract/RenderingContext.h"
#include "VK_Swapchain.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class Core;
class VK_Instance;
class VK_Surface;
class VK_Device;

class VK_Context:public RenderingContext {
public:
	VK_Context(Core* core);
	~VK_Context();

	VK_Device* getDevice() { return device; }

	VkImageView getSwapchainImage(int index) { return swapchain->getImage(index); }
	int getNumSwapchainImages() { return swapchain->getNumImages(); }

private:
	VK_Instance* instance;
	VK_Surface* surface;
	VK_Device* device;
	VK_Swapchain* swapchain;
};