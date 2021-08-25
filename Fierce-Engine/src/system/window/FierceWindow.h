#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/core/EngineSettings.h"

/* SystemIncludes*/
#include <Windows.h>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
enum FIERCE_ERROR;

class FierceWindow {
public:
	FierceWindow(LPCWSTR className, LPCWSTR title, EngineSettings* settings,bool dummy);
	~FierceWindow();

	void pollEvents();
	void show();

	HWND getHandle() { return windowHandle; }
private:
	FIERCE_ERROR createWindow(LPCWSTR className, LPCWSTR title, EngineSettings* settings, bool dummy);
	FIERCE_ERROR destroyWindow();
private:
	HWND windowHandle=nullptr;
};