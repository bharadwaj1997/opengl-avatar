#ifndef _LEG_H
#define _LEG_H

#if defined(__APPLE__)
	#include <GLUT/glut.h>
	#define APIENTRY
	#define GLAPIENTRY APIENTRY
#elif defined(__unix__)
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1

#define true  1
#define false 0

#define KEY_ESC 27

#define PI 3.1415926535898

void draw_thigh(int dl_thigh);
void draw_calf(int dl_calf);

#endif
