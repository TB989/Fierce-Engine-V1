#include "World.h"

#include "src/math/transform/Transform.h"
#include "src/system/render/abstract/RenderType.h"

World::World(){
	//Init ECS
	entityManager = new EntityManager(50);
	componentManager = new ComponentManager();
	componentManager->registerComponent<Transform2D>(50);
	componentManager->registerComponent<Transform3D>(50);
	componentManager->registerComponent<RenderType>(50);
	componentManager->registerComponent<GeometrySettings>(50);
	/**componentManager->registerComponent<ComponentMesh>(50);
	componentManager->registerComponent<ComponentMaterialColors>(50);*/

	//Init geometry loader
	loader = new GeometryLoader();
	loader->registerGeometry(GeometryType::RECTANGLE, new Rectangle2D());
	loader->registerGeometry(GeometryType::CIRCLE, new Circle2D());
	loader->registerGeometry(GeometryType::CIRCLE_RING, new CircleRing2D());
	loader->registerGeometry(GeometryType::TRIANGLE, new Triangle2D());
	loader->registerGeometry(GeometryType::PLANE, new Plane3D());
	loader->registerGeometry(GeometryType::CUBE, new Cube3D());
	loader->registerGeometry(GeometryType::CYLINDER, new Cylinder3D());
	loader->registerGeometry(GeometryType::HOLLOW_CYLINDER, new HollowCylinder3D());
	loader->registerGeometry(GeometryType::CONE, new Cone3D());
	loader->registerGeometry(GeometryType::SPHERE, new Sphere3D());
}

World::~World(){
	//Delete geometry loader
	loader->unregisterGeometry(GeometryType::RECTANGLE);
	loader->unregisterGeometry(GeometryType::CIRCLE);
	loader->unregisterGeometry(GeometryType::CIRCLE_RING);
	loader->unregisterGeometry(GeometryType::TRIANGLE);
	loader->unregisterGeometry(GeometryType::PLANE);
	loader->unregisterGeometry(GeometryType::CUBE);
	loader->unregisterGeometry(GeometryType::CYLINDER);
	loader->unregisterGeometry(GeometryType::HOLLOW_CYLINDER);
	loader->unregisterGeometry(GeometryType::CONE);
	loader->unregisterGeometry(GeometryType::SPHERE);
	delete loader;

	//Delete ECS
	componentManager->unregisterComponent<Transform2D>();
	componentManager->unregisterComponent<Transform3D>();
	componentManager->unregisterComponent<RenderType>();
	componentManager->unregisterComponent<GeometrySettings>();
	/**componentManager->unregisterComponent<ComponentMesh>();
	componentManager->unregisterComponent<ComponentMaterialColors>();*/
	delete componentManager;
	delete entityManager;
}