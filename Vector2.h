#pragma once
#ifndef _VECTOR_2
#define _VECTOR_2

#include <iostream>
#include <cmath>

class Vector2 {
public:
	float X;
	float Y;

	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& otherVec);

	~Vector2();

	//Vector addition
	Vector2 operator+(const Vector2& otherVec);

	Vector2& operator+=(const Vector2& otherVec);

	Vector2 operator+(float s);

	Vector2& operator+=(float s);


	//Vector subtraction
	Vector2 operator-(const Vector2& otherVec);

	Vector2& operator-=(const Vector2& otherVec);

	Vector2 operator-(float s);

	Vector2& operator-=(float s);


	//Vector multiplication
	Vector2 operator*(float s);

	Vector2& operator*=(float s);


	//Vector division
	Vector2 operator/(float s);

	Vector2& operator/=(float s);

	//Useful Vector Operations
	float Length() const;

	float LengthSq() const;

	Vector2& Normalize();

	float Distance(Vector2 otherVec) const;

	static float Dot(Vector2 v1, Vector2 v2);

	static float Cross(Vector2 v1, Vector2 v2);
};


//Vector comperison operators
bool operator<(const Vector2& lhs, const Vector2& rhs);

bool operator==(const Vector2& lhs, const Vector2& rhs);

bool operator!=(const Vector2& lhs, const Vector2& rhs);

bool operator<=(const Vector2& lhs, const Vector2& rhs);

bool operator>(const Vector2& lhs, const Vector2& rhs);

bool operator>=(const Vector2& lhs, const Vector2& rhs);

#endif