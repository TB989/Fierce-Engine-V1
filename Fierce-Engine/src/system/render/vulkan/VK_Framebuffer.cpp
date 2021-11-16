#include "VK_Framebuffer.h"

#include "VK_Device.h"

VK_Framebuffer::VK_Framebuffer(VK_Device* device, VkRenderPass renderpass){
    m_device = device;
    m_renderpass = renderpass;
}

VK_Framebuffer::~VK_Framebuffer(){
    vkDestroyFramebuffer(m_device->getDevice(), framebuffer, nullptr);
}

void VK_Framebuffer::create(){
    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.pNext = nullptr;
    framebufferInfo.flags = 0;
    framebufferInfo.renderPass = m_renderpass;
    framebufferInfo.attachmentCount = m_attachments.size();
    framebufferInfo.pAttachments = m_attachments.data();
    framebufferInfo.width = m_device->getSurfaceData()->swapchainWidth;
    framebufferInfo.height = m_device->getSurfaceData()->swapchainHeight;
    framebufferInfo.layers = 1;

    CHECK_VK(vkCreateFramebuffer(m_device->getDevice(), &framebufferInfo, nullptr, &framebuffer), "Failed to create framebuffer.");
}

void VK_Framebuffer::addAttachments(std::vector<VkImageView> attachments){
    m_attachments = attachments;
}