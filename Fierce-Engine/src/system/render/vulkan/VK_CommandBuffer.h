#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

/* SystemIncludes*/
#include "vulkan/vulkan.h"

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class VK_CommandBuffer{
public:
	VK_CommandBuffer(VkDevice device,VkCommandPool commandPool);
	~VK_CommandBuffer();

	void create();

private:
	VkDevice mDevice;
	VkCommandPool mCommandPool;
	VkCommandBuffer buffer;
};