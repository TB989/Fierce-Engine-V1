#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

/* SystemIncludes*/
#include <Windows.h>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

struct Event {};

//********** Window events ********//
struct WindowRequestHandleEvent : public Event {
	WindowRequestHandleEvent(bool dummy) :m_dummy{ dummy } {}
	bool m_dummy;
};
struct WindowSendHandleEvent : public Event {
	WindowSendHandleEvent(bool dummy, HWND handle) :m_dummy{ dummy }, m_handle{ handle } {}
	bool m_dummy;
	HWND m_handle;
};
struct WindowCloseEvent : public Event {};
struct WindowResizeEvent : public Event {
	WindowResizeEvent(int width, int height) :m_width{ width }, m_height{ height }{}
	int m_width;
	int m_height;
};
//*********************************//

//********** Keyboard events ******//
struct KeyDownEvent : public Event {
	KeyDownEvent(WPARAM key) :m_key{ key } {}
	WPARAM m_key;
};
struct KeyUpEvent : public Event {
	KeyUpEvent(WPARAM key) :m_key{ key } {}
	WPARAM m_key;
};
struct CharEvent : public Event {
	CharEvent(char character) :m_character{ character } {}
	char m_character;
};
//*********************************//

//********** Mouse events *********//
enum MOUSE_BUTTON {
	RIGHT,
	LEFT,
	MIDDLE
};
struct ButtonDownEvent : public Event {
	ButtonDownEvent(MOUSE_BUTTON button, int x, int y) :m_button{ button }, m_x{ x }, m_y{y} {}
	MOUSE_BUTTON m_button;
	int m_x;
	int m_y;
};
struct ButtonUpEvent : public Event {
	ButtonUpEvent(MOUSE_BUTTON button, int x, int y) :m_button{ button }, m_x{ x }, m_y{ y } {}
	MOUSE_BUTTON m_button;
	int m_x;
	int m_y;
};
struct MouseMoveEvent : public Event {
	MouseMoveEvent(int x, int y) : m_x{ x }, m_y{ y } {}
	int m_x;
	int m_y;
};
struct MouseScrollEvent : public Event {
	MouseScrollEvent(int delta,int x, int y) : m_delta{delta},m_x { x }, m_y{ y } {}
	int m_delta;
	int m_x;
	int m_y;
};