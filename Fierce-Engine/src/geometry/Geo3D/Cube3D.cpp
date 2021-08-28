#include "src/geometry/Geometry.h"

void Cube3D::getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings) {
	addVertex3D(vertices, -0.5f, -0.5f,  0.5f);
	addVertex3D(vertices,  0.5f, -0.5f,  0.5f);
	addVertex3D(vertices,  0.5f, -0.5f, -0.5f);
	addVertex3D(vertices, -0.5f, -0.5f, -0.5f);

	addVertex3D(vertices, -0.5f,  0.5f,  0.5f);
	addVertex3D(vertices,  0.5f,  0.5f,  0.5f);
	addVertex3D(vertices,  0.5f,  0.5f, -0.5f);
	addVertex3D(vertices, -0.5f,  0.5f, -0.5f);
}

void Cube3D::getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings) {
	//Bottom
	addQuadIndices(indices, 3, 2, 1, 0,false);

	addQuadIndices(indices, 0, 1, 5, 4, false);
	addQuadIndices(indices, 1, 2, 6, 5, false);
	addQuadIndices(indices, 2, 3, 7, 6, false);
	addQuadIndices(indices, 3, 0, 4, 7, false);

	//Top
	addQuadIndices(indices, 4, 5, 6, 7, false);
}