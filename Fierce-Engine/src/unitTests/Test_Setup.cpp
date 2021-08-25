#include "UnitTests.h"

#include "src/system/logging/Logger.h"

Test_Setup::Test_Setup() {
	m_settings.windowMode = HEADLESS;
}

void Test_Setup::init(){
	Loggers::CORE->info("Testing loggers:");
	Loggers::CORE->error("ERROR %i", 102);
	Loggers::CORE->warn("WARN %1.5f", 85.255496464);
	Loggers::CORE->info("INFO %s", "String");

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
	Loggers::CORE->info("Window size: %ix%i",m_settings.width,m_settings.height);
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
	Loggers::CORE->info("API version: %i.%i.%i", m_settings.apiVersionMajor,m_settings.apiVersionMinor,m_settings.apiVersionPatch);
}

void Test_Setup::update(float dt){}

void Test_Setup::render(){}

void Test_Setup::cleanUp(){}