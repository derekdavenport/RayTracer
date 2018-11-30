/*
 *  Camera.cpp
 *  Author: Christian Duncan
 *  Modified by: Derek Davenport
 *
 *  Maintains the position, orientation, and
 *  shape of a particular camera.
 *  Provides functions for manipulating the camera
 *  using such things as yaw, pitch, roll, move.
 */

//#include "utils.h"
#include "Camera.hpp"


/**
 * setModelViewMatrix():
 *    Computes the View Matrix for the 
 *    Camera's given position and orientation.
 **/
void Camera::setModelViewMatrix()
{
   float m[16];
   u.normalize();  // Should not be needed... but safer!
   v.normalize();
   n.normalize();
   Vector3 EyeV(eye.x, eye.y, eye.z);
   m[0] = u.dx; m[4] = u.dy; m[8]  = u.dz; m[12] = -EyeV.dot(u);
   m[1] = v.dx; m[5] = v.dy; m[9]  = v.dz; m[13] = -EyeV.dot(v);
   m[2] = n.dx; m[6] = n.dy; m[10] = n.dz; m[14] = -EyeV.dot(n);
   m[3] = 0;    m[7] = 0;    m[11] = 0;    m[15] = 1;
   
   // Puts this computed matrix as new ModelView Matrix
   cerr << "Camera::setModelViewMatrix(): Need to load the ModelView Matrix!" << endl;
   memcpy(modelViewMatrix, m, 16 * sizeof(float));
   //glMatrixMode(GL_MODELVIEW);
   //glLoadMatrixf(m);
}

/**
 * setProjectionMatrix():
 *    Computes the Projection Matrix for the 
 *    Camera's shape
 **/
void Camera::setProjectionMatrix()
{
    //cerr << "Camera::setProjectionMatrix(): Set your freaking Projection Matrix!!!" << endl;
    float f = 1.0 / tan(angle / 2);
    projectionMatrix[0] = f / aspectRatio; projectionMatrix[4] = 0; projectionMatrix[8]  = 0;                                           projectionMatrix[12] = 0;
    projectionMatrix[1] = 0;               projectionMatrix[5] = f; projectionMatrix[9]  = 0;                                           projectionMatrix[13] = 0,
    projectionMatrix[2] = 0;               projectionMatrix[6] = 0; projectionMatrix[10] = (nearDist + farDist) / (nearDist - farDist); projectionMatrix[14] = (2 * nearDist * farDist) / nearDist - farDist,
    projectionMatrix[3] = 0;               projectionMatrix[7] = 0; projectionMatrix[11] = -1;                                          projectionMatrix[15] = 0;
   //glMatrixMode(GL_PROJECTION);
   //glLoadIdentity();
   //gluPerspective(angle, aspectRatio, nearDist, farDist);
}

/**
* roll():
 *   Roll the camera (rotate the camera CCW about n axis)
 *   See Hearn and Baker, Equation 5-73, page 264
 *   Note, the signs are changed so rotation is CCW 
 *   [Otherwise, OBJECTS are rotated CCW - and not vector axes]
 **/
void Camera::roll(float delta)
{ 
    float c = cos(M_PI / 180 * delta);
    float s = sin(M_PI / 180 * delta);
    Vector3 uorig(u);
    u.set(c * uorig.dx + s * v.dx, c * uorig.dy + s * v.dy, c * uorig.dz + s * v.dz);
    v.set(-s * uorig.dx + c * v.dx, -s * uorig.dy + c * v.dy, -s * uorig.dz + c * v.dz);
}

/**
* pitch():
 *   Pitch the camera (rotate about the u axis)
 **/
void Camera::pitch(float delta)
{ 
    float c = cos(M_PI / 180 * delta);
    float s = sin(M_PI / 180 * delta);
    Vector3 vorig(v);
    v.set(c * vorig.dx + s * n.dx, c * vorig.dy + s * n.dy, c * vorig.dz + s * n.dz);
    n.set(-s * vorig.dx + c * n.dx, -s * vorig.dy + c * n.dy, -s * vorig.dz + c * n.dz);
} 

/**
* yaw():
 *   Yaw the camera (rotate about v axis)
 *     Equivalent to changing the "heading"
 **/
void Camera::yaw(float delta)
{
    float c = cos(M_PI / 180 * delta);
    float s = sin(M_PI / 180 * delta);
    Vector3 uorig(u);
    u.set(c * uorig.dx + s * n.dx, c * uorig.dy + s * n.dy, c * uorig.dz + s * n.dz);
    n.set(-s * uorig.dx + c * n.dx, -s * uorig.dy + c * n.dy, -s * uorig.dz + c * n.dz);
}

void Camera::slide(double du, double dv, double dn)
{
    eye.x += du * u.dx + dv * v.dx + dn * n.dx;
    eye.y += du * u.dy + dv * v.dy + dn * n.dy;
    eye.z += du * u.dz + dv * v.dz + dn * n.dz;
}
   
