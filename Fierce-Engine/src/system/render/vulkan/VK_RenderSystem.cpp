#include "VK_RenderSystem.h"

#include "src/core/Core.h"
#include "src/system/logging/Logger.h"

VK_RenderSystem::VK_RenderSystem(Core* core){
	Loggers::VK->info("########## Starting vulkan ##########");
	context = new VK_Context(core);
}

VK_RenderSystem::~VK_RenderSystem(){
	delete context;
}