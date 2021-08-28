#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/system/logging/Logger.h"

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
using Index = int;

class IComponentArray{};

template<typename T>
class ComponentArray : public IComponentArray {
public:
	ComponentArray(int maxComponents) {
		m_maxComponents = maxComponents;
		components = new T[maxComponents];
	}

	~ComponentArray() {
		if (pointer != 0) {
			Loggers::ECS->warn("%d components have not been removed.", pointer);
		}

		delete[] components;
	}

	void insertComponent(Entity entity, T component){
		if (entityToIndexMap.find(entity)!= entityToIndexMap.end()) {
			Loggers::ECS->warn("Trying to insert component more than once for entity %i.",entity);
			return;
		}

		if (pointer > m_maxComponents - 1) {
			Loggers::ECS->warn("Cannot add component, component array is full.");
			return;
		}

		Index newIndex = pointer;
		entityToIndexMap[entity] = newIndex;
		indexToEntityMap[newIndex] = entity;
		components[newIndex] = component;
		pointer++;
	}

	void removeComponent(Entity entity){
		if (entityToIndexMap.find(entity) == entityToIndexMap.end()) {
			Loggers::ECS->warn("Trying to remove nonexistent component for entity %i.", entity);
			return;
		}

		if (pointer < 1) {
			Loggers::ECS->warn("Cannot remove component for entity %i.",entity);
			return;
		}

		Index indexOfRemovedEntity = entityToIndexMap[entity];
		Index indexOfLastElement = pointer - 1;
		components[indexOfRemovedEntity] = components[indexOfLastElement];

		Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
		entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		entityToIndexMap.erase(entity);
		indexToEntityMap.erase(indexOfLastElement);

		pointer--;
	}

	T& getComponent(Entity entity){
		if (entityToIndexMap.find(entity) == entityToIndexMap.end()) {
			Loggers::ECS->warn("Component does not exist for entity %i.", entity);
			return T();
		}

		return components[entityToIndexMap[entity]];
	}
private:
	int m_maxComponents;

	T* components;
	int pointer = 0;
	std::unordered_map<Entity, Index> entityToIndexMap{};
	std::unordered_map<Index, Entity> indexToEntityMap{};
};