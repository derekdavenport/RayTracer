/*
 *  Point3.H
 *  Author: Christian Duncan
 *  Modified by: Derek Davenport
 *
 *  Provides basic functionality for a 3-D Point class
 */

#ifndef __POINT3_HPP
#define __POINT3_HPP

class Point3;

#include <iostream>
//#include <GLUT/glut.h>
#include "Vector3.hpp"

using namespace std;

class Point3 {
public:
	float x, y, z;

	/**
	 * Point3():
	 *    constructors for the Point3 class
	 **/
	Point3() : x(0), y(0), z(0) {}
	Point3(float _x, float _y, float _z = 0) : x(_x), y(_y), z(_z) {}

	void set(Point3 P) {
		x = P.x;
		y = P.y;
		z = P.z;
	}

	void getMatrix(float r[4]) const {
		r[0] = x;
		r[1] = y;
		r[2] = z;
		r[3] = 1;
	}

	/**
	 * lerp:
	 *    Compute the linear interpolation between two points (p and q)
	 *    at time t.
	 **/
	static Point3 lerp(const Point3& p, const Point3& q, float t) {
		return Point3(p.x + t * (q.x - p.x), p.y + t * (q.y - p.y), p.z + t * (q.z - p.z));
	}

	/**
	 * lerp:
	 *    Compute the linear interpolation between a point and
	 *    vector (direction) at time t.
	 **/
	static Point3 lerp(const Point3& p, const Vector3& q, float t);

	/**
	 * render:
	 *    make the OpenGL call to generate this vertex
	 **/
	 //void render() { glVertex3f(x, y, z); }

	 /**
	  * operator<<:
	  *    Generate a nice (DEBUGGING) display of the point.
	  **/
	friend ostream& operator<<(ostream& out, const Point3& p) {
		return out << "(" << p.x << "," << p.y << "," << p.z << ")";
	}
};
#endif
