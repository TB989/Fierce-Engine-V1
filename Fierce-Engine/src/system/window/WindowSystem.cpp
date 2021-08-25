#include "WindowSystem.h"

#include "src/core/Core.h"
#include "src/core/Exceptions.h"
#include "src/system/logging/Logger.h"
#include "src/system/event/Event.h"

#include "FierceWindow.h"

LRESULT CALLBACK wndProcFierceWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	FierceWindow* window = static_cast<FierceWindow*>(GetProp(hWnd, L"windowHandle"));
	WindowSystem* windowSystem = static_cast<WindowSystem*>(GetProp(hWnd, L"windowSystem"));

	switch (message) {
	//*** Window ***//
	case WM_CLOSE:
		windowSystem->postEvent(new WindowCloseEvent());
		return 0;
	case WM_SIZE:
		//FIXME: Bug for fullscreen
		if (windowSystem != nullptr) {
			windowSystem->postEvent(new WindowResizeEvent(LOWORD(lParam), HIWORD(lParam)));
		}
		return 0;
	//*** Keyboard ***//
	case WM_KEYDOWN:
		windowSystem->postEvent(new KeyDownEvent(wParam));
		return 0;
	case WM_KEYUP:
		windowSystem->postEvent(new KeyUpEvent(wParam));
		return 0;
	case WM_CHAR:
		windowSystem->postEvent(new CharEvent(wParam));
		return 0;
	//*** Mouse ***//
	case WM_LBUTTONDOWN:
		windowSystem->postEvent(new ButtonDownEvent(MOUSE_BUTTON::LEFT, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		return 0;
	case WM_RBUTTONDOWN:
		windowSystem->postEvent(new ButtonDownEvent(MOUSE_BUTTON::RIGHT, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		return 0;
	case WM_MBUTTONDOWN:
		windowSystem->postEvent(new ButtonDownEvent(MOUSE_BUTTON::MIDDLE, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		return 0;
	case WM_LBUTTONUP:
		windowSystem->postEvent(new ButtonUpEvent(MOUSE_BUTTON::LEFT, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		return 0;
	case WM_RBUTTONUP:
		windowSystem->postEvent(new ButtonUpEvent(MOUSE_BUTTON::RIGHT, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		return 0;
	case WM_MBUTTONUP:
		windowSystem->postEvent(new ButtonUpEvent(MOUSE_BUTTON::MIDDLE, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		return 0;
	case WM_MOUSEMOVE :
		windowSystem->postEvent(new MouseMoveEvent( GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		return 0;
	case WM_MOUSEWHEEL:
		windowSystem->postEvent(new MouseScrollEvent(GET_WHEEL_DELTA_WPARAM(wParam),GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		return 0;
	//****************//
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

LRESULT CALLBACK wndProcFierceDummyWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, message, wParam, lParam);
}

WindowSystem::WindowSystem(Core* app, EngineSettings* settings){
	m_app = app;
	m_settings = settings;
	hInstance= GetModuleHandle(NULL);

	app->eventSystem->addListener(this,&WindowSystem::onHandleRequested);

	CHECK_FIERCE(registerWindowClass(fierceWindowClassName,wndProcFierceWindow), "Failed to register window class for fierce window.");
	CHECK_FIERCE(registerWindowClass(fierceDummyWindowClassName,wndProcFierceDummyWindow), "Failed to register window class for fierce dummy window.");

	m_dummyWindow = new FierceWindow(fierceDummyWindowClassName, L"FierceDummyWindow", m_settings,true);
	m_window= new FierceWindow(fierceWindowClassName, L"FierceWindow", m_settings, false);

	SetProp(m_window->getHandle(), L"windowSystem", this);
}

WindowSystem::~WindowSystem(){
	delete m_dummyWindow;
	delete m_window;
	CHECK_FIERCE(unregisterWindowClass(fierceWindowClassName), "Failed to unregister window class for fierce window.");
	CHECK_FIERCE(unregisterWindowClass(fierceDummyWindowClassName), "Failed to unregister window class for fierce dummy window.");
}

void WindowSystem::onHandleRequested(WindowRequestHandleEvent* evt){
	if (evt->m_dummy) {
		m_app->eventSystem->postEvent(new WindowSendHandleEvent(true,m_dummyWindow->getHandle()));
	}
	else {
		m_app->eventSystem->postEvent(new WindowSendHandleEvent(false, m_window->getHandle()));
	}
}

FIERCE_ERROR WindowSystem::registerWindowClass(LPCWSTR className, WNDPROC wndProc){
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = wndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		return FE_WINDOW_ERROR;
	}
	return FE_NO_ERROR;
}

FIERCE_ERROR WindowSystem::unregisterWindowClass(LPCWSTR className){
	if (!UnregisterClass(className, hInstance)) {
		return FE_WINDOW_ERROR;
	}
	return FE_NO_ERROR;
}