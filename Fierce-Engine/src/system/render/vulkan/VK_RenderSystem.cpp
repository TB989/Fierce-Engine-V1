#include "VK_RenderSystem.h"

#include "src/core/Core.h"
#include "src/system/logging/Logger.h"

#include "VK_Renderpass.h"
#include "VK_Framebuffer.h"

VK_RenderSystem::VK_RenderSystem(Core* core){
	Loggers::VK->info("########## Starting vulkan ##########");
	context = new VK_Context(core);
	createRenderpasses();
	createFramebuffers();
	createCommandbuffers();
}

VK_RenderSystem::~VK_RenderSystem(){
	for (auto buffer:defaultCommandbuffers) {
		delete buffer;
	}
	for (auto framebuffer:defaultFramebuffers) {
		delete framebuffer;
	}
	delete defaultRenderpass;
	delete context;
}

void VK_RenderSystem::createRenderpasses(){
	Loggers::VK->info("Creating renderpasses.");
	defaultRenderpass = new VK_Renderpass(context->getDevice());
	defaultRenderpass->addAttachment(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
	defaultRenderpass->create();
}

void VK_RenderSystem::createFramebuffers(){
	Loggers::VK->info("Creating framebuffers.");
	for (int i = 0;i<context->getNumSwapchainImages();i++) {
		VK_Framebuffer* framebuffer = new VK_Framebuffer(context->getDevice(), defaultRenderpass->getID());
		framebuffer->addAttachments({ context->getSwapchainImage(i) });
		framebuffer->create();
		defaultFramebuffers.push_back(framebuffer);
	}
}

void VK_RenderSystem::createCommandbuffers(){
	Loggers::VK->info("Creating commandbuffers.");
	for (int i = 0; i < context->getNumSwapchainImages(); i++) {
		defaultCommandbuffers.push_back(context->getDevice()->getCommandBuffer());
	}
}