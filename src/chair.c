#include "../headers/chair.h"



void drawCircle(float cx, float cy, float r, int num_segments)
{
	int count;
	glBegin(GL_POLYGON);
	for( count = 0; count < num_segments; count++)
	{
		float theta = 2.0f * 3.1415926f * (float)count / (float)num_segments;//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex3f(x + cx, 0, y + cy);//output vertex

	}
	glEnd();
}


void drawRectangle(double width, double length, double height){

	if(height == 0)
	{
		glBegin(GL_QUADS);
			glVertex3d(0,0,0);
			glVertex3d(0,length,0);
			glVertex3d(width,length,0);
			glVertex3d(width, 0,0);
		glEnd();
	}
	else if(length == 0)
	{
		glBegin(GL_QUADS);
			glVertex3d(0,0,0);
			glVertex3d(0,0,height);
			glVertex3d(width, 0, height);
			glVertex3d(width, 0, 0);
		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
			glVertex3d(0,0,0);
			glVertex3d(0,length,0);
			glVertex3d(0,length,height);
			glVertex3d(0,0,height);
		glEnd();
	}

}

void drawPave(double width, double length, double height){

	glPushMatrix();
		drawRectangle(width,length,0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0,height);
		drawRectangle(width,length,0);
	glPopMatrix();

	glPushMatrix();
		drawRectangle(width,0,height);
		drawRectangle(0,length,height);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(width,length,0);
		drawRectangle(-width,0,height);
		drawRectangle(0,-length,height);
	glPopMatrix();
}



// une chaise
void draw_Seat(int dl_chair) {

	double widthPied = 0.8;
	double widthSeat = 6;
	double heightPied = 6;


	glPushMatrix();
	glNewList(dl_chair,GL_COMPILE);


	// l'assise
 	glColor3f(0.9, 0.3, 0.4);
	drawPave(widthSeat,6,1);

	// le dossier
	glColor3f(0.3, 0.9, 0.4);
	glPushMatrix();
		glTranslatef(0.1,0.1,0);
		drawPave(0.95,1,7);
		glTranslatef(widthSeat-1.1,0,0);
		drawPave(0.95,1,7);
	glPopMatrix();

	//les tiges du dossier
	glColor3f(1, 1, 1);
	glPushMatrix();
		glTranslatef(0.15,0.15,4);
		drawPave(widthSeat-0.2,0.9,0.5);
		glTranslatef(0,0,2);
		drawPave(widthSeat-0.2,0.9,0.5);
	glPopMatrix();

	// les pieds
	glColor3f((float)248/255,(float)248/255, (float)255/255);
	glPushMatrix();
		glTranslatef(0,0,-heightPied);
		drawPave(widthPied,widthPied,heightPied);
		glTranslatef(0,5,0);
		drawPave(widthPied,widthPied,heightPied);
		glTranslatef(widthSeat-1,0,0);
		drawPave(widthPied,widthPied,heightPied);
		glTranslatef(0,-5,0);
		drawPave(widthPied,widthPied,heightPied);
	glPopMatrix();

	// le tapis
	glPushMatrix();
	    glRotatef(90,1,0,0);
	    glColor3f(0.65,0.56,0.35);
	    glTranslatef(widthSeat/2,-heightPied,-widthSeat/2);
	    drawCircle(0,0,400,30);
	    glTranslatef(0,-0.1,0);
	    glColor3f(0.1,0.1,0.8);
	    drawCircle(0,0,650,30);
	glPopMatrix();

	glEndList();
	glPopMatrix();
}
