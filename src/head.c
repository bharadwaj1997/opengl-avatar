#include "../headers/head.h"



void draw_head(int dl_head) {
   int i;
   float j = 0.1;

   glPushMatrix();

   glNewList(dl_head, GL_COMPILE);
   glLineWidth(3);
   glColor3f(1, 0.8, 0.6);
   glRotatef(90, 0, 1, 0);
   glScalef(1.5, 1, 1.2);


   for(i = 0; i < 360; i++) {
      glBegin(GL_LINES);
         glVertex3f(0, 0, 0);
         glVertex3f(0.4, 0, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.4, 0, 0);
         glVertex3f(0.7, 1, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.7, 1, 0);
         glVertex3f(1, 1.2, 0);
      glEnd();
      if((i > 60 && i < 100) || (i > 240 && i < 300)) {
         glBegin(GL_LINES);
            glVertex3f(1, 1.2, 0);
            glVertex3f(1.1, 1.4, 0);
         glEnd();
         glBegin(GL_LINES);
            glVertex3f(1.1, 1.4, 0);
            glVertex3f(1.5, 1, 0);
         glEnd();

         glBegin(GL_LINES);
            glVertex3f(1, 1.2, 0);
            glVertex3f(1+j, 1.2+j, 0);
         glEnd();
         glBegin(GL_LINES);
            glVertex3f(1+j, 1.2+j, 0);
            glVertex3f(1.5, 1, 0);
         glEnd();
      }
      else {
         glBegin(GL_LINES);
            glVertex3f(1, 1.2, 0);
            glVertex3f(1.5, 1.1, 0);
         glEnd();

         glBegin(GL_LINES);
            glVertex3f(1.5, 1.1, 0);
            glVertex3f(1.7, 1, 0);
         glEnd();
      }

      glBegin(GL_LINES);
         glVertex3f(1.5, 1, 0);
         glVertex3f(1.7, 1, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(1.7, 1, 0);
         glVertex3f(2, 0.8, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(2, 0.8, 0);
         glVertex3f(2.1, 0.6, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(2.1, 0.6, 0);
         glVertex3f(2.1, 0.4, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(2.1, 0.4, 0);
         glVertex3f(2.2, 0, 0);
      glEnd();

      glRotatef(1, 1, 0, 0);
   }

   glPushMatrix();
   glTranslatef(1.3, 0.2, 0);
      glColor3f(1, 1, 1);
      glScalef(0.5, 1.2, 1.1);
      glutSolidSphere(1 ,8 ,8);
         glColor3f(0, 0, 0);
         glScalef(1, 2.3, 1.1);
         glutSolidSphere(0.5 ,8 ,8);
   glPopMatrix();

   glEndList();
   glPopMatrix();
}
