#include "Core.h"

#include "src/system/logging/Logger.h"
#include "src/system/window/WindowSystem.h"
#include "src/system/window/FierceWindow.h"
#include "src/system/render/openGL/GL_RenderSystem.h"
#include "src/system/render/vulkan/VK_RenderSystem.h"
#include "src/io/Parser.h"
#include "src/core/Exceptions.h"

Core::Core() {
	//Load settings
	Loggers::CORE->info("Loading engine settings.");
	std::map<std::string, std::string> settings = Parser::parsePropertiesFile("res/Engine.ini");
	if (settings.empty()) {
		Loggers::CORE->warn("Failed to load engine settings, using default.");
	}
	else {
		m_settings.parse(settings);
	}

	//Start event system
	Loggers::CORE->info("Starting event system.");
	eventSystem = new EventSystem();
	eventSystem->addListener(this, &Core::onWindowClosed);

	//Create world
	Loggers::CORE->info("Creating world.");
	world = new World();
}

Core::~Core() {
	
}

void Core::run() {
	coreInit();

	//Setup game loop
	if (m_settings.windowMode != HEADLESS) {
		m_window->show();
		Loggers::CORE->info("Starting game loop.");
		running = true;
	}

	//Start game loop
	while (running) {
		m_window->pollEvents();
		coreUpdate();
		coreRender();
	}

	coreCleanUp();
}

void Core::coreInit() {
	Loggers::CORE->info("Starting engine.");

	if (m_settings.windowMode != HEADLESS) {
		Loggers::CORE->info("Starting window system.");
		windowSystem = new WindowSystem(this, &m_settings);
		m_window = windowSystem->getWindow();

		Loggers::CORE->info("Starting render system.");
		switch (m_settings.api) {
		case OPEN_GL:
			renderSystem = new GL_RenderSystem(this);
			break;
		case VULKAN:
			renderSystem = new VK_RenderSystem(this);
			break;
		case DIRECT_X:
			CHECK_FIERCE(FE_NOT_SUPPORTED_ERROR,"DirectX is not supported yet.");
			break;
		}
	}

	init(world);
}

void Core::coreUpdate() {
	update(world,0.0f);
}

void Core::coreRender() {
	render(world);
}

void Core::coreCleanUp() {
	Loggers::CORE->info("Stopping engine.");

	cleanUp(world);

	if (m_settings.windowMode != HEADLESS) {
		Loggers::CORE->info("Stopping render system.");
		delete renderSystem;

		Loggers::CORE->info("Stopping window system.");
		delete windowSystem;
	}

	Loggers::CORE->info("Deleting world.");
	delete world;

	Loggers::CORE->info("Stopping event system.");
	delete eventSystem;
}

void Core::onWindowClosed(WindowCloseEvent* event) {
	running = false;
}