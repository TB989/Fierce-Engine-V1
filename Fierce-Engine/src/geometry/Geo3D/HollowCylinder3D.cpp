#include "src/geometry/Geometry.h"

void HollowCylinder3D::getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings) {
	addCircleVertices3D(vertices, 0.0f, 0.0f, -0.5f, numPoints, innerRadius, angle);
	addCircleVertices3D(vertices, 0.0f, 0.0f, -0.5f, numPoints, 0.5f, angle);
	addCircleVertices3D(vertices, 0.0f, 0.0f, 0.5f, numPoints, innerRadius, angle);
	addCircleVertices3D(vertices, 0.0f, 0.0f, 0.5f, numPoints, 0.5f, angle);
}

void HollowCylinder3D::getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings) {
	addCircleRingIndices(indices, numPoints, angle, 0, numPoints , false);
	addCircleRingIndices(indices, numPoints, angle, 2*numPoints, 3*numPoints, true);
	addCircleRingIndices(indices, numPoints, angle, numPoints, 3*numPoints, false);
	addCircleRingIndices(indices, numPoints, angle, 0, 2*numPoints, true);

	if (angle != 360.0f) {
		addQuadIndices(indices, 0, numPoints, 3*numPoints, 2*numPoints, true);
		addQuadIndices(indices, 2*numPoints-1, numPoints-1, 3*numPoints - 1,4 * numPoints -1, true);
	}
}