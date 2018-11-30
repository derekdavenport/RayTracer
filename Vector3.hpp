/*
 *  Vector3.H
 *  Author: Christian Duncan
 *  Modified by: Derek Davenport
 *
 *  Provides basic functionality for a 3-D Vector class
 */

#ifndef __VECTOR3_HPP
#define __VECTOR3_HPP

class Vector3;

#include <math.h>
#include <iostream>
#include "Point3.hpp"
// #include "utils.h"

using namespace std;

class Vector3 {
public:
	float dx, dy, dz;
	float matrix[4];

	/**
	 * Vector3(...):
	 *    constructors for the Vector3 class
	 **/
	Vector3() : dx(0), dy(0), dz(0) { matrix[0] = dx; matrix[1] = dy; matrix[2] = dz; matrix[3] = 0; }
	Vector3(float initDX, float initDY, float initDZ) : dx(initDX), dy(initDY), dz(initDZ) {
		matrix[0] = dx; matrix[1] = dy; matrix[2] = dz; matrix[3] = 0;
	}

	Vector3(const Point3& p); // p - (0,0,0)

	Vector3(const Point3& p, const Point3& q); // q - p

	Vector3 Reverse() const;

	/**
	 * set(...):
	 *    Set the three vector coordinate values
	 **/
	void set(float _dx, float _dy, float _dz) {
		dx = _dx; dy = _dy; dz = _dz;
		matrix[0] = dx; matrix[1] = dy; matrix[2] = dz;
	}

	void getMatrix(float r[4]) const {
		r[0] = dx;
		r[1] = dy;
		r[2] = dz;
		r[3] = 0;
	}

	/**
	 * dot(Vector3& other):
	 *    Computes this DOT other (dot product)
	 **/
	float dot(const Vector3& other) const { return dot(*this, other); }

	/**
	 * dot(a,b):
	 *    Computes the dot product of a and b
	 **/
	static float dot(const Vector3& a, const Vector3& b) {
		return a.dx * b.dx + a.dy * b.dy + a.dz * b.dz;
	}

	/**
	 * cross(a,b):
	 *    Computes the cross product of a and b
	 **/
	static Vector3 cross(const Vector3& A, const Vector3& B) {
		return Vector3(A.dy * B.dz - A.dz * B.dy,
					   A.dz * B.dx - A.dx * B.dz,
					   A.dx * B.dy - A.dy * B.dx);
	}

	Vector3 cross(const Vector3& B) const {
		return Vector3(dy * B.dz - dz * B.dy,
					   dz * B.dx - dx * B.dz,
					   dx * B.dy - dy * B.dx);
	}

	/**
	 * lerp(a,b,t):
	 *    Computes the lerp of two Vectors at time t
	 **/
	static Vector3 lerp(const Vector3& a, const Vector3& b, float t) {
		Vector3 answer;
		answer.dx = a.dx + t * (b.dx - a.dx);
		answer.dy = a.dy + t * (b.dy - a.dy);
		answer.dz = a.dz + t * (b.dz - a.dz);
		answer.normalize();
		return answer;
	}

	/**
	 * magnitude():
	 *    Returns the magnitude (length) of the vector
	 **/
	float magnitude() {
		return sqrt(dx * dx + dy * dy + dz * dz);
	}

	/**
	 * normalize():
	 *    Normalizes the current vector
	 **/
	void normalize() {
		float invMag = 1.0 / sqrtf(dx * dx + dy * dy + dz * dz); // InvSqrt(dx * dx + dy * dy + dz * dz);
		dx *= invMag;
		dy *= invMag;
		dz *= invMag;
	}

	/**
	 * operator<<:
	 *    Generate a nice (DEBUGGING) display of the vector.
	 **/
	friend ostream& operator<<(ostream& out, const Vector3& vec) {
		return out << "(" << vec.dx << "," << vec.dy << "," << vec.dz << ")";
	}

	/**
	* operator-:
	 *    Compute the vector b-a
	 **/
	friend Vector3 operator-(const Point3& a, Point3& b) {
		return Vector3(b, a);
	}
};
#endif
