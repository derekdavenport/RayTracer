/*
 *  TaperedCylinder.cpp
 *  RayTracer
 *
 *  Created by Derek Davenport on 12/6/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "TaperedCylinder.hpp"

void TaperedCylinder::draw()
{
    cerr << "TaperedCylinder::draw(): We don't need to be GL drawing anything!" << endl;
    /*
    DrawableObject::draw();
    glPushMatrix();
    {
        glMultMatrixf(tMatrix);
        //glLoadMatrixf(tMatrix);
        GLUquadricObj * Qobj = gluNewQuadric();
        gluQuadricDrawStyle(Qobj, GLU_FILL);
        gluCylinder(Qobj, 1.0, smallRadius, 1.0, 100, 100);
        
        gluDisk(Qobj, 0.0, 1.0, 100, 100);
        glTranslatef(0,0,1);
        gluDisk(Qobj, 0.0, smallRadius, 100, 100);
    }
    glPopMatrix();
     */
}