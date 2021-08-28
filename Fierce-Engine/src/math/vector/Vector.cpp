#include "Vector.h"

#include "src/system/logging/Logger.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector2f::Vector2f() {
	VX = 0.0f;
	VY = 0.0f;
}

Vector2f::Vector2f(float value) {
	VX = value;
	VY = value;
}

Vector2f::Vector2f(float x, float y) {
	VX = x;
	VY = y;
}

Vector2f::Vector2f(const Vector2f& vector){
	VX = vector.VX;
	VY = vector.VY;
}

Vector2f::Vector2f(float* vector){
	for (int i = 0; i < 2; i++) {
		v[i] = vector[i];
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Vector2f::length() {
	return std::sqrtf(VX * VX + VY * VY);
}

float Vector2f::lengthSquared(){
	return VX * VX + VY * VY;
}

float Vector2f::distance(const Vector2f& vector){
	return std::sqrtf((VX - vector.VX)*(VX - vector.VX) + (VY - vector.VY)*(VY - vector.VY));
}

float Vector2f::distanceSquared(const Vector2f& vector){
	return (VX - vector.VX) * (VX - vector.VX) + (VY - vector.VY) * (VY - vector.VY);
}

void Vector2f::normalize() {
	float l = length();
	VX = VX / l;
	VY = VY / l;
}

void Vector2f::print(std::string name){
	Loggers::MATH->info("[Vector %s]:", name.c_str());
	Loggers::MATH->info("%1.3f %1.3f",VX,VY);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector2f& Vector2f::operator=(const Vector2f vector) {
	if (this == &vector) {
		return *this;
	}

	for (int i = 0; i < 2; i++) {
		v[i] = vector.v[i];
	}

	return *this;
}

bool Vector2f::operator==(const Vector2f& vector) {
	return
		VX == vector.VX &&
		VY == vector.VY;
}

bool Vector2f::operator!=(const Vector2f& vector) {
	return !(*this == vector);
}

Vector2f& Vector2f::operator+=(const Vector2f& vector) {
	for (int i = 0; i < 2; i++) {
		v[i] += vector.v[i];
	}
	return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& vector) {
	for (int i = 0; i < 2; i++) {
		v[i] -= vector.v[i];
	}
	return *this;
}

Vector2f& Vector2f::operator*=(const Vector2f& vector) {
	for (int i = 0; i < 2; i++) {
		v[i] *= vector.v[i];
	}
	return *this;
}

Vector2f& Vector2f::operator/=(const Vector2f& vector) {
	for (int i = 0; i < 2; i++) {
		v[i] /= vector.v[i];
	}
	return *this;
}

Vector2f& Vector2f::operator*=(float factor) {
	for (int i = 0; i < 2; i++) {
		v[i] *= factor;
	}
	return *this;
}

Vector2f& Vector2f::operator/=(float factor) {
	for (int i = 0; i < 2; i++) {
		v[i] /= factor;
	}
	return *this;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector2f operator+(const Vector2f& v1, const Vector2f& v2) {
	Vector2f temp(v1);
	return (temp += v2);
}

Vector2f operator-(const Vector2f& v1, const Vector2f& v2) {
	Vector2f temp(v1);
	return (temp -= v2);
}

Vector2f operator*(const Vector2f& v1, const Vector2f& v2) {
	Vector2f temp(v1);
	return (temp *= v2);
}

Vector2f operator/(const Vector2f& v1, const Vector2f& v2) {
	Vector2f temp(v1);
	return (temp /= v2);
}

Vector2f operator*(const Vector2f& vector, float factor) {
	Vector2f temp(vector);
	return (temp *= factor);
}

Vector2f operator*(float factor, const Vector2f& vector) {
	Vector2f temp(vector);
	return (temp *= factor);
}

Vector2f operator/(const Vector2f& vector, float factor) {
	Vector2f temp(vector);
	return (temp /= factor);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector3f::Vector3f() {
	VX = 0.0f;
	VY = 0.0f;
	VZ = 0.0f;
}

Vector3f::Vector3f(float value) {
	VX = value;
	VY = value;
	VZ = value;
}

Vector3f::Vector3f(float x, float y, float z) {
	VX = x;
	VY = y;
	VZ = z;
}

Vector3f::Vector3f(const Vector3f& vector){
	VX = vector.VX;
	VY = vector.VY;
	VZ = vector.VZ;
}

Vector3f::Vector3f(float* vector){
	for (int i = 0; i < 3; i++) {
		v[i] = vector[i];
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Vector3f::length() {
	return std::sqrtf(VX * VX + VY * VY + VZ * VZ);
}

float Vector3f::lengthSquared(){
	return VX * VX + VY * VY + VZ * VZ;
}

float Vector3f::distance(const Vector3f& vector){
	return std::sqrtf((VX - vector.VX) * (VX - vector.VX) + (VY - vector.VY) * (VY - vector.VY)+ (VZ - vector.VZ) * (VZ - vector.VZ));
}

float Vector3f::distanceSquared(const Vector3f& vector){
	return (VX - vector.VX) * (VX - vector.VX) + (VY - vector.VY) * (VY - vector.VY) + (VZ - vector.VZ) * (VZ - vector.VZ);
}

void Vector3f::normalize() {
	float l = length();
	VX = VX / l;
	VY = VY / l;
	VZ = VZ / l;
}

void Vector3f::print(std::string name){
	Loggers::MATH->info("[Vector %s]:", name.c_str());
	Loggers::MATH->info("%1.3f %1.3f %1.3f", VX, VY, VZ);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector3f Vector3f::cross(const Vector3f& v1, const Vector3f& v2){
	return Vector3f(
		v1.VY * v2.VZ - v1.VZ * v2.VY,
		v1.VZ * v2.VX - v1.VX * v2.VZ,
		v1.VX * v2.VY - v1.VY * v2.VX
		);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector3f& Vector3f::operator=(const Vector3f vector) {
	if (this == &vector) {
		return *this;
	}

	for (int i = 0; i < 3; i++) {
		v[i] = vector.v[i];
	}

	return *this;
}

bool Vector3f::operator==(const Vector3f& vector) {
	return
		VX == vector.VX &&
		VY == vector.VY &&
		VZ == vector.VZ;
}

bool Vector3f::operator!=(const Vector3f& vector) {
	return !(*this == vector);
}

Vector3f& Vector3f::operator+=(const Vector3f& vector) {
	for (int i = 0; i < 3; i++) {
		v[i] += vector.v[i];
	}
	return *this;
}

Vector3f& Vector3f::operator-=(const Vector3f& vector) {
	for (int i = 0; i < 3; i++) {
		v[i] -= vector.v[i];
	}
	return *this;
}

Vector3f& Vector3f::operator*=(const Vector3f& vector) {
	for (int i = 0; i < 3; i++) {
		v[i] *= vector.v[i];
	}
	return *this;
}

Vector3f& Vector3f::operator/=(const Vector3f& vector) {
	for (int i = 0; i < 3; i++) {
		v[i] /= vector.v[i];
	}
	return *this;
}

Vector3f& Vector3f::operator*=(float factor) {
	for (int i = 0; i < 3; i++) {
		v[i] *= factor;
	}
	return *this;
}

Vector3f& Vector3f::operator/=(float factor) {
	for (int i = 0; i < 3; i++) {
		v[i] /= factor;
	}
	return *this;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector3f operator+(const Vector3f& v1, const Vector3f& v2) {
	Vector3f temp(v1);
	return (temp += v2);
}

Vector3f operator-(const Vector3f& v1, const Vector3f& v2) {
	Vector3f temp(v1);
	return (temp -= v2);
}

Vector3f operator*(const Vector3f& v1, const Vector3f& v2) {
	Vector3f temp(v1);
	return (temp *= v2);
}

Vector3f operator/(const Vector3f& v1, const Vector3f& v2) {
	Vector3f temp(v1);
	return (temp /= v2);
}

Vector3f operator*(const Vector3f& vector, float factor) {
	Vector3f temp(vector);
	return (temp *= factor);
}

Vector3f operator*(float factor, const Vector3f& vector) {
	Vector3f temp(vector);
	return (temp *= factor);
}

Vector3f operator/(const Vector3f& vector, float factor) {
	Vector3f temp(vector);
	return (temp /= factor);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector4f::Vector4f() {
	VX = 0.0f;
	VY = 0.0f;
	VZ = 0.0f;
	VW = 0.0f;
}

Vector4f::Vector4f(float value) {
	VX = value;
	VY = value;
	VZ = value;
	VW = value;
}

Vector4f::Vector4f(float x, float y, float z, float w) {
	VX = x;
	VY = y;
	VZ = z;
	VW = w;
}

Vector4f::Vector4f(const Vector4f& vector){
	VX = vector.VX;
	VY = vector.VY;
	VZ = vector.VZ;
	VW = vector.VW;
}

Vector4f::Vector4f(float* vector){
	for (int i = 0; i < 4; i++) {
		v[i] = vector[i];
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Vector4f::length() {
	return std::sqrtf(VX * VX + VY * VY + VZ * VZ + VW * VW);
}

float Vector4f::lengthSquared(){
	return VX * VX + VY * VY + VZ * VZ + VW * VW;
}

float Vector4f::distance(const Vector4f& vector){
	return std::sqrtf((VX - vector.VX) * (VX - vector.VX) + (VY - vector.VY) * (VY - vector.VY) + (VZ - vector.VZ) * (VZ - vector.VZ) + (VW - vector.VW) * (VW - vector.VW));
}

float Vector4f::distanceSquared(const Vector4f& vector){
	return (VX - vector.VX) * (VX - vector.VX) + (VY - vector.VY) * (VY - vector.VY) + (VZ - vector.VZ) * (VZ - vector.VZ) + (VW - vector.VW) * (VW - vector.VW);
}

void Vector4f::normalize() {
	float l = length();
	VX = VX / l;
	VY = VY / l;
	VZ = VZ / l;
	VW = VW / l;
}

void Vector4f::print(std::string name){
	Loggers::MATH->info("[Vector %s]:", name.c_str());
	Loggers::MATH->info("%1.3f %1.3f %1.3f %1.3f", VX, VY, VZ, VW);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector4f& Vector4f::operator=(const Vector4f vector) {
	if (this == &vector) {
		return *this;
	}

	for (int i = 0; i < 4; i++) {
		v[i] = vector.v[i];
	}

	return *this;
}

bool Vector4f::operator==(const Vector4f& vector) {
	return
		VX == vector.VX &&
		VY == vector.VY &&
		VZ == vector.VZ &&
		VW == vector.VW;
}

bool Vector4f::operator!=(const Vector4f& vector) {
	return !(*this == vector);
}

Vector4f& Vector4f::operator+=(const Vector4f& vector) {
	for (int i = 0; i < 4; i++) {
		v[i] += vector.v[i];
	}
	return *this;
}

Vector4f& Vector4f::operator-=(const Vector4f& vector) {
	for (int i = 0; i < 4; i++) {
		v[i] -= vector.v[i];
	}
	return *this;
}

Vector4f& Vector4f::operator*=(const Vector4f& vector) {
	for (int i = 0; i < 4; i++) {
		v[i] *= vector.v[i];
	}
	return *this;
}

Vector4f& Vector4f::operator/=(const Vector4f& vector) {
	for (int i = 0; i < 4; i++) {
		v[i] /= vector.v[i];
	}
	return *this;
}

Vector4f& Vector4f::operator*=(float factor) {
	for (int i = 0; i < 4; i++) {
		v[i] *= factor;
	}
	return *this;
}

Vector4f& Vector4f::operator/=(float factor) {
	for (int i = 0; i < 4; i++) {
		v[i] /= factor;
	}
	return *this;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector4f operator+(const Vector4f& v1, const Vector4f& v2) {
	Vector4f temp(v1);
	return (temp += v2);
}

Vector4f operator-(const Vector4f& v1, const Vector4f& v2) {
	Vector4f temp(v1);
	return (temp -= v2);
}

Vector4f operator*(const Vector4f& v1, const Vector4f& v2) {
	Vector4f temp(v1);
	return (temp *= v2);
}

Vector4f operator/(const Vector4f& v1, const Vector4f& v2) {
	Vector4f temp(v1);
	return (temp /= v2);
}

Vector4f operator*(const Vector4f& vector, float factor) {
	Vector4f temp(vector);
	return (temp *= factor);
}

Vector4f operator*(float factor, const Vector4f& vector) {
	Vector4f temp(vector);
	return (temp *= factor);
}

Vector4f operator/(const Vector4f& vector, float factor) {
	Vector4f temp(vector);
	return (temp /= factor);
}