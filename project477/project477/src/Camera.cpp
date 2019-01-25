#include "Camera.h"



#ifdef __APPLE__

#include <GLUT/glut.h>

#else

#ifdef _WIN32

#include "GL/glut.h"

#else

#include <GL/freeglut.h>

#endif

#endif



#include <iostream>

#include <cmath>

#include <cstring>

#include <vector>



//Window parameters

int cwidth = 1024;

int cheight = 768;



//Model matrices

double c_matrix_s[16];

double c_matrixI_s[16];

double c_matrix_t[16];

double c_matrixI_t[16];



///* Ortho (if used) */

double c_left = 0.0;		/* ortho view volume params */

double c_right = 0.0;

double c_bottom = 0.0;

double c_top = 0.0;

double c_zNear = 0.1;

double c_zFar = 50.0;

double cfovy = 45.0;

double cprev_z = 0;



/* Mouse Interface  */

int c_mouseX = 0;		/* mouse control variables */

int c_mouseY = 0;

bool c_mouseLeft = false;

bool c_mouseMiddle = false;

bool c_mouseRight = false;



double c_dragPosX = 0.0;

double c_dragPosY = 0.0;

double c_dragPosZ = 0.0;



bool sideView_bool = true;



double vlenC(double x, double y, double z)

{

	return sqrt(x * x + y * y + z * z);

}



void invertMatrixC(const GLdouble * m, GLdouble * out)

{



	/* NB. OpenGL Matrices are COLUMN major. */

#define MAT(m,r,c) (m)[(c)*4+(r)]



/* MACRO (row,column) to index. */

#define m11 MAT(m,0,0)

#define m12 MAT(m,0,1)

#define m13 MAT(m,0,2)

#define m14 MAT(m,0,3)

#define m21 MAT(m,1,0)

#define m22 MAT(m,1,1)

#define m23 MAT(m,1,2)

#define m24 MAT(m,1,3)

#define m31 MAT(m,2,0)

#define m32 MAT(m,2,1)

#define m33 MAT(m,2,2)

#define m34 MAT(m,2,3)

#define m41 MAT(m,3,0)

#define m42 MAT(m,3,1)

#define m43 MAT(m,3,2)

#define m44 MAT(m,3,3)



	GLdouble det;

	GLdouble d12, d13, d23, d24, d34, d41;

	GLdouble tmp[16];		/* Allow out == in. */



	/* Inverse = adjoint / det. (See linear algebra texts.) */



	/* pre-compute 2x2 dets for last two rows when computing */

	/* cofactors of first two rows. */

	d12 = (m31 * m42 - m41 * m32);

	d13 = (m31 * m43 - m41 * m33);

	d23 = (m32 * m43 - m42 * m33);

	d24 = (m32 * m44 - m42 * m34);

	d34 = (m33 * m44 - m43 * m34);

	d41 = (m34 * m41 - m44 * m31);



	tmp[0] = (m22 * d34 - m23 * d24 + m24 * d23);

	tmp[1] = -(m21 * d34 + m23 * d41 + m24 * d13);

	tmp[2] = (m21 * d24 + m22 * d41 + m24 * d12);

	tmp[3] = -(m21 * d23 - m22 * d13 + m23 * d12);



	/* Compute determinant as early as possible using these cofactors. */

	det = m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2] + m14 * tmp[3];



	/* Run singularity test. */

	if (det == 0.0) {

		/* printf("invert_matrix: Warning: Singular matrix.\n"); */

	/* 	  memcpy(out,_identity,16*sizeof(double)); */

	}

	else {

		GLdouble invDet = 1.0 / det;

		/* Compute rest of inverse. */

		tmp[0] *= invDet;

		tmp[1] *= invDet;

		tmp[2] *= invDet;

		tmp[3] *= invDet;



		tmp[4] = -(m12 * d34 - m13 * d24 + m14 * d23) * invDet;

		tmp[5] = (m11 * d34 + m13 * d41 + m14 * d13) * invDet;

		tmp[6] = -(m11 * d24 + m12 * d41 + m14 * d12) * invDet;

		tmp[7] = (m11 * d23 - m12 * d13 + m13 * d12) * invDet;



		/* Pre-compute 2x2 dets for first two rows when computing */

		/* cofactors of last two rows. */

		d12 = m11 * m22 - m21 * m12;

		d13 = m11 * m23 - m21 * m13;

		d23 = m12 * m23 - m22 * m13;

		d24 = m12 * m24 - m22 * m14;

		d34 = m13 * m24 - m23 * m14;

		d41 = m14 * m21 - m24 * m11;



		tmp[8] = (m42 * d34 - m43 * d24 + m44 * d23) * invDet;

		tmp[9] = -(m41 * d34 + m43 * d41 + m44 * d13) * invDet;

		tmp[10] = (m41 * d24 + m42 * d41 + m44 * d12) * invDet;

		tmp[11] = -(m41 * d23 - m42 * d13 + m43 * d12) * invDet;

		tmp[12] = -(m32 * d34 - m33 * d24 + m34 * d23) * invDet;

		tmp[13] = (m31 * d34 + m33 * d41 + m34 * d13) * invDet;

		tmp[14] = -(m31 * d24 + m32 * d41 + m34 * d12) * invDet;

		tmp[15] = (m31 * d23 - m32 * d13 + m33 * d12) * invDet;



		memcpy(out, tmp, 16 * sizeof(GLdouble));

	}



