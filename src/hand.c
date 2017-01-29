#include "../headers/hand.h"



void draw_hand(int dl_hand) {
   glNewList(dl_hand, GL_COMPILE);
   glColor3f(1, 0, 0);
      glScalef(1.1, 1, 0.7);
      glutSolidSphere(0.8 ,8 ,8);
   glEndList();
}
