#include "Geometry.h"

void Geometry2D::addVertex2D(std::vector<float>& vertices,float x,float y){
	vertices.push_back(x);
	vertices.push_back(y);
}

void Geometry2D::addCircleVertices2D(std::vector<float>& vertices, float x, float y,int numPoints,float radius,float angle){
	float da = 0;
	if (angle == 360.0f) {
		da = angle / numPoints;
	}
	else {
		da = angle / (numPoints - 1);
	}

	for (int i = 0; i < numPoints; i++) {
		vertices.push_back(x + radius * sin(M_PI / 180.0f * i * da));
		vertices.push_back(y + radius * cos(M_PI / 180.0f * i * da));
	}
}

void Geometry::addTriangleIndices(std::vector<unsigned int>& indices, int i1, int i2, int i3, bool flip){
	if (flip) {
		indices.push_back(i2);
		indices.push_back(i1);
		indices.push_back(i3);
	}
	else {
		indices.push_back(i1);
		indices.push_back(i2);
		indices.push_back(i3);
	}
}

void Geometry::addQuadIndices(std::vector<unsigned int>& indices, int i1, int i2, int i3, int i4, bool flip){
	if (flip) {
		indices.push_back(i2);
		indices.push_back(i1);
		indices.push_back(i3);

		indices.push_back(i3);
		indices.push_back(i1);
		indices.push_back(i4);
	}
	else {
		indices.push_back(i1);
		indices.push_back(i2);
		indices.push_back(i3);

		indices.push_back(i1);
		indices.push_back(i3);
		indices.push_back(i4);
	}
}

void Geometry::addCircleIndices(std::vector<unsigned int>& indices,int numPoints,float angle,int center,int start, bool flip){
	for (int i = 0; i < numPoints - 1; i++) {
		if (flip) {
			indices.push_back(i + start);
			indices.push_back(center);
			indices.push_back(i + start + 1);
		}
		else {
			indices.push_back(center);
			indices.push_back(i + start);
			indices.push_back(i + start + 1);
		}
	}

	if (angle == 360.0f) {
		if (flip) {
			indices.push_back(start + numPoints - 1);
			indices.push_back(center);
			indices.push_back(start);
		}
		else {
			indices.push_back(center);
			indices.push_back(start + numPoints - 1);
			indices.push_back(start);
		}
	}
}

void Geometry::addCircleRingIndices(std::vector<unsigned int>& indices, int numPoints, float angle, int start1, int start2, bool flip){
	for (int i = 0; i < numPoints - 1; i++) {
		if (flip) {
			//First triangle
			indices.push_back(start2 + i + 1);
			indices.push_back(start1 + i);
			indices.push_back(start1 + i + 1);

			//Second triangle
			indices.push_back(start2 + i);
			indices.push_back(start1 + i);
			indices.push_back(start2 + i + 1);
		}
		else {
			//First triangle
			indices.push_back(start1 + i);
			indices.push_back(start2 + i + 1);
			indices.push_back(start1 + i + 1);

			//Second triangle
			indices.push_back(start1 + i);
			indices.push_back(start2 + i);
			indices.push_back(start2 + i + 1);
		}
	}

	if (angle == 360.0f) {
		if (flip) {
			//First triangle
			indices.push_back(start2);
			indices.push_back(start1 + numPoints - 1);
			indices.push_back(start1);
			
			//Second triangle
			indices.push_back(start2 + numPoints - 1);
			indices.push_back(start1 + numPoints - 1);
			indices.push_back(start2);
		}
		else {
			//First triangle
			indices.push_back(start1 + numPoints - 1);
			indices.push_back(start2);
			indices.push_back(start1);

			//Second triangle
			indices.push_back(start1 + numPoints - 1);
			indices.push_back(start2 + numPoints - 1);
			indices.push_back(start2);
		}
	}
}

void Geometry3D::addVertex3D(std::vector<float>& vertices, float x, float y,float z) {
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

void Geometry3D::addCircleVertices3D(std::vector<float>& vertices, float x, float y,float z, int numPoints, float radius, float angle) {
	float da = 0;
	if (angle == 360.0f) {
		da = angle / numPoints;
	}
	else {
		da = angle / (numPoints - 1);
	}

	for (int i = 0; i < numPoints; i++) {
		vertices.push_back(x + radius * sin(M_PI / 180.0f * i * da));
		vertices.push_back(y + radius * cos(M_PI / 180.0f * i * da));
		vertices.push_back(z);
	}
}