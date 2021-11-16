#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/system/render/abstract/RenderSystem.h"
#include "VK_Context.h"
#include "VK_Renderpass.h"

/* SystemIncludes*/
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class Core;
class VK_Renderpass;
class VK_Framebuffer;

class VK_RenderSystem:public RenderSystem {
public:
	VK_RenderSystem(Core* core);
	~VK_RenderSystem();

private:
	VK_Context* context;
	VK_Renderpass* defaultRenderpass;
	std::vector<VK_Framebuffer*> defaultFramebuffers;
	std::vector<VK_CommandBuffer*> defaultCommandbuffers;

	void createRenderpasses();
	void createFramebuffers();
	void createCommandbuffers();
};