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
	void init(World* world) override;
	void update(World* world,float dt) override;
	void render(World* world) override;
	void cleanUp(World* world) override;
};

class Test_Rendering : public Core {

public:
	Test_Rendering();

	void onKeyPressed(KeyDownEvent* event);

protected:
	void init(World* world) override;
	void update(World* world,float dt) override;
	void render(World* world) override;
	void cleanUp(World* world) override;
};