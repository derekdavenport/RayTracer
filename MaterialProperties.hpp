/*
 *  MaterialProperties.h
 *  RayTracer
 *
 *  Created by Derek Davenport on 11/17/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __MATERIAL_PROPERTIES_HPP
#define __MATERIAL_PROPERTIES_HPP

//class MaterialProperties;

#include <iostream>
//#include <OpenGL/gl.h>

using namespace std;

class MaterialProperties
{
    public:
        float ambient[4];
        float diffuse[4];
        float specular[4];
        float shininess;
        
        MaterialProperties(float _ambientR,  float _ambientG,  float _ambientB,  float _ambientA,
                           float _diffuseR,  float _diffuseG,  float _diffuseB,  float _diffuseA,
                           float _specularR, float _specularG, float _specularB, float _specularA,
                           float _shininess) : shininess(_shininess)
        {
            ambient[0] = _ambientR, ambient[1] = _ambientG, ambient[2] = _ambientB, ambient[3] = _ambientA;
            diffuse[0] = _diffuseR, diffuse[1] = _diffuseG, diffuse[2] = _diffuseB, diffuse[3] = _diffuseA;
            specular[0] = _specularR, specular[1] = _specularG, specular[2] = _specularB, specular[3] = _specularA;
        }
};
#endif