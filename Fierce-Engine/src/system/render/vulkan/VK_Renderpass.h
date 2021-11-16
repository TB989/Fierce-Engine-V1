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

class VK_Renderpass{
public:
	VK_Renderpass(VK_Device* device);
	~VK_Renderpass();

	void create();

	void addAttachment(VkImageLayout initialLayout, VkImageLayout finalLayout,VkImageLayout layout);

	VkRenderPass getID() { return renderpass; }

private:
	VK_Device* m_device;
	VkRenderPass renderpass;
	int counter = 0;

	std::vector<VkAttachmentDescription> attachments;
	std::vector<VkAttachmentReference> attachmentReferences;
};