#include "FierceWindow.h"

#include "src/core/Exceptions.h"
#include "src/system/logging/Logger.h"

#include <windows.h>
#include <strsafe.h>

FierceWindow::FierceWindow(LPCWSTR className, LPCWSTR title, EngineSettings* settings,bool dummy) {
	CHECK_FIERCE(createWindow(className, title, settings,dummy), "Failed to create window.");
}

FierceWindow::~FierceWindow(){
	CHECK_FIERCE(destroyWindow(),"Failed to destroy window.");
}

FIERCE_ERROR FierceWindow::createWindow(LPCWSTR className, LPCWSTR title, EngineSettings* settings, bool dummy) {
	DWORD style=0;
	DWORD exStyle = WS_EX_APPWINDOW;

	RECT r = RECT();
	r.left = 0;
	r.top = 0;

	if (settings->windowMode == WINDOWED || dummy) {
		style = WS_OVERLAPPEDWINDOW;
		r.right = settings->width;
		r.bottom = settings->height;
	}
	else if (settings->windowMode==FULLSCREEN) {
		style = WS_POPUP;
		r.right = GetSystemMetrics(SM_CXSCREEN);
		r.bottom = GetSystemMetrics(SM_CYSCREEN);
		settings->width= GetSystemMetrics(SM_CXSCREEN);
		settings->height= GetSystemMetrics(SM_CYSCREEN);
	}

	if (!AdjustWindowRectEx(&r, style, FALSE, exStyle)) {
		return FE_WINDOW_ERROR;
	}

	windowHandle = CreateWindowEx(
		exStyle,
		className,
		title,
		style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		r.right - r.left, r.bottom - r.top,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (!windowHandle) {
		return FE_WINDOW_ERROR;
	}

	SetProp(windowHandle, L"windowHandle", this);

	return FE_NO_ERROR;
}

FIERCE_ERROR FierceWindow::destroyWindow() {
	if (!DestroyWindow(windowHandle)) {
		return FE_WINDOW_ERROR;
	}
	return FE_NO_ERROR;
}

void FierceWindow::pollEvents() {
	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

void FierceWindow::show() {
	ShowWindow(windowHandle, SW_SHOW);
	UpdateWindow(windowHandle);
}