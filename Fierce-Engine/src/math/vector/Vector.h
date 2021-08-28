#pragma once

#define VX v[0]
#define VY v[1]
#define VZ v[2]
#define VW v[3]

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "src/utils/FierceStrings.h"

/* SystemIncludes*/
#include <cmath>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class Vector2f {
public:
	Vector2f();
	Vector2f(float value);
	Vector2f(float x, float y);
	Vector2f(const Vector2f& vector);
	Vector2f(float* vector);

public:
	float length();
	float lengthSquared();
	float distance(const Vector2f& vector);
	float distanceSquared(const Vector2f& vector);

	void normalize();

	void print(std::string name);

public:
	float* get() { return v; };
	float getX() { return VX; }
	float getY() { return VY; }
	void setX(float x) { VX = x; }
	void setY(float y) { VY = y; }
	void setTo(const Vector2f& vector) { VX = vector.VX; VY = vector.VY; }
	void setTo(float x,float y) { VX = x; VY = y; }

public:
	Vector2f& operator=(const Vector2f vector);
	bool operator==(const Vector2f& vector);
	bool operator!=(const Vector2f& vector);

	Vector2f& operator+=(const Vector2f& vector);
	Vector2f& operator-=(const Vector2f& vector);
	Vector2f& operator*=(const Vector2f& vector);
	Vector2f& operator/=(const Vector2f& vector);
	Vector2f& operator*=(float factor);
	Vector2f& operator/=(float factor);

private:
	float v[2];
};

Vector2f operator+(const Vector2f& v1, const Vector2f& v2);
Vector2f operator-(const Vector2f& v1, const Vector2f& v2);
Vector2f operator*(const Vector2f& v1, const Vector2f& v2);
Vector2f operator/(const Vector2f& v1, const Vector2f& v2);

Vector2f operator*(const Vector2f& vector, float factor);
Vector2f operator*(float factor, const Vector2f& vector);
Vector2f operator/(const Vector2f& vector, float factor);

class Vector3f {
public:
	Vector3f();
	Vector3f(float value);
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& vector);
	Vector3f(float* vector);

public:
	float length();
	float lengthSquared();
	float distance(const Vector3f& vector);
	float distanceSquared(const Vector3f& vector);

	void normalize();

	void print(std::string name);

public:
	static Vector3f cross(const Vector3f& v1,const Vector3f& v2);

public:
	float* get() { return v; };
	float getX() { return VX; }
	float getY() { return VY; }
	float getZ() { return VZ; }
	void setX(float x) { VX = x; }
	void setY(float y) { VY = y; }
	void setZ(float z) { VZ = z; }
	void setTo(const Vector3f& vector) { VX = vector.VX; VY = vector.VY; VZ = vector.VZ; }
	void setTo(float x, float y, float z) { VX = x; VY = y; VZ = z; }

public:
	Vector3f& operator=(const Vector3f vector);
	bool operator==(const Vector3f& vector);
	bool operator!=(const Vector3f& vector);

	Vector3f& operator+=(const Vector3f& vector);
	Vector3f& operator-=(const Vector3f& vector);
	Vector3f& operator*=(const Vector3f& vector);
	Vector3f& operator/=(const Vector3f& vector);
	Vector3f& operator*=(float factor);
	Vector3f& operator/=(float factor);

private:
	float v[3];
};

Vector3f operator+(const Vector3f& v1, const Vector3f& v2);
Vector3f operator-(const Vector3f& v1, const Vector3f& v2);
Vector3f operator*(const Vector3f& v1, const Vector3f& v2);
Vector3f operator/(const Vector3f& v1, const Vector3f& v2);

Vector3f operator*(const Vector3f& vector, float factor);
Vector3f operator*(float factor, const Vector3f& vector);
Vector3f operator/(const Vector3f& vector, float factor);

class Vector4f {
public:
	Vector4f();
	Vector4f(float value);
	Vector4f(float x, float y, float z, float w);
	Vector4f(const Vector4f& vector);
	Vector4f(float* vector);

public:
	float length();
	float lengthSquared();
	float distance(const Vector4f& vector);
	float distanceSquared(const Vector4f& vector);

	void normalize();

	void print(std::string name);

public:
	float* get() { return v; };
	float getX() { return VX; }
	float getY() { return VY; }
	float getZ() { return VZ; }
	float getW() { return VW; }
	void setX(float x) { VX = x; }
	void setY(float y) { VY = y; }
	void setZ(float z) { VZ = z; }
	void setW(float w) { VW = w; }
	void setTo(const Vector4f& vector) { VX = vector.VX; VY = vector.VY; VZ = vector.VZ; VW = vector.VW;}
	void setTo(float x, float y, float z, float w) { VX = x; VY = y; VZ = z; VW = w; }

public:
	Vector4f& operator=(const Vector4f vector);
	bool operator==(const Vector4f& vector);
	bool operator!=(const Vector4f& vector);

	Vector4f& operator+=(const Vector4f& vector);
	Vector4f& operator-=(const Vector4f& vector);
	Vector4f& operator*=(const Vector4f& vector);
	Vector4f& operator/=(const Vector4f& vector);
	Vector4f& operator*=(float factor);
	Vector4f& operator/=(float factor);

private:
	float v[4];
};

Vector4f operator+(const Vector4f& v1, const Vector4f& v2);
Vector4f operator-(const Vector4f& v1, const Vector4f& v2);
Vector4f operator*(const Vector4f& v1, const Vector4f& v2);
Vector4f operator/(const Vector4f& v1, const Vector4f& v2);

Vector4f operator*(const Vector4f& vector, float factor);
Vector4f operator*(float factor, const Vector4f& vector);
Vector4f operator/(const Vector4f& vector, float factor);