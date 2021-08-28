#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/geometry/Geometry.h"

/* SystemIncludes*/
#include <vector>
#include <map>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class GeometrySettings;

class GeometryLoader{
public:
	void loadGeometry(GeometrySettings& geometrySettings,std::vector<float> &vertices,std::vector<unsigned int> &indices);
	void registerGeometry(GeometryType type, Geometry* geometry);
	void unregisterGeometry(GeometryType type);
private:
	std::map<GeometryType, Geometry*> geometries;
};