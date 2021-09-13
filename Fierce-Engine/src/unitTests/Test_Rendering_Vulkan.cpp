#include "UnitTests.h"

#include "src/system/logging/Logger.h"

Test_Rendering_Vulkan::Test_Rendering_Vulkan() {
	m_settings.api = VULKAN;
	m_settings.apiVersionMajor = 1;
	m_settings.apiVersionMinor = 0;
	eventSystem->addListener(this, &Test_Rendering_Vulkan::onKeyPressed);
}

void Test_Rendering_Vulkan::init(World* world) {

}

void Test_Rendering_Vulkan::update(World* world, float dt) {}

void Test_Rendering_Vulkan::render(World* world) {

}

void Test_Rendering_Vulkan::cleanUp(World* world) {}

void Test_Rendering_Vulkan::onKeyPressed(KeyDownEvent* event) {
	if (event->m_key == VK_ESCAPE) {
		eventSystem->postEvent(new WindowCloseEvent());
	}
}