#undef m11

#undef m12

#undef m13

#undef m14

#undef m21

#undef m22

#undef m23

#undef m24

#undef m31

#undef m32

#undef m33

#undef m34

#undef m41

#undef m42

#undef m43

#undef m44

#undef MAT

}



void getMatrixC(double _matrix_1[16], double _matrix_2[16])

{

	glGetDoublev(GL_MODELVIEW_MATRIX, _matrix_1);

	invertMatrixC(_matrix_1, _matrix_2);

}



void copyMatrix(const GLdouble * m, GLdouble * out)

{

	/* NB. OpenGL Matrices are COLUMN major. */

#define MAT(m,r,c) (m)[(c)*4+(r)]



/* MACRO (row,column) to index. */

#define m11 MAT(m,0,0)

#define m12 MAT(m,0,1)

#define m13 MAT(m,0,2)

#define m14 MAT(m,0,3)

#define m21 MAT(m,1,0)

#define m22 MAT(m,1,1)

#define m23 MAT(m,1,2)

#define m24 MAT(m,1,3)

#define m31 MAT(m,2,0)

#define m32 MAT(m,2,1)

#define m33 MAT(m,2,2)

#define m34 MAT(m,2,3)

#define m41 MAT(m,3,0)

#define m42 MAT(m,3,1)

#define m43 MAT(m,3,2)

#define m44 MAT(m,3,3)



	GLdouble tmp[16];		/* Allow out == in. */



	tmp[0] = m11;

	tmp[1] = m12;

	tmp[2] = m13;

	tmp[3] = m14;

	tmp[4] = m21;

	tmp[5] = m22;

	tmp[6] = m23;

	tmp[7] = m24;

	tmp[8] = m31;

	tmp[9] = m32;

	tmp[10] = m33;

	tmp[11] = m34;

	tmp[12] = m41;

	tmp[13] = m42;

	tmp[14] = m43;

	tmp[15] = m44;



	memcpy(out, tmp, 16 * sizeof(GLdouble));



#undef m11

#undef m12

#undef m13

#undef m14

#undef m21

#undef m22

#undef m23

#undef m24

#undef m31

#undef m32

#undef m33

#undef m34

#undef m41

#undef m42

#undef m43

#undef m44

#undef MAT

}



void Camera::init(double _matrix_1[16], double _matrix_2[16])

