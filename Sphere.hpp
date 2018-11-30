/*
 *  Sphere.hpp
 *  RayTracer
 *
 *  Created by Derek Davenport on 11/16/06.
 *  Copyright 2006. All rights reserved.
 *
 */

#ifndef __SPHERE_HPP
#define __SPHERE_HPP

//class Sphere;
#include <algorithm>

#include "DrawableObject.hpp"



using namespace std;

class Sphere : public DrawableObject
{
    public:
        
        Sphere(const MaterialProperties & _Props) : DrawableObject(_Props) { }
        

    
    /***
    *   getHit:
    *        R = ray defined in World space
    *        HitPoint = hit point in Object Space
    *        Norm = normal in World Space  
    ***/
        float getHit(const Ray & R, Vector3 & Norm)
        {
            float eye[4], invEye[4];
            R.Start.getMatrix(eye);
            matrixMultiply4(tMatrixInv, eye, invEye);
            
            float dir[4], invDir[4];
            R.Direction.getMatrix(dir);
            matrixMultiply4(tMatrixInv, dir, invDir);
            
            Ray Rinv(Point3(invEye[0], invEye[1], invEye[2]), Vector3(invDir[0], invDir[1], invDir[2]));
            
            float A, B, C;
            A = pow(invDir[0], 2) + pow(invDir[1], 2) + pow(invDir[2], 2);
            B = invDir[0] * invEye[0] + invDir[1] * invEye[1] + invDir[2] * invEye[2];
            C = pow(invEye[0], 2) + pow(invEye[1], 2) + pow(invEye[2], 2) - 1;
            
            float discriminant = B * B - A * C;
            //cout << "disc: " << discriminant << endl;
            if(discriminant >= 0)
            {
                float hitTime1 = -(B / A) + (sqrt(discriminant) / A);
                float hitTime2 = -(B / A) - (sqrt(discriminant) / A);
				float hitTime = hitTime1 < hitTime2 ? hitTime1 : hitTime2; //min(hitTime1, hitTime2);
                Point3 HitPoint(Rinv.pointAtTime(hitTime));
                float t[4] = { HitPoint.x / 1.73205080757f, HitPoint.y / 1.73205080757f, HitPoint.z / 1.73205080757f, 1 };
                float m[4];
                matrixMultiply4(tMatrixInvTrans, t, m);
                Norm.set(m[0], m[1], m[2]);
                Norm.normalize();
                return hitTime;
            }        
            else
                return 0;
        }
        
        
        void draw();
};
#endif
// Props(MaterialProperties({ 0.23125, 0.23125, 0.23125, 1.0 }, { 0.2775, 0.2775, 0.2775, 1.0 }, { 0.773911, 0.773911, 0.773911, 1.0 }, 89.6))