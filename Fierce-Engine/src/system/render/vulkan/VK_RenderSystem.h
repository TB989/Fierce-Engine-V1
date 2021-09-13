#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/system/render/abstract/RenderSystem.h"
#include "VK_Context.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class Core;

class VK_RenderSystem:public RenderSystem {
public:
	VK_RenderSystem(Core* core);
	~VK_RenderSystem();

private:
	VK_Context* context;
};