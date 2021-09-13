#include "GL_RenderSystem.h"

#include "src/core/Core.h"
#include "src/system/logging/Logger.h"

GL_RenderSystem::GL_RenderSystem(Core* core){
	Loggers::GL->info("########## Starting openGL ##########");
	context = new GL_Context(core);
}

GL_RenderSystem::~GL_RenderSystem(){
	delete context;
}