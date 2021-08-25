#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/core/EngineSettings.h"

/* SystemIncludes*/
#include <Windows.h>
#include <windowsx.h>
#include <map>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class Core;
class FierceWindow;
enum FIERCE_ERROR;
struct WindowRequestHandleEvent;

class WindowSystem {
public:
	WindowSystem(Core* app, EngineSettings* settings);
	~WindowSystem();

	FierceWindow* getWindow() { return m_window; }

	template<typename EventType>
	void postEvent(EventType* evnt) {
		m_app->eventSystem->postEvent(evnt);
	}

private:
	FIERCE_ERROR registerWindowClass(LPCWSTR className, WNDPROC wndProc);
	FIERCE_ERROR unregisterWindowClass(LPCWSTR className);

	void onHandleRequested(WindowRequestHandleEvent* evt);
private:
	Core* m_app=nullptr;
	EngineSettings* m_settings = {};

	HINSTANCE hInstance=nullptr;
	LPCWSTR fierceWindowClassName = L"FierceWindow";
	LPCWSTR fierceDummyWindowClassName = L"FierceDummyWindow";

	FierceWindow* m_window=nullptr;
	FierceWindow* m_dummyWindow=nullptr;
};