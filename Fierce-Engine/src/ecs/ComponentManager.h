#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/system/logging/Logger.h"
#include "ComponentArray.h"

/* SystemIncludes*/
#include <unordered_map>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
using Entity = int;

class ComponentManager{
public:
	~ComponentManager() {
		if (!m_componentArrays.empty()) {
			Loggers::ECS->warn("The following components have not been unregistered:");
			for (auto& it : m_componentArrays) {
				Loggers::ECS->warn("%s",it.first);
			}
		}
	}

	template<typename T>
	void registerComponent(int maxComponents) {
		const char* typeName = typeid(T).name();

		if (m_componentArrays.find(typeName)!= m_componentArrays.end()) {
			Loggers::ECS->warn("Trying to register component %s more than once.", typeName);
			return;
		}

		m_componentArrays.insert({ typeName, new ComponentArray<T>(maxComponents) });
	}

	template<typename T>
	void unregisterComponent() {
		const char* typeName = typeid(T).name();

		if (m_componentArrays.find(typeName) == m_componentArrays.end()) {
			Loggers::ECS->warn("Trying to unregister component %s, which has never been registered, or already has been unregistered.", typeName);
			return;
		}

		ComponentArray<T>* arr = GetComponentArray<T>();
		delete arr;
		m_componentArrays.erase(typeName);
	}

	template<typename T>
	void addComponent(Entity entity, T component){
		const char* typeName = typeid(T).name();

		if (m_componentArrays.find(typeName) == m_componentArrays.end()) {
			Loggers::ECS->warn("Cannot add component %s, as component has never been registered.", typeName);
			return;
		}

		GetComponentArray<T>()->insertComponent(entity,component);
	}

	template<typename T>
	void removeComponent(Entity entity){
		const char* typeName = typeid(T).name();

		if (m_componentArrays.find(typeName) == m_componentArrays.end()) {
			Loggers::ECS->warn("Cannot remove component %s, as component has never been registered.", typeName);
			return;
		}

		GetComponentArray<T>()->removeComponent(entity);
	}

	template<typename T>
	T& getComponent(Entity entity){
		const char* typeName = typeid(T).name();

		if (m_componentArrays.find(typeName) == m_componentArrays.end()) {
			Loggers::ECS->warn("Cannot get component %s, as component has never been registered.", typeName);
			return T();
		}

		return GetComponentArray<T>()->getComponent(entity);
	}

private:
	std::unordered_map<const char*, IComponentArray*> m_componentArrays{};

	template<typename T>
	ComponentArray<T>* GetComponentArray(){
		const char* typeName = typeid(T).name();

		return (ComponentArray<T>*)(m_componentArrays[typeName]);
	}
};