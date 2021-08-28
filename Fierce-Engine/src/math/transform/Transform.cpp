#include "Transform.h"

Transform2D::Transform2D(){
	m_position = Vector2f(0,0);
	m_scale = Vector2f(1,1);
	m_rotation = 0;
}

Transform2D::Transform2D(Transform2D& transform){
	m_position = Vector2f(transform.getPosition());
	m_scale = Vector2f(transform.getScale());
	m_rotation = transform.getRotation();
}

Transform2D::Transform2D(float x, float y, float scaleX, float scaleY, float rotation) {
	m_position = Vector2f(x, y);
	m_scale = Vector2f(scaleX, scaleY);
	m_rotation = rotation;
}

Transform2D::Transform2D(Vector2f* position, Vector2f* scale, float rotation){
	m_position = Vector2f(*position);
	m_scale = Vector2f(*scale);
	m_rotation = rotation;
}

Transform3D::Transform3D(){
	m_position = Vector3f(0, 0, 0);
	m_scale = Vector3f(1, 1, 1);
	m_rotation = Vector3f(0, 0, 0);
}

Transform3D::Transform3D(Transform3D& transform){
	m_position = Vector3f(transform.getPosition());
	m_scale = Vector3f(transform.getScale());
	m_rotation = Vector3f(transform.getRotation());
}

Transform3D::Transform3D(float x, float y, float z, float scaleX, float scaleY, float scaleZ, float rotationX, float rotationY, float rotationZ){
	m_position = Vector3f(x, y, z);
	m_scale = Vector3f(scaleX, scaleY, scaleZ);
	m_rotation = Vector3f(rotationX, rotationY, rotationZ);
}

Transform3D::Transform3D(Vector3f* position, Vector3f* scale, Vector3f* rotation){
	m_position = Vector3f(*position);
	m_scale = Vector3f(*scale);
	m_rotation = Vector3f(*rotation);
}