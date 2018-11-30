/*
 *  Plane.hpp
 *  RayTracer
 *
 *  Created by Derek Davenport on 11/21/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __PLANE_HPP
#define __PLANE_HPP

//class Sphere;

#include "DrawableObject.hpp"

using namespace std;

class Plane : public DrawableObject
{
    public:
        Plane(const MaterialProperties & _Props) : DrawableObject(_Props) { }
        
        virtual Vector3 getNormal(Point3 & Point) const
        {
            return Vector3(0,0,1);
        }

    //ray passed in as world ray
    //Norm returned as world normal
        float getHit(const Ray & R, Vector3 & Norm)
        {
            float eye[4], invEye[4];
            R.Start.getMatrix(eye);
            matrixMultiply4(tMatrixInv, eye, invEye);
            
            float dir[4], invDir[4];
            R.Direction.getMatrix(dir);
            matrixMultiply4(tMatrixInv, dir, invDir);
            
            Ray Rinv(Point3(invEye[0], invEye[1], invEye[2]), Vector3(invDir[0], invDir[1], invDir[2]));
            
            float denom = Rinv.Direction.dz;
            if(fabs(denom) < 0.0001)
            {
                return 0;
            }
            
            float time = -Rinv.Start.z / denom;
            if(time <= 0.0)
            {
                return 0;
            }
            else
            {
                float t[4] = { 0, 0, 1, 1 };
                float m[4];
                matrixMultiply4(tMatrixInvTrans, t, m);
                Norm.set(m[0], m[1], m[2]);
                Norm.normalize();
                return time;
            }
        }
    
        void draw();
};
#endif