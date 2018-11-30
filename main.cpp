#include <stdlib.h>

#include <GL/glut.h>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <math.h>
//#include <png.h>

#include "Window.hpp"
#include "Camera.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "TaperedCylinder.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "Light.hpp"

using namespace std;

//#define PI 3.14159265358979323846

static bool calcShadows = true; //calculate shadows
static int maxRef = 3; //maximum times to reflect light

//static bool lvFlag = GL_FALSE;
//static bool smoothLighting = true;
//static bool rayTrace = false;

static const int FPS = 60;
static const int DELAY = (1000 / FPS);
static Camera Cam;
static Window Win(720, 720, 150, 150, "Ray Tracer");

Light * Lights[8];
DrawableObject * Objs[100];

//void matrixMultiply4(float M1[], float M2[], float R[]);
//void matrixMultiply16(float M1[], float M2[], float R[]);
void traceRays();

/*
void setPolishedSilver(int face)
{
	// Set its properties... (to be silver-like)
	float ambient[] = { 0.23125, 0.23125, 0.23125, 1.0 };
	float diffuse[] = { 0.2775, 0.2775, 0.2775, 1.0 };
	float specular[] = { 0.773911, 0.773911, 0.773911, 1.0 };
	float shininess = 89.6;
	//glMaterialfv(face, GL_AMBIENT, ambient);
	//glMaterialfv(face, GL_DIFFUSE, diffuse);
	//glMaterialfv(face, GL_SPECULAR, specular);
	//glMaterialf(face, GL_SHININESS, shininess);
}
*/

/*
void placeLight0()
{
	GLfloat brit = 10.0;
	GLfloat x = 30, y = 30, z = -50;
	GLfloat pos[] = { x, y, z, 1.0 };
	GLfloat amb[] = { 0, 0, 0, 1.0 };
	GLfloat dif[] = { brit, brit, brit, 1.0 };
	GLfloat spc[] = { brit, brit, brit, 1.0 };
	//GLfloat dir[] = { 0, -50, 0, 0 }; //for spotlight

	// For Light 0, set the position, ambient, diffuse, and specular values
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spc);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, lvFlag);

	glEnable(GL_LIGHT0);

	glPushMatrix();
	{
		glDisable(GL_LIGHTING);
		glTranslatef(x, y, z);
		glColor3f(1, 1, 0);
		glutSolidSphere(20, 10, 10);
		glEnable(GL_LIGHTING);

	}
	glPopMatrix();
}
*/

// Set the viewport to the full screen!
//glViewport(0, 0, Win.width, Win.height);
//glMatrixMode(GL_MODELVIEW);
//Cam.prepare();

Color traceRay(const Ray& R, const int depth = 1) {
	Color ObjColor(0, 0, 0);

	Vector3 Normal, N;
	float hitTime, smallestHitTime = Cam.farDist;
	DrawableObject * ClosestObj = NULL;

	//go through all the objects and get the closest one we hit (if any)
	for (int i = 0; i < 100 && Objs[i] != NULL; i++) {
		hitTime = Objs[i]->getHit(R, N);
		if (hitTime > 0.00001 && hitTime < smallestHitTime) {
			smallestHitTime = hitTime;
			ClosestObj = Objs[i];
			Normal = N;
		}
	}

	if (ClosestObj != NULL) {
		/* */
		Point3 WorldHitPoint = R.pointAtTime(smallestHitTime);

		Vector3 DV;
		for (int j = 0; j < 8 && Lights[j] != NULL; j++) {
			//Color Temp = 
			bool isLit = true;
			if (calcShadows) {
				Vector3 S = Vector3(WorldHitPoint, Lights[j]->Position); // Lights[j]->Position - WorldHitPoint; 
				float shadowHit;
				Ray ShadowRay(WorldHitPoint, S);
				for (int k = 0; k < 100 && isLit && Objs[k] != NULL; k++) {
					if (Objs[k] == ClosestObj) {
						continue;
					}
					else {
						shadowHit = Objs[k]->getHit(ShadowRay, DV);
						if (shadowHit > 0 && shadowHit < 1) {
							isLit = false;
						}
					}
				}
			}

			if (isLit) {
				ObjColor = ObjColor + ClosestObj->calcFromLight(Lights[j], Cam.eye, WorldHitPoint, Normal);
			}
		}

		if (depth < maxRef) {
			//formula for reflection Ref: r = dir - 2(dir . m) m

			float p = 2 * R.Direction.dot(Normal);
			Vector3 RefVec(R.Direction.dx - (p * Normal.dx), R.Direction.dy - (p * Normal.dy), R.Direction.dz - (p * Normal.dz));
			//RefVec.normalize();
			Ray RefRay(WorldHitPoint, RefVec);
			//cout << Normal << "; " << R.Direction << "; " << RefVec << endl;
			Color ReflectColor = traceRay(RefRay, depth + 1);
			ReflectColor.r *= ClosestObj->Props.specular[0];
			ReflectColor.g *= ClosestObj->Props.specular[1];
			ReflectColor.b *= ClosestObj->Props.specular[2];
			ObjColor = ObjColor + ReflectColor;
		}
		/* */
		//ObjColor.set(1,1,1);
	}

	return ObjColor;
}

