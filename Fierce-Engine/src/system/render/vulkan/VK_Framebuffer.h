#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

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

class VK_Device;

class VK_Framebuffer{
public:
	VK_Framebuffer(VK_Device* device,VkRenderPass renderpass);
	~VK_Framebuffer();

	void create();

	void addAttachments(std::vector<VkImageView> attachments);

private:
	VK_Device* m_device;
	VkRenderPass m_renderpass;

	VkFramebuffer framebuffer;
	std::vector<VkImageView> m_attachments;
};