/*
 *  Ray.h
 *  RayTracer
 *
 *  Created by Derek Davenport on 11/17/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __RAY_HPP
#define __RAY_HPP

#include "Point3.hpp"
#include "Vector3.hpp"
using namespace std;

class Ray
{
    public:
        Point3 Start;
        Vector3 Direction;
        
        Ray(float px, float py, float pz, float vx, float vy, float vz) : Start(px, py, pz), Direction(vx, vy, vz) { }
        Ray(const Point3& _Start, const Vector3& _Direction) : Start(_Start), Direction(_Direction) { }
        
        Point3 pointAtTime(float t) const
        {
            return Point3(Start.x + Direction.dx * t, Start.y + Direction.dy * t, Start.z + Direction.dz * t);
        }
        
        friend ostream& operator<<(ostream& out, const Ray& r)
        {
            return out << "(" << r.Start.x << "," << r.Start.y << "," << r.Start.z << ")" << " + <" << r.Direction.dx << "," << r.Direction.dy << "," << r.Direction.dz << ">";
        }
};
#endif