void drawPixel(Color C, int x, int y) {
	glColor3f(C.r, C.g, C.b);
	glRecti(x, y, x + 1, y + 1);
}

void traceRays() {
	std::cout << "start ray tracing" << endl;
	glDisable(GL_LIGHTING);
	glViewport(0, 0, Win.width, Win.height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, Win.width, 0, Win.height);
	/*
	FILE * image = fopen("output.png", "wb");
	if(!image)
	{
		cerr << "Couldn't create output handle" << endl;
		return;
	}

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		cerr << "Couldn't create png crite struct." << endl;
		return;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr)
	{
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		cerr << "Couldn't create png info struct." << endl;
		return;
	}

	if(setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(image);
		cerr << "Couldn't set PNG jump." << endl;
		return;
	}

	png_init_io(png_ptr, image);

	png_set_IHDR(png_ptr, info_ptr, Win.width, Win.height, 16, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	png_write_info(png_ptr, info_ptr);
	*/

	float cN = -Cam.nearDist, cU, cV;
	std::cout << Cam << endl;
	/* */
	//png_byte * row_pointer = (png_byte *) malloc(info_ptr->rowbytes);
	for (int r = 0; r < Win.height; r++) {
		cV = Cam.H * (2.0 * r / Win.height - 1.0);
		for (int c = 0; c < Win.width; c++) {
			cU = Cam.W * (2.0 * c / Win.width - 1.0);
			//cout << cU << endl;
			float dirx = cN * Cam.n.dx + cU * Cam.u.dx + cV * Cam.v.dx,
				diry = cN * Cam.n.dy + cU * Cam.u.dy + cV * Cam.v.dy,
				dirz = cN * Cam.n.dz + cU * Cam.u.dz + cV * Cam.v.dz;
			Vector3 Dir(dirx, diry, dirz);
			Dir.normalize();

			Ray R(Cam.eye, Dir);

			Color ObjColor = traceRay(R);
			drawPixel(ObjColor, c, r);
			//png_byte pixel[4] = { ObjColor.r, ObjColor.g, ObjColor.b, 0 };
			//row_pointer[c*4] = (png_byte) 255 * ObjColor.r;
			//row_pointer[c*4 + 1] = (png_byte) 255 * ObjColor.g;
			//row_pointer[c*4 + 2] = (png_byte) 255 * ObjColor.b;
			//row_pointer[c*4] = pixel;

			//cerr << "traceRays(): Output your results or something!!!" << endl;
		}

		//png_write_row(png_ptr, row_pointer);
		glFlush();
	}

	//png_write_end(png_ptr, NULL);

	/* cleanup */
	//free(row_pointer);
	//fclose(image);
	std::cout << "done tracing rays" << endl;
}


