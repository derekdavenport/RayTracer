/*
 *  Vector3.cpp
 *  Author: Christian Duncan
 *  Modified by: Derek Davenport
 *
 *  Provides basic functionality for a 3-D Vector class
 */

#include "Vector3.hpp"

/**
 * Vector3(Point3& p):
 *    p-(0,0,0) - means just use p.x, etc...
 **/
Vector3::Vector3(const Point3& p) {
	dx = p.x; dy = p.y; dz = p.z;
}

/**
 * Vector3(Point3& p):
 *    Vector is q-p
 **/
Vector3::Vector3(const Point3& p, const Point3& q) {
	dx = q.x - p.x;
	dy = q.y - p.y;
	dz = q.z - p.z;
}

Vector3 Vector3::Reverse() const {
	return Vector3(-dx, -dy, -dz);
}
