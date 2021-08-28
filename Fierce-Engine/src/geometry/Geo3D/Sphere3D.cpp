#include "src/geometry/Geometry.h"

void Sphere3D::getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings) {
	float da = 180.0f / (numRings+1);

	addVertex3D(vertices, 0.0f, 0.0f, -0.5f);
	for (int i = 0;i<numRings;i++) {
		float radius = 0.5f * sin(M_PI / 180.0f * (i + 1) * da);
		float height = -0.5f * cos(M_PI / 180.0f * (i + 1) * da);
		addCircleVertices3D(vertices, 0.0f, 0.0f, height, numPoints, radius, 360.0f);
	}
	addVertex3D(vertices, 0.0f, 0.0f, 0.5f);
}

void Sphere3D::getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings) {
	addCircleIndices(indices, numPoints, angle, 0, 1, false);
	for (int i = 0; i < numRings-1; i++) {
		addCircleRingIndices(indices, numPoints, angle, i * numPoints + 1, (i+1)*numPoints + 1,false);
	}
	addCircleIndices(indices, numPoints, angle, numRings*numPoints + 1, (numRings-1)*numPoints+1, true);
}