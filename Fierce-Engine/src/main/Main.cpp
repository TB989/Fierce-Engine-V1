#include "src/unitTests/UnitTests.h"
#include "src/core/Exceptions.h"
#include "src/system/logging/Logger.h"

int main() {
	try {
		Test_Setup app;
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

	return EXIT_SUCCESS;
}