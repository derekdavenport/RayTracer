/*
 *  Sphere.cpp
 *  RayTracer
 *
 *  Created by Derek Davenport on 11/16/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "Sphere.hpp"

void Sphere::draw()
{
    cerr << "Sphere::draw(): We don't need to be GL drawing anything!" << endl;
    /*
    DrawableObject::draw();
    glPushMatrix();
    {
        glMultMatrixf(tMatrix);
        //glLoadMatrixf(tMatrix);
        glutSolidSphere(1, 100, 100);
    }
    glPopMatrix();
     */
}