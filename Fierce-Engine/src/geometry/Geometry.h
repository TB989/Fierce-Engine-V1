#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

/* SystemIncludes*/
#include <vector>

#include <math.h>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

enum GeometryType {
	RECTANGLE,
	CIRCLE,
	CIRCLE_RING,
	TRIANGLE,

	PLANE,
	CUBE,
	CYLINDER,
	HOLLOW_CYLINDER,
	CONE,
	SPHERE
};

class GeometrySettings{
public:
	GeometrySettings(GeometryType type, int numPoints, float angle, float innerRadius, int numRings) {
		m_type = type;
		m_numPoints = numPoints;
		m_angle = angle;
		m_innerRadius = innerRadius;
		m_numRings = numRings;
	}

	GeometrySettings() {
		m_type = GeometryType::RECTANGLE;
		m_numPoints = 0;
		m_angle = 0;
		m_innerRadius = 0;
		m_numRings = 0;
	}

	GeometryType getType() { return m_type; }
	int getNumPoints() { return m_numPoints; }
	float getAngle() { return m_angle; }
	float getInnerRadius() { return m_innerRadius; }
	float getNumRings() { return m_numRings; }
private:
	GeometryType m_type;
	int m_numPoints;
	float m_angle;
	float m_innerRadius;
	int m_numRings;
};

class Geometry {
public:
	virtual void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius,int numRings) = 0;
	virtual void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius,int numRings) = 0;
protected:
	void addTriangleIndices(std::vector<unsigned int>& indices, int i1, int i2, int i3,bool flip);
	void addQuadIndices(std::vector<unsigned int>& indices, int i1, int i2, int i3, int i4, bool flip);
	void addCircleIndices(std::vector<unsigned int>& indices, int numPoints, float angle, int center, int start, bool flip);
	void addCircleRingIndices(std::vector<unsigned int>& indices, int numPoints, float angle, int start1, int start2, bool flip);
};

class Geometry2D:public Geometry{
protected:
	void addVertex2D(std::vector<float>& vertices, float x, float y);
	void addCircleVertices2D(std::vector<float>& vertices, float x, float y, int numPoints, float radius, float angle);
};

class Rectangle2D :public Geometry2D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings);
};

class Circle2D :public Geometry2D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings);
};

class CircleRing2D :public Geometry2D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings);
};

class Triangle2D :public Geometry2D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings);
};

class Geometry3D :public Geometry {
protected:
	void addVertex3D(std::vector<float>& vertices, float x, float y,float z);
	void addCircleVertices3D(std::vector<float>& vertices, float x, float y,float z, int numPoints, float radius, float angle);
};

class Plane3D :public Geometry3D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings);
};

class Cube3D :public Geometry3D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings);
};

class Cylinder3D :public Geometry3D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings);
};

class HollowCylinder3D :public Geometry3D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings);
};

class Cone3D :public Geometry3D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings);
};

class Sphere3D :public Geometry3D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings);
};