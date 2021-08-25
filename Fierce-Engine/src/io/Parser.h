#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/utils/FierceStrings.h"

/* SystemIncludes*/
#include <map>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class Parser {
public:
	static std::map<std::string, std::string> parsePropertiesFile(std::string filename);
};