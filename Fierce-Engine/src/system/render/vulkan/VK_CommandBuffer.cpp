#include "VK_CommandBuffer.h"

#include "src/core/Exceptions.h"

VK_CommandBuffer::VK_CommandBuffer(VkDevice device,VkCommandPool commandPool){
    mDevice=device;
    mCommandPool = commandPool;
}

VK_CommandBuffer::~VK_CommandBuffer(){
    vkFreeCommandBuffers(mDevice, mCommandPool, 1, &buffer);
}

void VK_CommandBuffer::create(){
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.pNext = nullptr;
    allocInfo.commandPool = mCommandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    CHECK_VK(vkAllocateCommandBuffers(mDevice, &allocInfo, &buffer), "Failed to allocate command buffers.");
}