{

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(cfovy, (double)cwidth / (double)cheight, c_zNear, c_zFar);



	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();



	//Translate camera

	glPushMatrix();

	glLoadIdentity();

	glTranslatef(0, 0, -20.0); //Initial camera coordinates (original -5.0)

	glMultMatrixd(_matrix_1);

	getMatrixC(_matrix_1, _matrix_2);

	glPopMatrix();



	copyMatrix(_matrix_1, c_matrix_s);

	copyMatrix(_matrix_2, c_matrixI_s);



	glLoadIdentity();

	glTranslatef(0, -12, 0);

	glRotatef(40.0, 20, 0, 0);

	glTranslatef(0, -8, 0);

	glRotatef(40.0, 20, 0, 0);

	glTranslatef(0, -25, 2);

	glMultMatrixd(_matrix_1);

	getMatrixC(_matrix_1, _matrix_2);

	copyMatrix(_matrix_1, c_matrix_t);

	copyMatrix(_matrix_2, c_matrixI_t);

}



void Camera::zoomout(double _matrix_1[16], double _matrix_2[16])

{

	glLoadIdentity();

	glTranslatef(0, 0, -0.1);

	glMultMatrixd(_matrix_1);

	getMatrixC(_matrix_1, _matrix_2);

	glutPostRedisplay();

}



void Camera::zoomout(double _matrix_1[16], double _matrix_2[16], double num)

{

	glLoadIdentity();

	glTranslatef(0, 0, -num);

	glMultMatrixd(_matrix_1);

	getMatrixC(_matrix_1, _matrix_2);

	glutPostRedisplay();

}



void Camera::zoomin(double _matrix_1[16], double _matrix_2[16])

{

	glLoadIdentity();

	glTranslatef(0, 0, 0.1);

	glMultMatrixd(_matrix_1);

	getMatrixC(_matrix_1, _matrix_2);

	glutPostRedisplay();

}



void Camera::zoomin(double _matrix_1[16], double _matrix_2[16], double num)

{

	glLoadIdentity();

	glTranslatef(0, 0, num);

	glMultMatrixd(_matrix_1);

	getMatrixC(_matrix_1, _matrix_2);

	glutPostRedisplay();

}



void Camera::moveUp(double _matrix_1[16], double _matrix_2[16])

{

	glLoadIdentity();

	glTranslatef(0, -0.4, 0);

	glMultMatrixd(_matrix_1);

	getMatrixC(_matrix_1, _matrix_2);

	glutPostRedisplay();

}



void Camera::moveDown(double _matrix_1[16], double _matrix_2[16])

{

	glLoadIdentity();

	glTranslatef(0, 0.4, 0);

	glMultMatrixd(_matrix_1);

	getMatrixC(_matrix_1, _matrix_2);

	glutPostRedisplay();

}



void Camera::moveRight(double _matrix_1[16], double _matrix_2[16])

{

	glLoadIdentity();

	glTranslatef(-0.4, 0, 0);

	glMultMatrixd(_matrix_1);

	getMatrixC(_matrix_1, _matrix_2);

	glutPostRedisplay();

}



void Camera::moveLeft(double _matrix_1[16], double _matrix_2[16])

{

	glLoadIdentity();

	glTranslatef(0.4, 0, 0);

	glMultMatrixd(_matrix_1);

	getMatrixC(_matrix_1, _matrix_2);

	glutPostRedisplay();

}



void Camera::topView(double _matrix_1[16], double _matrix_2[16])

{

	if (sideView_bool == true)

	{

		glLoadIdentity();

		copyMatrix(c_matrix_t, _matrix_1);

		copyMatrix(c_matrixI_t, _matrix_2);

		glMultMatrixd(_matrix_1);

		getMatrixC(_matrix_1, _matrix_2);

		glutPostRedisplay();

		sideView_bool = false;

	}

	else

	{

		sideView(_matrix_1, _matrix_2);

	}

}



void Camera::sideView(double _matrix_1[16], double _matrix_2[16])

{

	glLoadIdentity();

	copyMatrix(c_matrix_s, _matrix_1);

	copyMatrix(c_matrixI_s, _matrix_2);

	glMultMatrixd(_matrix_1);

	getMatrixC(_matrix_1, _matrix_2);

	glutPostRedisplay();

	sideView_bool = true;

}