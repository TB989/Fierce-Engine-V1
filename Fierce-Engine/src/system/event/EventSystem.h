#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

/* SystemIncludes*/
#include <list>
#include <map>
#include <typeindex>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
struct Event;

class HandlerFunctionBase {
public:
	// Call the member function
	void exec(Event* evnt) {
		call(evnt);
	}
private:
	// Implemented by MemberFunctionHandler
	virtual void call(Event* evnt) = 0;
};

template<class T, class EventType>
class MemberFunctionHandler : public HandlerFunctionBase
{
public:
	typedef void (T::* MemberFunction)(EventType*);

	MemberFunctionHandler(T* instance, MemberFunction memberFunction) : instance{ instance }, memberFunction{ memberFunction } {};

	void call(Event* evnt) {
		// Cast event to the correct type and call member function
		(instance->*memberFunction)(static_cast<EventType*>(evnt));
	}
private:
	// Pointer to class instance
	T* instance;

	// Pointer to member function
	MemberFunction memberFunction;
};

typedef std::list<HandlerFunctionBase*> HandlerList;

class EventSystem {
public:
	template<typename EventType>
	void postEvent(EventType* evnt) {
		HandlerList* handlers = listeners[typeid(EventType)];

		if (handlers == nullptr) {
			return;
		}

		for (auto& handler : *handlers) {
			if (handler != nullptr) {
				handler->exec(evnt);
			}
		}
	}

	template<class T, class EventType>
	void addListener(T* instance, void (T::* memberFunction)(EventType*)) {
		HandlerList* handlers = listeners[typeid(EventType)];

		//First time initialization
		if (handlers == nullptr) {
			handlers = new HandlerList();
			listeners[typeid(EventType)] = handlers;
		}

		handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
	}

private:
	std::map<std::type_index, HandlerList*> listeners;
};