#include "src/geometry/Geometry.h"

void Plane3D::getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings) {
	addVertex3D(vertices, -0.5f, 0, -0.5f);
	addVertex3D(vertices, -0.5f, 0,  0.5f);
	addVertex3D(vertices,  0.5f, 0,  0.5f);
	addVertex3D(vertices,  0.5f, 0, -0.5f);
}

void Plane3D::getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings) {
	addQuadIndices(indices,0,1,2,3,false);
}