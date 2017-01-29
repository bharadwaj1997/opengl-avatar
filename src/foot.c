#include "../headers/foot.h"



void draw_foot(int dl_foot) {
   glNewList(dl_foot, GL_COMPILE);
   glColor3f(1, 0, 0);
      glScalef(0.4, 1.5, 0.7);
      glutSolidSphere(0.8 ,8 ,8);
   glEndList();
}
