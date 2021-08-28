#include "GeometryLoader.h"

void GeometryLoader::loadGeometry(GeometrySettings& geometrySettings, std::vector<float> &vertices, std::vector<unsigned int> &indices){
	Geometry* geom = geometries[geometrySettings.getType()];

	geom->getVertices(vertices, geometrySettings.getNumPoints(), geometrySettings.getAngle(), geometrySettings.getInnerRadius(), geometrySettings.getNumRings());
	geom->getIndices(indices, geometrySettings.getNumPoints(), geometrySettings.getAngle(), geometrySettings.getInnerRadius(), geometrySettings.getNumRings());
}

void GeometryLoader::registerGeometry(GeometryType type, Geometry* geometry){
	geometries[type] = geometry;
}

void GeometryLoader::unregisterGeometry(GeometryType type){
	Geometry* geometry = geometries[type];
	geometries.erase(type);
	delete geometry;
}