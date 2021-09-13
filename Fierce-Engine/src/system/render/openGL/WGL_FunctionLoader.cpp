#include "WGL_FunctionLoader.h"
#include "src/core/Exceptions.h"
#include "src/system/logging/Logger.h"

wglCreateContextAttribsARB_type* wglCreateContextAttribsARB = nullptr;
wglChoosePixelFormatARB_type* wglChoosePixelFormatARB = nullptr;

void* getWGLFunctionPointer(const char* name) {
	void* p = (void*)wglGetProcAddress(name);
	if (p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1)) {
		Loggers::GL->error("Failed to load function %s.", name);
	}

	return p;
}

void loadAllWGLFunctions(){
	wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*)getWGLFunctionPointer("wglCreateContextAttribsARB");
	wglChoosePixelFormatARB = (wglChoosePixelFormatARB_type*)getWGLFunctionPointer("wglChoosePixelFormatARB");
}