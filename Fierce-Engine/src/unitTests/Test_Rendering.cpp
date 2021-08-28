#include "UnitTests.h"

#include "src/system/logging/Logger.h"

Test_Rendering::Test_Rendering() {
	eventSystem->addListener(this, &Test_Rendering::onKeyPressed);
}

void Test_Rendering::init(World* world) {
	
}

void Test_Rendering::update(World* world,float dt) {}

void Test_Rendering::render(World* world) {
	
}

void Test_Rendering::cleanUp(World* world) {}

void Test_Rendering::onKeyPressed(KeyDownEvent* event) {
	if (event->m_key == VK_ESCAPE) {
		eventSystem->postEvent(new WindowCloseEvent());
	}
}