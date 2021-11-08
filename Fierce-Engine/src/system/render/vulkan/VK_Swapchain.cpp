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
	SurfaceData* surfaceData = m_device->getSurfaceData();
	VkExtent2D extent = surfaceData->surfaceCapabilities.currentExtent;
	extent.width = max(extent.width, surfaceData->surfaceCapabilities.minImageExtent.width);
	extent.width = min(extent.width, surfaceData->surfaceCapabilities.maxImageExtent.width);
	extent.height = max(extent.height, surfaceData->surfaceCapabilities.minImageExtent.height);
	extent.height = min(extent.height, surfaceData->surfaceCapabilities.maxImageExtent.height);

	uint32_t imageCount = surfaceData->surfaceCapabilities.minImageCount + 1;
	if (surfaceData->surfaceCapabilities.maxImageCount > 0 && imageCount > surfaceData->surfaceCapabilities.maxImageCount) {
		imageCount = surfaceData->surfaceCapabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.surface = m_surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = m_device->getSurfaceData()->swapchainFormat.format;
	createInfo.imageColorSpace = m_device->getSurfaceData()->swapchainFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	createInfo.queueFamilyIndexCount = 0;
	createInfo.pQueueFamilyIndices = nullptr;
	createInfo.preTransform = surfaceData->surfaceCapabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = m_device->getSurfaceData()->swapchainPresentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	CHECK_VK(vkCreateSwapchainKHR(m_device->getDevice(), &createInfo, nullptr, &m_swapchain), "Failed to create swapchain.");
}