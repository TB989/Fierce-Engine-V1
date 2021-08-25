#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/core/Core.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class Test_Setup : public Core {

public:
	Test_Setup();

protected:
	void init() override;
	void update(float dt) override;
	void render() override;
	void cleanUp() override;
};

class Test_Rendering : public Core {

public:
	Test_Rendering();

protected:
	void init() override;
	void update(float dt) override;
	void render() override;
	void cleanUp() override;
};