/*
 *  Light.h
 *  RayTracer
 *
 *  Created by Derek Davenport on 11/19/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __LIGHT_HPP
#define __LIGHT_HPP

//#include <GLUT/glut.h>
#include "Point3.hpp"

class Light
{
    public:
        int num;
        float ambient[4];
        float diffuse[4];
        float specular[4];
        float f;
        Point3 Position;
    
        Light(int _num, 
              float _ambientR,  float _ambientG,  float _ambientB,  float _ambientA,
              float _diffuseR,  float _diffuseG,  float _diffuseB,  float _diffuseA,
              float _specularR, float _specularG, float _specularB, float _specularA,
              float _f, Point3 _Position) : num(_num), f(_f), Position(_Position)
        {
            ambient[0] = _ambientR, ambient[1] = _ambientG, ambient[2] = _ambientB, ambient[3] = _ambientA;
            diffuse[0] = _diffuseR, diffuse[1] = _diffuseG, diffuse[2] = _diffuseB, diffuse[3] = _diffuseA;
            specular[0] = _specularR, specular[1] = _specularG, specular[2] = _specularB, specular[3] = _specularA;
        }
        /*
        void place()
        {
            float r[4];
            Position.getMatrix(r);
            glLightfv(num, GL_POSITION, r);
            glLightfv(num, GL_AMBIENT,  ambient);
            glLightfv(num, GL_DIFFUSE,  diffuse);
            glLightfv(num, GL_SPECULAR, specular);
            
            glEnable(num);
            
            glDisable(GL_LIGHTING);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            {
                glTranslatef(Position.x, Position.y, Position.z);
                glColor3f(specular[0], specular[1], specular[2]);
                glutSolidSphere(0.5,10,10);
            }
            glPopMatrix();
            glEnable(GL_LIGHTING);
        }
         */
};
#endif