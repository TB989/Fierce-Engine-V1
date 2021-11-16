#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/system/render/abstract/RenderSystem.h"
#include "GL_Context.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class Core;

class GL_RenderSystem: public RenderSystem{
public:
	GL_RenderSystem(Core* core);
	~GL_RenderSystem();

private:
	GL_Context* context;

	void createRenderpasses();
	void createFramebuffers();
	void createCommandbuffers();
};