#include "UnitTests.h"

#include "src/system/logging/Logger.h"

Test_Rendering_OpenGL::Test_Rendering_OpenGL() {
	m_settings.api = OPEN_GL;
	m_settings.apiVersionMajor = 4;
	m_settings.apiVersionMinor = 3;
	eventSystem->addListener(this, &Test_Rendering_OpenGL::onKeyPressed);
}

void Test_Rendering_OpenGL::init(World* world) {
	
}

void Test_Rendering_OpenGL::update(World* world,float dt) {}

void Test_Rendering_OpenGL::render(World* world) {
	
}

void Test_Rendering_OpenGL::cleanUp(World* world) {}

void Test_Rendering_OpenGL::onKeyPressed(KeyDownEvent* event) {
	if (event->m_key == VK_ESCAPE) {
		eventSystem->postEvent(new WindowCloseEvent());
	}
}