#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "EngineSettings.h"
#include "src/system/event/EventSystem.h"
#include "src/system/event/Event.h"

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
	virtual void init() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void cleanUp() = 0;

private:
	void coreInit();
	void coreUpdate();
	void coreRender();
	void coreCleanUp();

	void onWindowClosed(WindowCloseEvent* event);

private:
	bool running = false;

protected:
	EngineSettings m_settings = {};

	WindowSystem* windowSystem = nullptr;
	FierceWindow* m_window = nullptr;

public:
	EventSystem* eventSystem = nullptr;
};