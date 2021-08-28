#include "src/geometry/Geometry.h"

void CircleRing2D::getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings) {
	addCircleVertices2D(vertices, 0.5f, 0.5f, numPoints, innerRadius, angle);
	addCircleVertices2D(vertices, 0.5f, 0.5f, numPoints, 0.5f, angle);
}

void CircleRing2D::getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings) {
	addCircleRingIndices(indices,numPoints,angle,0,numPoints,false);
}