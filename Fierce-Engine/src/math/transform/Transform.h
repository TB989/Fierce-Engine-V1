#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/math/vector/Vector.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class Transform {};

class Transform2D : Transform {
private:
	Vector2f m_position;
	Vector2f m_scale;
	float m_rotation;
public:
	Transform2D();
	Transform2D(Transform2D& transform);
	Transform2D(float x, float y, float scaleX, float scaleY, float rotation);
	Transform2D(Vector2f* position, Vector2f* scale, float rotation);

	Vector2f getPosition(){ return m_position; }
	Vector2f getScale() { return m_scale; }
	float getRotation() { return m_rotation; }
};

class Transform3D : Transform {
private:
	Vector3f m_position;
	Vector3f m_scale;
	Vector3f m_rotation;
public:
	Transform3D();
	Transform3D(Transform3D& transform);
	Transform3D(float x, float y, float z,float scaleX, float scaleY,float scaleZ, float rotationX,float rotationY,float rotationZ);
	Transform3D(Vector3f* position, Vector3f* scale, Vector3f* rotation);

	Vector3f getPosition() { return m_position; }
	Vector3f getScale() { return m_scale; }
	Vector3f getRotation() { return m_rotation; }
};