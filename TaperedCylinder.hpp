/*
 *  TaperedCylinder.hpp
 *  RayTracer
 *
 *  Created by Derek Davenport on 12/6/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __TAPERED_CYLINDER_HPP
#define __TAPERED_CYLINDER_HPP
#define WALL 0
#define BASE 1
#define CAP 2

//class TaperedCylinder;

#include "DrawableObject.hpp"

using namespace std;

class TaperedCylinder : public DrawableObject
{
public:
    float smallRadius;
    TaperedCylinder(const MaterialProperties & _Props) : DrawableObject(_Props), smallRadius(1) { }
    TaperedCylinder(const MaterialProperties & _Props, float _smallRadius) : DrawableObject(_Props), smallRadius(_smallRadius) { }
    
    
    
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
        
        float sm = smallRadius - 1;
        float d = sm * invDir[2];
        float f = sm * invEye[2] + 1;
        
        float A, B, C;
        A = pow(invDir[0], 2) + pow(invDir[1], 2) - pow(d, 2);
        B = invDir[0] * invEye[0] + invDir[1] * invEye[1] - f * d;
        C = pow(invEye[0], 2) + pow(invEye[1], 2) - pow(f, 2);
        
        float discriminant = B * B - A * C;
        float hitTime = 0.0;
        int surface = -1;
        if(discriminant > 0.0)
        {
            float discRoot = sqrt(discriminant);
            float hitTime1 = (-B - discRoot) / A;
            //float hitTime2 = (-B + discRoot) / A;
            float zHit = invEye[2] + invDir[2] * hitTime1; //z component of ray
            if(hitTime1 > 0.00001 && zHit <= 1.0 && zHit >= 0.0)
            {
                surface = WALL;
                hitTime = hitTime1;
            }
            /* // we don't need the second hit really
             zHit = invEye[2] + invDir[2] * hitTime2;
            if(hitTime2 > 0.00001 && zHit <= 1.0 && zHit >= 0.0)
            {
                hitTime = hitTime2;
            }
            */
        }
        
        float hitTimeB = -invEye[2] / invDir[2]; //-genRay.start.z/genRay.dir.z; //hit time at z = 0 plane
        //cout << wall << ": " << hitTime << ", " << hitTimeB << "; within: " << (pow(invEye[0] + invDir[0] * hitTimeB, 2) + pow(invEye[1] + invDir[1] * hitTimeB, 2)) << endl;
        if(hitTimeB > 0.00001 && (pow(invEye[0] + invDir[0] * hitTimeB, 2) + pow(invEye[1] + invDir[1] * hitTimeB, 2)) < 1.0) //within disc of base
        {
            if(surface < 0 || (hitTimeB < hitTime))
            {
                hitTime = hitTimeB;
                surface = BASE;
            }
        }
        
        float hitTimeC = (1 - invEye[2]) / invDir[2]; //for the cap
        if(hitTimeC > 0.00001 && (pow(invEye[0] + invDir[0] * hitTimeC, 2) + pow(invEye[1] + invDir[1] * hitTimeC, 2)) < pow(smallRadius, 2))
        {
            if(surface < 0 || (hitTimeC < hitTime))
            {
                hitTime = hitTimeC;
                surface = CAP;
            }
        }
        
        if(hitTime > 0.0)
        {
            Point3 HitPoint(Rinv.pointAtTime(hitTime));
            //P0.x, P0.y, -sm * (1 + sm * P0.z)
            float t[4] = { 0, 0, -1, 0 };
            if(surface == WALL)
            {
                t[0] = HitPoint.x;
                t[1] = HitPoint.y;
                t[2] = -sm * (1 + sm * HitPoint.z);
            }
            else if(surface == CAP)
            {
                t[2] = 1;
            }
            float m[4];
            matrixMultiply4(tMatrixInvTrans, t, m);
            Norm.set(m[0], m[1], m[2]);
            Norm.normalize();
        }
        
        return hitTime;
}


void draw();
};
#endif
// Props(MaterialProperties({ 0.23125, 0.23125, 0.23125, 1.0 }, { 0.2775, 0.2775, 0.2775, 1.0 }, { 0.773911, 0.773911, 0.773911, 1.0 }, 89.6))