#include "UnitTests.h"

#include "src/system/logging/Logger.h"

#include "src/math/transform/Transform.h"
#include "src/system/render/abstract/RenderType.h"

Test_Setup::Test_Setup() {
	m_settings.windowMode = HEADLESS;
}

void TestLoggers() {
	Loggers::CORE->info("Testing loggers:");
	Loggers::CORE->error("ERROR %i", 102);
	Loggers::CORE->warn("WARN %1.5f", 85.255496464);
	Loggers::CORE->info("INFO %s", "String");
}

void TestEngineSettings(EngineSettings m_settings) {
	Loggers::CORE->info("Printing engine settings:");
	switch (m_settings.windowMode) {
	case WINDOWED:
		Loggers::CORE->info("Window mode: WINDOWED");
		break;
	case FULLSCREEN:
		Loggers::CORE->info("Window mode: FULLSCREEN");
		break;
	case HEADLESS:
		Loggers::CORE->info("Window mode: HEADLESS");
		break;
	}
	Loggers::CORE->info("Window size: %ix%i", m_settings.width, m_settings.height);
	switch (m_settings.api) {
	case OPEN_GL:
		Loggers::CORE->info("API: OpenGL");
		break;
	case VULKAN:
		Loggers::CORE->info("API: Vulkan");
		break;
	case DIRECT_X:
		Loggers::CORE->info("API: DirectX");
		break;
	}
	Loggers::CORE->info("API version: %i.%i.%i", m_settings.apiVersionMajor, m_settings.apiVersionMinor, m_settings.apiVersionPatch);
}

void TestECS(World* world) {
	Loggers::CORE->info("Testing ECS:");
	//Create entities
	Entity ent1=world->createEntity();
	Loggers::CORE->info("Created ent1 id=%i",ent1);
	Entity ent2 = world->createEntity();
	Loggers::CORE->info("Created ent2 id=%i", ent2);
	//Add components
	world->addComponent(ent1, Transform2D(1.0f,2.0f,3.0f,4.0f,5.0f));
	Loggers::CORE->info("Added component Transform2D");
	world->addComponent(ent2, Transform3D(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f));
	Loggers::CORE->info("Added component Transform3D");
	//Print components
	Transform2D trafo1 = world->getComponent<Transform2D>(ent1);
	Loggers::CORE->info("Print Transform2D: [%1.3f %1.3f][%1.3f %1.3f][%1.3f]",
		trafo1.getPosition().getX(),
		trafo1.getPosition().getY(), 
		trafo1.getScale().getX(),
		trafo1.getScale().getY(),
		trafo1.getRotation());
	Transform3D trafo2 = world->getComponent<Transform3D>(ent2);
	Loggers::CORE->info("Print Transform3D: [%1.3f %1.3f %1.3f][%1.3f %1.3f %1.3f][%1.3f %1.3f %1.3f]",
		trafo2.getPosition().getX(),
		trafo2.getPosition().getY(),
		trafo2.getPosition().getZ(),
		trafo2.getScale().getX(),
		trafo2.getScale().getY(),
		trafo2.getScale().getZ(),
		trafo2.getRotation().getX(),
		trafo2.getRotation().getY(),
		trafo2.getRotation().getZ());

	//More components
	world->addComponent(ent1, RenderType::GEOMETRY);
	world->addComponent(ent1,GeometrySettings(GeometryType::RECTANGLE,0,0.0f,0.0f,0));
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	world->loadGeometry(world->getComponent<GeometrySettings>(ent1),vertices,indices);

	world->removeComponent<GeometrySettings>(ent1);
	world->removeComponent<RenderType>(ent1);
	world->removeComponent<Transform2D>(ent1);
	world->removeComponent<Transform3D>(ent2);
	world->destroyEntity(ent1);
	world->destroyEntity(ent2);
}

void Test_Setup::init(World* world){
	Loggers::CORE->info("################################################");
	TestLoggers();
	Loggers::CORE->info("################################################");
	TestEngineSettings(m_settings);
	Loggers::CORE->info("################################################");
	TestECS(world);
	Loggers::CORE->info("################################################");
}

void Test_Setup::update(World* world,float dt){}

void Test_Setup::render(World* world){}

void Test_Setup::cleanUp(World* world){}