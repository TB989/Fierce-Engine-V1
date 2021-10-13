#include "VK_Swapchain.h"

#include "src/core/Exceptions.h"

VK_Swapchain::VK_Swapchain(VK_Device* device, VkSurfaceKHR surface){
	m_device = device;
	m_surface = surface;
}

VK_Swapchain::~VK_Swapchain(){
	vkDestroySwapchainKHR(m_device->getDevice(), m_swapchain, nullptr);
}

void VK_Swapchain::create(){
	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.surface = m_surface;
	createInfo.minImageCount = m_device->getSurfaceData()->imageCount;
	createInfo.imageFormat = m_device->getSurfaceData()->swapchainFormat.format;
	createInfo.imageColorSpace = m_device->getSurfaceData()->swapchainFormat.colorSpace;
	createInfo.imageExtent = m_device->getSurfaceData()->swapchainExtent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	createInfo.queueFamilyIndexCount = 0;
	createInfo.pQueueFamilyIndices = nullptr;
	createInfo.preTransform = m_device->getSurfaceData()->swapchainTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = m_device->getSurfaceData()->swapchainPresentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	CHECK_VK(vkCreateSwapchainKHR(m_device->getDevice(), &createInfo, nullptr, &m_swapchain), "Failed to create swapchain.");
}