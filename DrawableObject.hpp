/*
 *  DrawableObject.h
 *  RayTracer
 *
 *  Created by Derek Davenport on 11/17/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __DRAWABLE_OBJECT_HPP
#define __DRAWABLE_OBJECT_HPP

#include <iostream>
//#include <GLUT/glut.h>
//#include <OpenGL/gl.h>
//#include <GLUT/vvector.h>
#define _USE_MATH_DEFINES
#include <math.h>
//#include "utils.h"
#include "Ray.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"
#include "MaterialProperties.hpp"
#include "Color.hpp"
#include "Light.hpp"
//#include "MatrixMath.hpp"



using namespace std;

class DrawableObject {
public:
	Point3 Center;
	MaterialProperties Props;
	float tMatrix[16];
	float tMatrixInv[16];
	float tMatrixInvTrans[16];

	DrawableObject(const MaterialProperties & _Props) : Props(_Props), Center(0, 0, 0) {

		tMatrix[0] = 1, tMatrix[4] = 0, tMatrix[8] = 0, tMatrix[12] = 0,
			tMatrix[1] = 0, tMatrix[5] = 1, tMatrix[9] = 0, tMatrix[13] = 0,
			tMatrix[2] = 0, tMatrix[6] = 0, tMatrix[10] = 1, tMatrix[14] = 0,
			tMatrix[3] = 0, tMatrix[7] = 0, tMatrix[11] = 0, tMatrix[15] = 1;
			/*
			float r[16];
			m4_inverse(tMatrix, tMatrixInv);
			matrixMultiply16(tMatrix, tMatrixInv, r);
			cout << tMatrixInv[12] << " " << tMatrixInv[13] << " " << tMatrixInv[14] << " " << tMatrixInv[15] << endl;
			*/

			//memcpy(tMatrix, 
			//cerr << "We need to set the Model View Matrix!" << endl;
			//glMatrixMode(GL_MODELVIEW);
			//glGetFloatv(GL_MODELVIEW_MATRIX, tMatrix);
		calcInv();
		/* */
		tMatrixInv[0] = 1, tMatrixInv[4] = 0, tMatrixInv[8] = 0, tMatrixInv[12] = 0,
			tMatrixInv[1] = 0, tMatrixInv[5] = 1, tMatrixInv[9] = 0, tMatrixInv[13] = 0,
			tMatrixInv[2] = 0, tMatrixInv[6] = 0, tMatrixInv[10] = 1, tMatrixInv[14] = 0,
			tMatrixInv[3] = 0, tMatrixInv[7] = 0, tMatrixInv[11] = 0, tMatrixInv[15] = 1;


		tMatrixInvTrans[0] = 1, tMatrixInvTrans[4] = 0, tMatrixInvTrans[8] = 0, tMatrixInvTrans[12] = 0,
			tMatrixInvTrans[1] = 0, tMatrixInvTrans[5] = 1, tMatrixInvTrans[9] = 0, tMatrixInvTrans[13] = 0,
			tMatrixInvTrans[2] = 0, tMatrixInvTrans[6] = 0, tMatrixInvTrans[10] = 1, tMatrixInvTrans[14] = 0,
			tMatrixInvTrans[3] = 0, tMatrixInvTrans[7] = 0, tMatrixInvTrans[11] = 0, tMatrixInvTrans[15] = 1;


	}

	float maxf(float a, float b) const {
		return (a > b) ? a : b;
	}

	void calcInv() {
		m4_inverse(tMatrix, tMatrixInv);
		m4_transpose(tMatrixInv, tMatrixInvTrans);

	}

	void translate(float x, float y, float z) {
		//glMatrixMode(GL_MODELVIEW);
		//glPushMatrix();
		//{
			//glLoadMatrixf(tMatrix);
			//glMultMatrixf(tMatrix);
		float tempMatrix[16];
		memcpy(tempMatrix, tMatrix, 16 * sizeof(float)); //copy tMatrix to tempMatrix
		float translateMatrix[16] =
		{
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
		};
		matrixMultiply16(tempMatrix, translateMatrix, tMatrix);
		//glTranslatef(x, y, z);
		//glGetFloatv(GL_MODELVIEW_MATRIX, tMatrix);
	//}
	//glPopMatrix();
		calcInv();

		cout << "tMatrixInv" << endl;
		printMatrix(tMatrixInv);
		cout << "tMatrixInvTrans" << endl;
		printMatrix(tMatrixInvTrans);
	}

	void scale(float x, float y, float z) {
		/*
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			glLoadMatrixf(tMatrix);
			//glMultMatrixf(tMatrix);
			glScalef(x, y, z);
			glGetFloatv(GL_MODELVIEW_MATRIX, tMatrix);
		}
		glPopMatrix();
		*/
		float tempMatrix[16];
		memcpy(tempMatrix, tMatrix, 16 * sizeof(float));
		float scaleMatrix[16] =
		{
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
		};
		matrixMultiply16(tempMatrix, scaleMatrix, tMatrix);
		calcInv();
	}

	void rotate(float angle, float x, float y, float z) {
		float c = cos(M_PI / 180 * angle);
		float s = sin(M_PI / 180 * angle);
		float oc = 1 - c;
		float tempMatrix[16];
		memcpy(tempMatrix, tMatrix, 16 * sizeof(float));
		float rotateMatrix[16] =
		{
			c + oc * x * x,      oc * x * y - s * z,  oc * x * z + s * y, 0,
			oc * y * x + s * z,  c + oc * y * y,      oc * y * z - s * x, 0,
			oc * z * x - s * y,  oc * z * y + s * x,  c + oc * z * z,     0,
			0,                   0,                   0,                  1
		};
		matrixMultiply16(tempMatrix, rotateMatrix, tMatrix);
		/*
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			glLoadMatrixf(tMatrix);
			glRotatef(angle, x, y, z);
			glGetFloatv(GL_MODELVIEW_MATRIX, tMatrix);
		}
		glPopMatrix();
		*/
		calcInv();
	}

	virtual void draw() {
		cerr << "DrawableObject::draw(): We don't need to be GL drawing anything!" << endl;
		/*
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  Props.ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  Props.diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Props.specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Props.shininess);
		 */
	}

	virtual float getHit(const Ray & R, Vector3& Norm) = 0;

	virtual Vector3 getNormal(Point3& Point) {
		cerr << "DEBUG: This function should never be called." << endl;
		return Vector3(0, 0, 0);
	}

	/***
		* calcFromLight:
		*     L : Light is a given Light (in World Space)
		*     Eye: is location of Camera in World Space
		*     HitPoint: is location of Point on object hit (in World Space)
		*     Norm: is normal at this point (in OBJECT SPACE - possibly change this!)
		***/
	Color calcFromLight(const Light * L, const Point3 & Eye, Point3 & HitPoint, Vector3 & M) {
		/*float t[4], m[4];
		Vector3 M;

		// Convert Normal to World Space
		Norm.getMatrix(t);
		//m4_transpose(tMatrixInv, tMatrixInvTrans);
		matrixMultiply4(tMatrixInvTrans, t, m);
		//cout << "Inv" << endl;
		M.set(m[0], m[1], m[2]);
		//cout << m[0] << endl;
		//cout << M.magnitude() << endl;
		M.normalize();*/

		//Eye.getMatrix(t);
		//matrixMultiply4(tMatrixInv, t, m);
		//Vector3 V(m[0] - HitPoint.x, m[1] - HitPoint.y, m[2] - HitPoint.z);
		Vector3 V = Vector3(HitPoint, Eye); // Eye - HitPoint;
		V.normalize();
		//L->Position.getMatrix(t);
		//matrixMultiply4(tMatrixInv, t, m);
		//Vector3 S(m[0] - HitPoint.x, m[1] - HitPoint.y, m[2] - HitPoint.z); // = L->Position - HitPoint;
		Vector3 S = Vector3(HitPoint, L->Position); //L->Position - HitPoint;
		S.normalize();

		float lambert = maxf(S.dot(M), 0.0);
		Vector3 H(S.dx + V.dx, S.dy + V.dy, S.dz + V.dz);
		H.normalize();
		float phong = maxf(H.dot(M), 0.0);
		//cout << phong << endl;
		//phong = 0;

		float r = L->ambient[0] * Props.ambient[0] + L->diffuse[0] * Props.diffuse[0] * lambert + L->specular[0] * Props.specular[0] * pow(phong, L->f);
		float g = L->ambient[1] * Props.ambient[1] + L->diffuse[1] * Props.diffuse[1] * lambert + L->specular[1] * Props.specular[1] * pow(phong, L->f);
		float b = L->ambient[2] * Props.ambient[2] + L->diffuse[2] * Props.diffuse[2] * lambert + L->specular[2] * Props.specular[2] * pow(phong, L->f);
		//cout << r << " " << L->ambient[0] << " " << Props.ambient[0] << " " << L->diffuse[0] << " " << lambert << " " << L->specular[0] << " " << Props.specular[0] << " " << phong << " " << L->f << endl;

		return Color(r, g, b);
	}

	void matrixMultiply4(float M1[], float M2[], float R[]) const;
	void matrixMultiply16(float M1[], float M2[], float R[]) const;
	float m3_det(float mat[]) const;
	void m4_submat(float mr[], float mb[], int i, int j) const;
	float m4_det(float mr[]) const;
	void m4_inverse(float ma[], float mr[]) const;
	void m4_transpose(float M[], float R[]) const;
	void printMatrix(float M[]);


};
#endif