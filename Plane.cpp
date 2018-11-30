/*
 *  Plane.cpp
 *  RayTracer
 *
 *  Created by Derek Davenport on 11/21/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "Plane.hpp"

void Plane::draw()
{
    cerr << "Plane::draw(): We don't need to be GL drawing anything!" << endl;
    /*
    DrawableObject::draw();
    glPushMatrix();
    {
        glMultMatrixf(tMatrix);
        //glLoadMatrixf(tMatrix);
        
        glBegin(GL_QUADS);
        {
            glNormal3f(0, 0, 1);
            for(float i = -10; i < 10; i += .1)
            {
                for(float j = -10; j < 10; j += .1)
                {
                    glVertex3f(i, j, 0);
                    glVertex3f(i + .1, j, 0);
                    glVertex3f(i + .1, j + .1, 0);
                    glVertex3f(i, j + .1, 0);
                }
            }
        }
        glEnd();
    }
    glPopMatrix();
     */
}