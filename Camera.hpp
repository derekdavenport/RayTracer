/*
 *  Camera.H
 *  Author: Christian Duncan
 *  Modified by: Derek Davenport
 *
 *  Maintains the position, orientation, and
 *  shape of a particular camera.
 *  Provides functions for manipulating the camera
 *  using such things as yaw, pitch, roll, move.
 */

#ifndef __CAMERA_HPP
#define __CAMERA_HPP

class Camera;

#include <iostream>
//#include <GLUT/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Point3.hpp"
#include "Vector3.hpp"
//#include "utils.h"


using namespace std;

class Camera {
private:
	void setModelViewMatrix();  // Helper function to set MV Matrix in OpenGL
	void setProjectionMatrix(); // .. to set Proj. Matrix in OpenGL

public:
	// Position, Orientation, and Lense Shape of Camera
	Point3 eye;            // Location of camera
	Vector3 u, v, n;       // Camera coordinate system
	float angle;           // Camera's angle
	float aspectRatio;     // Aspect ratio of camera window
	float nearDist;        //    Near clipping plane distance
	float farDist;         //    Far clipping plane distance
	float H, W;
	float modelViewMatrix[16], projectionMatrix[16];

	void roll(float delta);
	void pitch(float delta);
	void yaw(float delta);
	void slide(double du, double dv, double dn);

	/**
	 * Camera():
	 *    Constructor for the Camera class
	 *    Sets eye, orientation, etc to default values
	 **/
	Camera() : eye(0, 0, 0), u(1, 0, 0), v(0, 1, 0), n(0, 0, 1), angle(45), aspectRatio(1), nearDist(1), farDist(500), H(nearDist * tan(45 * M_PI / 360)), W(H * aspectRatio) {}

	/**
	 * prepareCamera():
	 *    Prepares the camera for OpenGL calls.
	 *    This sets the Project Matrix to Camera's shape
	 *    and the MV Matrix to appropriate one given values u,v,n, and eye
	 **/
	void prepare() {
		setProjectionMatrix();
		setModelViewMatrix();
	}

	/**
	 * lookAt(origin, look, up):
	 *    Places camera's position and orientation
	 *    in similar manner to gluLookAt
	 **/
	void lookAt(const Point3& Origin, const Point3& Look, const Vector3& Up) {
		eye = Origin;
		n = Vector3(Look, eye);
		u = Up.cross(n);
		v = n.cross(u);
	}

	/**
	 * setLensShape():
	 *   Store new values for the shape of camera's Frustum
	 **/
	void setLensShape(double _angle, double _aspectRatio, double _nearDist, double _farDist) {
		angle = _angle;
		aspectRatio = _aspectRatio;
		nearDist = _nearDist;
		farDist = _farDist;
		H = nearDist * tan(45 * M_PI / 360);
		W = H * aspectRatio;
	}

	Point3 getEye() const {
		return eye;
	}

	/**
	 * operator<<:
	 *   Display Camera's values in nice display output
	 **/
	friend ostream& operator<<(ostream& out, const Camera& cam) {
		return out << "Eye: " << cam.eye <<
			" U: " << cam.u <<
			" V: " << cam.v <<
			" N: " << cam.n <<
			"(angle = " << cam.angle <<
			", aspRat = " << cam.aspectRatio << ")" << cam.W << " " << cam.H << endl;
	}
};

#endif
