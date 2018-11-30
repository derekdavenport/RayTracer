/*
 *  DrawableObject.cpp
 *  RayTracer
 *
 *  Created by Derek Davenport on 11/17/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "DrawableObject.hpp"

/*
virtual void DrawableObject::draw()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  Props.ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  Props.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Props.specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Props.shininess);
}
*/

void DrawableObject::matrixMultiply4(float M1[16], float M2[4], float R[4]) const {
	for (int i = 0; i < 4; i++) // look at this row
	{
		R[i] = 0;
		for (int k = 0; k < 4; k++) {
			R[i] += M1[i + 4 * k] * M2[k];
		}
		//cout << R[i] << endl;
	}
}

void DrawableObject::matrixMultiply16(float M1[], float M2[], float R[]) const {
	// look at this row
	for (int i = 0; i < 4; i++) {
		// look at this column
		for (int j = 0; j < 4; j++) {
			R[i + 4 * j] = 0;
			for (int k = 0; k < 4; k++) {
				R[i + 4 * j] += M1[i + 4 * k] * M2[k + 4 * j];
			}
			//cout << R[4 * i + j] << endl;
		}
	}
}

float DrawableObject::m3_det(float mat[]) const {
	float det;

	det = mat[0] * (mat[4] * mat[8] - mat[7] * mat[5])
		- mat[1] * (mat[3] * mat[8] - mat[6] * mat[5])
		+ mat[2] * (mat[3] * mat[7] - mat[6] * mat[4]);

	return det;
}

void DrawableObject::m4_submat(float mr[], float mb[], int i, int j) const {
	int ti, tj, idst, jdst;

	for (ti = 0; ti < 4; ti++) {
		if (ti < i)
			idst = ti;
		else
			if (ti > i)
				idst = ti - 1;

		for (tj = 0; tj < 4; tj++) {
			if (tj < j)
				jdst = tj;
			else
				if (tj > j)
					jdst = tj - 1;

			if (ti != i && tj != j)
				mb[idst * 3 + jdst] = mr[ti * 4 + tj];
		}
	}
}

float DrawableObject::m4_det(float mr[]) const {
	float det, result = 0, i = 1;
	float msub3[9];
	int     n;

	for (n = 0; n < 4; n++, i *= -1) {
		m4_submat(mr, msub3, 0, n);

		det = m3_det(msub3);
		result += mr[n] * det * i;
	}

	return result;
}

void DrawableObject::m4_inverse(float ma[], float mr[]) const {
	float mdet = m4_det(ma);
	float mtemp[9];
	int i, j, sign;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			sign = 1 - ((i + j) % 2) * 2;

			m4_submat(ma, mtemp, i, j);

			mr[i + j * 4] = (m3_det(mtemp) * sign) / mdet;
		}
	}
}

void DrawableObject::m4_transpose(float M[], float R[]) const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			R[i + 4 * j] = M[4 * i + j];
		}
	}
}

void DrawableObject::printMatrix(float M[]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << M[i + 4 * j] << " ";
		}
		cout << endl;
	}
}