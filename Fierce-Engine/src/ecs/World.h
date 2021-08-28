#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/ecs/EntityManager.h"
#include "src/ecs/ComponentManager.h"
#include "src/geometry/GeometryLoader.h"

/* SystemIncludes*/
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
using Entity = int;

class World {
public:
	World();
	~World();

	//ECS
	Entity createEntity() { return entityManager->createEntity(); }
	void destroyEntity(Entity entity) { entityManager->destroyEntity(entity); }

	template<typename T>
	void addComponent(Entity entity, T component) { componentManager->addComponent<T>(entity, component); }

	template<typename T>
	void removeComponent(Entity entity) { componentManager->removeComponent<T>(entity); }

	template<typename T>
	T& getComponent(Entity entity) { return componentManager->getComponent<T>(entity); }

	//Geometry loader
	void loadGeometry(GeometrySettings& geometrySettings, std::vector<float>& vertices, std::vector<unsigned int>& indices) { loader->loadGeometry(geometrySettings, vertices, indices); }

private:
	EntityManager* entityManager;
	ComponentManager* componentManager;

	GeometryLoader* loader;
};