void init() {
	Point3 eye(0, 3, 3);
	Point3 look(0, 0, 0);  // Slight downward look
	Vector3 up(0, 1, 0);

	Cam.lookAt(eye, look, up);
	// Cam.setLensShape(45, Win.width / Win.height, 1, 100); // this is the correct code and used to work in 2006, but the aspect ratio is messed up now
	Cam.setLensShape(90, 4.5, 1, 100);

	//glClearColor (0.0, 0.0, 0.0, 0.0);
	// Set up lighting and depth-test
	/*
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);   // For z-buffering!
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);
	 */

	MaterialProperties Mirror(0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1);
	MaterialProperties Pearl(0.25, 0.20725, 0.20725, 1.0, 1.0, 0.829, 0.829, 1.0, 0.296648, 0.296648, 0.296648, 1.0, 11.264);
	MaterialProperties Obsidian(0.05375, 0.05, 0.06625, 1.0, 0.18275, 0.17, 0.22525, 1.0, 0.332741, 0.328634, 0.346435, 1.0, 38.4);
	MaterialProperties Chrome(0.25, 0.25, 0.25, 1.0, 0.4, 0.4, 0.4, 1.0, 0.774597, 0.774597, 0.774597, 1.0, 76.8);
	MaterialProperties PolishedSilver(0.23125, 0.23125, 0.23125, 1.0, 0.2775, 0.2775, 0.2775, 1.0, 0.773911, 0.773911, 0.773911, 1.0, 89.6);
	MaterialProperties Copper(0.19125, 0.0735, 0.0225, 1.0, 0.7038, 0.27048, 0.0828, 1.0, 0.256777, 0.137622, 0.086014, 1.0, 128.0);
	MaterialProperties Gold(0.24725, 0.1995, 0.0745, 1.0, 0.75164, 0.60648, 0.22648, 1.0, 0.628281, 0.555802, 0.366065, 1.0, 51.2);

	Lights[0] = new Light(0, 0.0, 0.0, 0.0, 1.0, 0.7, 0.3, 0.3, 1.0, 0.7, 0.3, 0.3, 1.0, 40, Point3(-5, 8, 5));
	Lights[1] = new Light(0, 0.0, 0.0, 0.0, 1.0, 0.3, 0.7, 0.3, 1.0, 0.3, 0.7, 0.3, 1.0, 40, Point3(5, 7, -5));
	Lights[2] = new Light(0, 0.0, 0.0, 0.0, 1.0, 0.3, 0.3, 0.7, 1.0, 0.3, 0.3, 0.7, 1.0, 40, Point3(0, 9, 4));
	/* */
	Objs[0] = new Sphere(Pearl);
	//Objs[0]->translate(-2.5, -1, -2);
	//Objs[0]->rotate(45, -1, 0, -1);
	//Objs[0]->scale(1, 2, 1);

	Objs[1] = new Plane(Copper);
	Objs[1]->translate(0, -20, 0);
	Objs[1]->rotate(-90, 1, 0, 0);

	Objs[2] = new Plane(Mirror);

	//Objs[1] = new Sphere(PolishedSilver);
	//Objs[1]->rotate(30, 0, 0, 1);
	//Objs[1]->scale(1, 2, 1);

	//Objs[2] = new Sphere(Pearl);
	//Objs[2]->translate(3, 2, -2);
	//Objs[2]->rotate(60, 1, 1, 0);
	//Objs[2]->scale(2, 1.75, 1.5);

	/* *
	Objs[0] = new Sphere(PolishedSilver);
	Objs[0]->translate(-1, 1, 0);
	Objs[1] = new Sphere(PolishedSilver);
	Objs[1]->translate(1, 1, 0);
	/* */


	//Objs[4] = new Sphere(Obsidian);
	//Objs[4]->translate(-1, 4, -2);
	//Objs[4]->scale(2.5, 1.5, 1);


	////glScaled(1,1.5,1); //regular GL calls still work :)

	//Objs[6] = new TaperedCylinder(Chrome, 0);
	//Objs[6]->translate(-2, 1.7071067812, 2);
	//Objs[6]->scale(0.7071067812, 0.7071067812, 0.7071067812);
	//Objs[6]->rotate(-90, 1, 0, 0);


	//Objs[7] = new Sphere(Chrome);
	//Objs[7]->translate(-2, 1, 2);

	//Objs[8] = new TaperedCylinder(Chrome, 0);
	//Objs[8]->translate(-2, 0.2928932188, 2);
	//Objs[8]->scale(0.7071067812, 0.7071067812, 0.7071067812);
	//Objs[8]->rotate(90, 1, 0, 0);

	//Objs[6]->scale(1,1,3);

}

/*
FILE * read_png(char *file_name)  // We need to open the file
{
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	png_uint_32 width, height;
	int bit_depth, color_type, interlace_type;
	FILE * fp;
	if ((fp = fopen(file_name, "rb")) == NULL)
		return NULL;//(ERROR);

	cout << "creating read struct" << endl;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (png_ptr == NULL)
	{
		fclose(fp);
		return NULL;//(ERROR);
	}
}
*/

int main(int argc, char ** argv) {

	// Initialize the GLUT environment
	glutInit(&argc, argv);

	// Double-buffered, using RGB
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(Win.width, Win.height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Test");

	init(); // Initialize non-GLUT content
	glutDisplayFunc(traceRays);
	glutMainLoop();
	return 0;
}
