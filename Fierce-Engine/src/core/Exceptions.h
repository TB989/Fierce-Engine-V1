#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/utils/FierceStrings.h"

/* SystemIncludes*/
#include <Windows.h>
#include <stdexcept>

#include "vulkan/vulkan.h"
#include "src/system/render/openGL/GL_Include.h"

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

enum FIERCE_ERROR {
	FE_NO_ERROR,
	FE_WINDOW_ERROR,
	FE_CONTEXT_ERROR,
	FE_IO_ERROR,
	FE_NOT_SUPPORTED_ERROR
};

class Fierce_Exception :public std::runtime_error {
public:
	Fierce_Exception(std::string message) :runtime_error(message) {}
};

inline void CHECK_FIERCE(FIERCE_ERROR result, std::string message) {
	std::string errorString;
	switch (result) {
	case FE_NO_ERROR:
		return;
	case FE_WINDOW_ERROR:
		errorString = "FIERCE Error: FE_WINDOW_ERROR";
		break;
	case FE_CONTEXT_ERROR:
		errorString = "FIERCE Error: FE_CONTEXT_ERROR";
		break;
	case FE_IO_ERROR:
		errorString = "FIERCE Error: FE_IO_ERROR";
		break;
	case FE_NOT_SUPPORTED_ERROR:
		errorString = "FIERCE Error: FE_NOT_SUPPORTED_ERROR";
		break;
	default:
		errorString = "FIERCE Error: FE_UNKNOWN_ERROR";
	}

	std::wstring temp1 = std::wstring(message.begin(), message.end());
	std::wstring temp2 = std::wstring(errorString.begin(), errorString.end());
	MessageBox(NULL, temp1.c_str(), temp2.c_str(), MB_ICONERROR);
	throw Fierce_Exception(message.c_str());
}

class Win_Exception :public std::runtime_error {
public:
	Win_Exception(std::string message) :runtime_error(message) {}
};

inline void CHECK_WIN(DWORD result, std::string message) {
	std::string errorString;

	switch (result) {
	case 0:
		return;

	default:
		errorString = "Win Error: ["+std::to_string(result)+"]";
	}

	std::wstring temp1 = std::wstring(message.begin(), message.end());
	std::wstring temp2 = std::wstring(errorString.begin(), errorString.end());
	MessageBox(NULL, temp1.c_str(), temp2.c_str(), MB_ICONERROR);
	throw Win_Exception(message.c_str());
}

class GL_Exception :public std::runtime_error {
public:
	GL_Exception(std::string message) :runtime_error(message) {}
};

inline void CHECK_GL(GLenum result, std::string message) {
	std::string errorString;
	switch (result) {
	case GL_NO_ERROR:
		return;

	case GL_INVALID_ENUM:
		errorString = "GL Error: GL_INVALID_ENUM";
		break;
	case GL_INVALID_VALUE:
		errorString = "GL Error: GL_INVALID_VALUE";
		break;
	case GL_INVALID_OPERATION:
		errorString = "GL Error: GL_INVALID_OPERATION";
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		errorString = "GL Error: GL_INVALID_FRAMEBUFFER_OPERATION";
		break;
	case GL_OUT_OF_MEMORY:
		errorString = "GL Error: GL_OUT_OF_MEMORY";
		break;
	case GL_STACK_UNDERFLOW:
		errorString = "GL Error: GL_STACK_UNDERFLOW";
		break;
	case GL_STACK_OVERFLOW:
		errorString = "GL Error: GL_STACK_OVERFLOW";
		break;
	default:
		errorString = "GL Error: GL_UNKNOWN_ERROR";
	}

	std::wstring temp1 = std::wstring(message.begin(), message.end());
	std::wstring temp2 = std::wstring(errorString.begin(), errorString.end());
	MessageBox(NULL, temp1.c_str(), temp2.c_str(), MB_ICONERROR);
	throw GL_Exception(message.c_str());
}

class VK_Exception :public std::runtime_error {
public:
	VK_Exception(std::string message) :runtime_error(message) {}
};

inline void CHECK_VK(VkResult result, std::string message) {
	std::string errorString;
	switch (result) {
	case VK_SUCCESS:
	case VK_NOT_READY:
	case VK_TIMEOUT:
	case VK_EVENT_SET:
	case VK_EVENT_RESET:
	case VK_INCOMPLETE:
	case VK_SUBOPTIMAL_KHR:
		return;

	case VK_ERROR_OUT_OF_HOST_MEMORY:
		errorString = "VK Error: VK_ERROR_OUT_OF_HOST_MEMORY";
		break;
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		errorString = "VK Error: VK_ERROR_OUT_OF_DEVICE_MEMORY";
		break;
	case VK_ERROR_INITIALIZATION_FAILED:
		errorString = "VK Error: VK_ERROR_INITIALIZATION_FAILED";
		break;
	case VK_ERROR_MEMORY_MAP_FAILED:
		errorString = "VK Error: VK_ERROR_MEMORY_MAP_FAILED";
		break;
	case VK_ERROR_DEVICE_LOST:
		errorString = "VK Error: VK_ERROR_DEVICE_LOST";
		break;
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		errorString = "VK Error: VK_ERROR_EXTENSION_NOT_PRESENT";
		break;
	case VK_ERROR_FEATURE_NOT_PRESENT:
		errorString = "VK Error: VK_ERROR_FEATURE_NOT_PRESENT";
		break;
	case VK_ERROR_LAYER_NOT_PRESENT:
		errorString = "VK Error: VK_ERROR_LAYER_NOT_PRESENT";
		break;
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		errorString = "VK Error: VK_ERROR_INCOMPATIBLE_DRIVER";
		break;
	case VK_ERROR_TOO_MANY_OBJECTS:
		errorString = "VK Error: VK_ERROR_TOO_MANY_OBJECTS";
		break;
	case VK_ERROR_FORMAT_NOT_SUPPORTED:
		errorString = "VK Error: VK_ERROR_FORMAT_NOT_SUPPORTED";
		break;
	case VK_ERROR_SURFACE_LOST_KHR:
		errorString = "VK Error: VK_ERROR_SURFACE_LOST_KHR";
		break;
	case VK_ERROR_OUT_OF_DATE_KHR:
		errorString = "VK Error: VK_ERROR_OUT_OF_DATE_KHR";
		break;
	case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
		errorString = "VK Error: VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
		break;
	case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
		errorString = "VK Error: VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
		break;
	case VK_ERROR_VALIDATION_FAILED_EXT:
		errorString = "VK Error: VK_ERROR_VALIDATION_FAILED_EXT";
		break;
	default:
		errorString = "VK Error: VK_UNKNOWN_ERROR";
	}

	std::wstring temp1 = std::wstring(message.begin(), message.end());
	std::wstring temp2 = std::wstring(errorString.begin(), errorString.end());
	MessageBox(NULL, temp1.c_str(), temp2.c_str(), MB_ICONERROR);
	throw VK_Exception(message.c_str());
}