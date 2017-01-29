#include "../headers/neck.h"



void draw_neck(int dl_neck) {
   int i;

   glPushMatrix();

   glNewList(dl_neck, GL_COMPILE);
   glLineWidth(3);
   glColor3f(1, 0.8, 0.6);

   for(i = 0; i < 360; i++) {
      glBegin(GL_LINES);
         glVertex3f(0, 0.2, 0);
         glVertex3f(0.4, 0.3, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.4, 0.3, 0);
         glVertex3f(0.7, 0.5, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.7, 0.5, 0);
         glVertex3f(1, 0.7, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(1, 0.7, 0);
         glVertex3f(1.5, 0.6, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(1.5, 0.6, 0);
         glVertex3f(1.7, 0.5, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(1.7, 0.5, 0);
         glVertex3f(2, 0.5, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(2, 0.5, 0);
         glVertex3f(2.1, 0.3, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(2.1, 0.3, 0);
         glVertex3f(2.1, 0.5, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(2.1, 0.5, 0);
         glVertex3f(2.2, 0, 0);
      glEnd();

      glRotatef(1, 1, 0, 0);
   }

   glEndList();
   glPopMatrix();
}
