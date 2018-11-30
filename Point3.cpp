/*
 *  Point3.cpp
 *  Author: Christian Duncan
 *  Modified by: Derek Davenport
 *
 *  Provides basic functionality for a 3-D Point class
 */

#include "Point3.hpp"
#include "Vector3.hpp"

/**
 * lerp:
 *    Compute the linear interpolation between a point and
 *    vector (direction) at time t.
 *
 * NOTE: This is in a separate cpp file because the Vector class
 *       is needed which also includes Point3.h - cyclic dependency!
 **/
Point3 Point3::lerp(const Point3& p, const Vector3& v, float t)
{
  return Point3(p.x + t*v.dx,
		p.y + t*v.dy,
		p.z + t*v.dz);
}
