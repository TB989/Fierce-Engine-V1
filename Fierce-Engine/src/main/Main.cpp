#include "src/unitTests/UnitTests.h"
#include "src/core/Exceptions.h"
#include "src/system/logging/Logger.h"

int main() {
	try {
		Test_Rendering_Vulkan app;
		app.run();
	}
	catch (const Fierce_Exception& e) {
		Loggers::CORE->error(e.what());
		return EXIT_FAILURE;
	}
	catch (const Win_Exception& e) {
		Loggers::CORE->error(e.what());
		return EXIT_FAILURE;
	}
	catch (const GL_Exception& e) {
		Loggers::CORE->error(e.what());
		return EXIT_FAILURE;
	}
	catch (const VK_Exception& e) {
		Loggers::CORE->error(e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}