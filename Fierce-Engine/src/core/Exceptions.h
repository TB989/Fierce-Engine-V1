#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/utils/FierceStrings.h"

/* SystemIncludes*/
#include <Windows.h>
#include <stdexcept>

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
	FE_IO_ERROR
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