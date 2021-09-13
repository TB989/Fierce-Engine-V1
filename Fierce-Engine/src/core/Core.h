#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "EngineSettings.h"
#include "src/system/event/EventSystem.h"
#include "src/system/event/Event.h"
#include "src/system/render/abstract/RenderSystem.h"
#include "src/ecs/World.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class WindowSystem;
class FierceWindow;

class Core {
public:
	Core();
	~Core();

	void run();

protected:
	virtual void init(World* world) = 0;
	virtual void update(World* world,float dt) = 0;
	virtual void render(World* world) = 0;
	virtual void cleanUp(World* world) = 0;

private:
	void coreInit();
	void coreUpdate();
	void coreRender();
	void coreCleanUp();

	void onWindowClosed(WindowCloseEvent* event);

private:
	bool running=false;

	World* world;

protected:
	WindowSystem* windowSystem = nullptr;
	FierceWindow* m_window = nullptr;

	RenderSystem* renderSystem=nullptr;

public:
	EngineSettings m_settings = {};
	EventSystem* eventSystem = nullptr;
};