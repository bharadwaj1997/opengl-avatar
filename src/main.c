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
#include <time.h>

#include "../headers/frame.h"
#include "../headers/head.h"
#include "../headers/arm.h"
#include "../headers/chest.h"
#include "../headers/foot.h"
#include "../headers/hand.h"
#include "../headers/leg.h"
#include "../headers/neck.h"
#include "../headers/shoulder.h"
#include "../headers/chair.h"
#include "../headers/neck.h"
#include "../headers/hat.h"
#include "../headers/buttocks.h"


#define    windowWidth 800
#define    windowHeight 800


#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1

#define true  1
#define false 0

#define KEY_ESC 27

#define PI 3.1415926535898

#define position_Ini 0.0
#define WALK 0.50
#define RUN 1

float t = 0.f;
float delta = 10.f;
float delta_scratch = -56;
float k = 0.001f;
float K = 0.002f;
int IdleRunning = true;
int TraceEcran = false;
int RangFichierStockage = 0;
float positionX = position_Ini;
float positionZ = position_Ini;
float tempX, tempZ;
float chaiseX = 20;
float chaiseZ = 20;
float widthSeat = 6;
float rayonTapis = 20;
double theta = 0.0;
float angleSeat = 0;
double countI=0, countJ = 0, countK = 0;
int i=0, j=0;
float position = position_Ini;

#define NB_LISTS 14

enum lists{		dl_init	 	= 0,
					dl_head 		= 1,
					dl_chest 	= 2,
					dl_neck 		= 3,
					dl_hand 		= 4,
					dl_arm 		= 5,
					dl_calf 		= 6,
					dl_thigh		= 7,
					dl_foot 		= 8,
					dl_forearm 	= 9,
					dl_frame		= 10,
					dl_pectoral	= 11,
					dl_chair		= 12,
					dl_shoulder	= 13,
					dl_hat		= 14,
					dl_buttocks	= 15
			};
int dl_lists[NB_LISTS];

enum key_state {NOTPUSHED, PUSHED = 1} keyarr[127];

enum state {run = 0, walk = 1, pause = 2, sitting = 4, sit = 5, getup = 6};

int state = pause;
int previous_state = pause;
int finish_mvt = 0;
int scratch;

float cam_x = 0;
float cam_y = 0;
float cam_z = 0;

float po_x = 0;
float po_y = 0;
float po_z = 0;

enum laterality{left = 0, right = 1};

float angle_Bras[2];
float angle_AvantBras[2];
float angle_Cuisse[2];
float angle_Mollet[2];

float angle_scratch[3] = {3, 3, 0};

float angle_Bras_Ini[2] = {-30.0, 15.0};
float angle_AvantBras_Ini[2] = {0.0, 15.0};
float angle_Cuisse_Ini[2] = {20.0, -20.0};
float angle_Mollet_Ini[2] = {0.0, -20.0};

float amplitude_Bras;
float amplitude_AvantBras;
float amplitude_Cuisse;
float amplitude_Mollet;
float med_Bras;
float med_AvantBras;
float med_Cuisse;
float med_Mollet;

float mvt_speed = 60;

float d_angle_r;
float d_angle_l;

int timer = 0;
int alea = 0;

static GLfloat mat_specular[] = { 1.0 , 1.0 , 1.0 , 1.0 };
static GLfloat mat_ambientanddiffuse[] = { 0.4, 0.4 , 0.0 , 1.0 };
static GLfloat mat_shininess[] = { 20.0};

static GLfloat light_position0[] = { 15.0 , 15.0 , 15.0 , 0.0 };
static GLfloat light_position1[] = { 15.0 , 15.0 , -15.0 , 0.0 };

static GLfloat ambient_light0[] = { 0.0 , 0.0 , 0.0 , 0.0 };
static GLfloat diffuse_light0[] = { 0.4 , 0.4 , 0.4 , 1.0 };
static GLfloat specular_light0[] = { 0.1 , 0.1 , 0.1 , 0.1 };

static GLfloat ambient_light1[] = { 0.20 , 0.20 , 0.20 , 1.0 };
static GLfloat diffuse_light1[] = { 0.2 , 1.0 , 1.0 , 1.0 };
static GLfloat specular_light1[] = { 0.2 , 1.0 , 1.0 , 1.0 };

int Step = 0;
int latence =5;

void init_scene();
void render_scene();
void init_gl_ids();
GLvoid initGL();
GLvoid idle();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid window_keyup(unsigned char key, int x, int y);
GLvoid window_timer();


int main(int argc, char **argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("openGL ET3");

	initGL();
	init_scene();

	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	glutKeyboardFunc(&window_key);
	glutIdleFunc(&idle);
	glutKeyboardUpFunc(&window_keyup);
	glutTimerFunc(latence, &window_timer, Step);

	glutMainLoop();

	return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque

GLvoid initGL()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// propri�t�s mat�rielles des objets
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambientanddiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0.2, 0.22, 0.25, ALPHA);
	// z-buffer
	glEnable(GL_DEPTH_TEST);
}

void init_scene()
{
	int i;
	draw_frame(dl_frame);

	draw_head(dl_head);
	draw_neck(dl_neck);
	draw_hat(dl_hat);
	draw_chest(dl_chest);

	draw_arm(dl_arm);
	draw_forearm(dl_forearm);
	draw_shoulder(dl_shoulder);
	draw_hand(dl_hand);

	draw_calf(dl_calf);
	draw_thigh(dl_thigh);
	draw_buttocks(dl_buttocks);
	draw_foot(dl_foot);

	draw_Seat(dl_chair);

	amplitude_Bras = .5 * (angle_Bras_Ini[ right ] - angle_Bras_Ini[ left ]);
	amplitude_AvantBras = .5 * (angle_AvantBras_Ini[ right ] - angle_AvantBras_Ini[ left ]);
	amplitude_Cuisse = .5 * (angle_Cuisse_Ini[ right ] - angle_Cuisse_Ini[ left ]);
	amplitude_Mollet = .5 * (angle_Mollet_Ini[ right ] - angle_Mollet_Ini[ left ]);
	med_Bras = .5 * (angle_Bras_Ini[ right ] + angle_Bras_Ini[ left ]);
	med_AvantBras = .5 * (angle_AvantBras_Ini[ right ] + angle_AvantBras_Ini[ left ]);
	med_Cuisse = .5 * (angle_Cuisse_Ini[ right ] + angle_Cuisse_Ini[ left ]);
	med_Mollet = .5 * (angle_Mollet_Ini[ right ] + angle_Mollet_Ini[ left ]);

	for(i = 0; i < 127; i++) {
		keyarr[i] = NOTPUSHED;
	}
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display()
{
	double speed;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(-positionX+20+cam_x, cam_y, positionZ+20+cam_z, -positionX, po_y, positionZ, 0, 1, 0);

	if(finish_mvt) {
		previous_state = pause;
		state = pause;
		delta-=mvt_speed;
		speed = fabs(WALK*(cos(delta*K)+sin(delta*K+PI)));
		if(speed < 0.6) {
			speed += 0.2;
		}
		positionZ += speed * cos(theta);
		positionX -= speed * sin(theta);
		if(fabs(cos(K*delta)) < 0.99)
		{
			finish_mvt = 1;
		}
		else {
			finish_mvt = 0;
		}
	}
	if(state == sitting)
	{
		if(angleSeat < 90)
		{
			angleSeat += 10;
		}
	}
	else if(state == sit)
	{
		if(keyarr['z'])
		{
			previous_state = state;
			state = getup;
		}
	 }
	 else if(state == getup)
	{
		if(angleSeat > 0)
		{
			angleSeat -= 10;
		}
	}
	else {
		if(scratch) {
			delta_scratch-=100;
		}
		if((keyarr['z'] || state == walk)) {
			tempZ = positionZ + speed * cos(theta);
			tempX = positionX - speed * sin(theta);

			if((tempX > chaiseX - 4) && (tempX < chaiseX + widthSeat +4)
				&& (tempZ > chaiseZ + widthSeat - 1) && (tempZ < chaiseZ + widthSeat +6)) {
					positionX = chaiseX + widthSeat/2;
					positionZ = chaiseZ + widthSeat/2 + 4;
					previous_state = state;
					state = sitting;
					theta = 0;
				}
				else {
					previous_state = state;
					scratch = 0;
					state = walk;
					delta-=mvt_speed;
					speed = fabs(WALK*(cos(delta*K)+sin(delta*K+PI)));
					if(speed < 0.6) {
						speed += 0.2;
					}
					positionZ += speed * cos(theta);
					positionX -= speed * sin(theta);
				}
			}

			if(keyarr['e'] || state == run) {
				tempZ = positionZ + speed * cos(theta);
				tempX = positionX - speed * sin(theta);

				if((tempX > chaiseX - 4) && (tempX < chaiseX + widthSeat +4)
					&& (tempZ > chaiseZ + widthSeat - 1) && (tempZ < chaiseZ + widthSeat +6)){

						positionX = chaiseX + widthSeat/2;
						positionZ = chaiseZ + widthSeat/2 + 4;

						previous_state = state;
						state = sitting;
					}
					else {
						previous_state = state;
						scratch = 0;
						state = run;
						delta-=mvt_speed;
						speed = fabs(RUN*(cos(delta*K)+sin(delta*K+PI)));
						if(speed < 0.8) {
							speed += 0.8;
						}
						positionZ += speed * cos(theta);
						positionX -= speed * sin(theta);
					}
				}

				if(!keyarr['e'] && !keyarr['z'] && timer == 0) {
					previous_state = state;
					state = pause;
				}

				if(keyarr['d']) {
					theta = (theta + PI/48);
				}
				if(keyarr['q']) {
					theta = (theta - PI/48);
				}
			}

			if(keyarr['l']) {
				cam_x++;
			}
			if(keyarr['j']) {
				cam_x--;
			}
			if(keyarr['i']) {
				cam_y++;
			}
			if(keyarr['k']) {
				cam_y--;
			}
			if(keyarr['u']) {
				cam_z++;
			}
			if(keyarr['o']) {
				cam_z--;
			}

			render_scene();
			glFlush();
}

// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1.333, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

GLvoid idle() {
	glutPostRedisplay();
}

// fonction de call-back pour la gestion des �v�nements clavier

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
		case KEY_ESC:
			exit(1);
			break;
		case ' ':
			if(!keyarr[' ']) {
				keyarr[' '] = PUSHED;
			}
			else {
				keyarr[' '] = NOTPUSHED;
			}
			break;
		}
		if(!keyarr[' ']) {
			if(key == 'z') {
				keyarr['z'] = PUSHED;
			}
			if(key == 'e') {
				keyarr['e'] = PUSHED;
			}
			if(key == 'd') {
				keyarr['d'] = PUSHED;
			}
			if(key == 'q') {
				keyarr['q'] = PUSHED;
			}
		}

		if(key == 'i') {
			keyarr['i'] = PUSHED;
		}
		if(key == 'k') {
			keyarr['k'] = PUSHED;
		}

		if(key == 'j') {
			keyarr['j'] = PUSHED;
		}
		if(key == 'l') {
			keyarr['l'] = PUSHED;
		}
		if(key == 'u') {
			keyarr['u'] = PUSHED;
		}
		if(key == 'o') {
			keyarr['o'] = PUSHED;
		}
}

GLvoid window_keyup(unsigned char key, int x, int y)
{
	if(key == 'z') {
		keyarr['z'] = NOTPUSHED;
	}
	if(key == 'e') {
		keyarr['e'] = NOTPUSHED;
	}
	if(key == 'd') {
		keyarr['d'] = NOTPUSHED;
	}
	if(key == 'q') {
		keyarr['q'] = NOTPUSHED;
	}

	if(key == 'i') {
		keyarr['i'] = NOTPUSHED;
	}
	if(key == 'k') {
		keyarr['k'] = NOTPUSHED;
	}

	if(key == 'j') {
		keyarr['j'] = NOTPUSHED;
	}
	if(key == 'l') {
		keyarr['l'] = NOTPUSHED;
	}

	if(key == 'u') {
		keyarr['u'] = NOTPUSHED;
	}
	if(key == 'o') {
		keyarr['o'] = NOTPUSHED;
	}
}



GLvoid window_timer()
{
	timer --;
	if(timer < 0) {
		timer = 0;
	}
	double x;

	if(state == run) {
		angle_Bras[right] = sin(K*delta)*30-15;
		angle_AvantBras[right] = sin(K*delta)*35+15;
		if(angle_AvantBras[right] < 0) {
			angle_AvantBras[right] = 0;
		}
		angle_Bras[left] = -sin(K*delta)*30-15;
		angle_AvantBras[left] = -sin(K*delta)*35+15;
		if(angle_AvantBras[left] < 0) {
			angle_AvantBras[left] = 0;
		}

		angle_Cuisse[right] = sin(K*delta)*50-10;
		angle_Mollet[right] = sin(K*delta)*80;
		if(angle_Mollet[right] > 0) {
			angle_Mollet[right] = 0;
		}
		else {
			angle_Mollet[right] = sin(K*delta)*40-40;
		}

		angle_Cuisse[left] = -sin(K*delta)*50-10;
		angle_Mollet[left] = -sin(K*delta)*80;
		if(angle_Mollet[left] > 0) {
			angle_Mollet[left] = 0;
		}
		else {
			angle_Mollet[left] = -sin(K*delta)*40-40;
		}
	}
	else if(state == walk || finish_mvt == 1) {
		x = K*delta;
		angle_Bras[right] = sin(K*delta)*15-15;
		angle_AvantBras[right] = sin(K*delta)*10+15;
		angle_Bras[left] = -sin(K*delta)*15-15;
		angle_AvantBras[left] = -sin(K*delta)*10+15;

		angle_Cuisse[right] = sin(K*delta)*30;
		angle_Mollet[right] = sin(K*delta)*20-10;
		if(angle_Mollet[right] > 0) {
			angle_Mollet[right] = 0;
		}
		else if(angle_Mollet[right] < 0 && angle_Mollet[right] > -20) {
			angle_Mollet[right] += -15;
		}
		angle_Cuisse[left] = -sin(K*delta)*30;
		angle_Mollet[left] = -sin(K*delta)*20-10;
		if(angle_Mollet[left] > 0) {
			angle_Mollet[left] = 0;
		}
		else if(angle_Mollet[left] < 0 && angle_Mollet[left] > -20) {
			angle_Mollet[left] += -15;
		}
	}
	else if(state == sitting)
	{
		angle_Cuisse[right] = angleSeat;
		angle_Cuisse[left] = angleSeat;
		angle_Mollet[right] = -angleSeat;
		angle_Mollet[left] = -angleSeat;
	}
	else if(state == sit)
	{
		angle_Cuisse[right] = angleSeat;
		angle_Cuisse[left] = angleSeat;
		angle_Mollet[right] = -angleSeat;
		angle_Mollet[left] = -angleSeat;
	}
	else if(state == getup)
	{
		angle_Cuisse[right] = angleSeat;
		angle_Cuisse[left] = angleSeat;
		angle_Mollet[right] = -angleSeat;
		angle_Mollet[left] = -angleSeat;
	}

	if(scratch && state == pause) {
		if(fabs(110-fabs(angle_scratch[0])) < 2 && fabs(140-fabs(angle_scratch[1])) < 2) {
			angle_scratch[0] = 0;
			angle_scratch[1] = 0;
			scratch = 0;
		}
		else {
			angle_scratch[0] = fabs(sin(K*delta_scratch/12)*25*5)-110;
			angle_scratch[1] = fabs(sin(K*delta_scratch/12)*25*5)-140;
		}
	}

	glutTimerFunc(latence,&window_timer,++Step);
	glutPostRedisplay();
}

void init_gl_ids() {
	int i;
	dl_lists[dl_init] = glGenLists(NB_LISTS);
	for(i = 1; i < NB_LISTS; i++) {
		dl_lists[i] = dl_lists[dl_init] + i;
	}
}

void render_scene()
{
	glPushMatrix();
		glCallList(dl_frame);
	glPopMatrix();


   // rotation de 90 degres autour de Ox pour mettre l'axe Oz
   // vertical comme sur la figure
   glRotatef(-90, 1, 0, 0);
	glRotatef(180, 0, 0, 1);

	glPushMatrix();
		//translate vers la position de la chaise dans l'univers
		glTranslatef(chaiseX,chaiseZ,-4);
		glCallList(dl_chair);
	glPopMatrix();

   // d�placement horizontal selon l�axe Oy pour donner
	// une impression de d�placement horizontal accompagnant
   // la marche

	glTranslatef(positionX, positionZ, 0);
	glRotatef((180*theta)/PI,0,0,1);

	if(state == pause && previous_state == walk) {
		finish_mvt = 1;
	}
	else if(state == pause && previous_state == run) {
		finish_mvt = 1;
	}

	if(state == run) {
		glRotatef(sin(K*delta)*3, 0, 0, 1);
		glRotatef(-sin(K*delta)*3, 0, 1, 0);
		glRotatef(-fabs(-sin(K*delta)*2)*3, 1, 0, 0);
		glTranslatef(0, 0, -fabs(-sin(K*delta))*2);
	}
	else if(state == walk) {
		glRotatef(-sin(K*delta)*1.5, 0, 1, 0);
		glRotatef(-fabs(-sin(K*delta)*2), 1, 0, 0);
		glTranslatef(0, 0, -fabs(-sin(K*delta)));
	}
	else if(state == sitting)
	{
		countI += 0.35;
		countJ += 0.3;
		countK +=  0.25;
		i++;
	}
	else if(state == sit)
	{
		countI = 3.15;
		countJ= 2.7;
		countK= 2.25;
		i=0;
	}
	else if(state == getup)
	{
		countI -= 0.35;
		countJ -= 0.3;
		countK -= 0.25;
		i++;
	}
	else {
		glRotatef(-sin(K*delta)*1.5, 0, 1, 0);
		glRotatef(-fabs(-sin(K*delta)*2), 1, 0, 0);
		glTranslatef(0, 0, -fabs(-sin(K*delta)));
	}

	alea = rand() % 300;
	if(alea == 100) {
		scratch = 1;
	}

	if(keyarr[' '] && timer == 0) {
		alea = rand() % 4;
		if(alea == 1) {
			state = walk;
			previous_state = walk;
			timer = 200;
		}
		else if(alea == 2) {
			state = run;
			previous_state = run;
			timer = 200;
		}
		else if(alea == 3) {
			state = pause;
			previous_state = pause;
			timer = 100;
		}
	}

	if(keyarr[' '] && state != pause && timer%3 == 0) {
		alea = rand() % 3;
		if(alea == 0) {}
		else if(alea == 1) {theta = (theta + PI/48);}
		else if(alea == 2) {theta = (theta - PI/24);}
	}


	if(state == sitting || state == sit || state == getup)
	{
		glTranslatef(0,0,-countI);
		glPushMatrix();
			glTranslatef(0,-countJ,0);
	}

	glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		glCallList(dl_chest);
		glPopMatrix();
			glColor3f(1, 0.8, 0.6);
			glPushMatrix();
				glTranslatef(0,0,11);
				glCallList(dl_head);
				glTranslatef(1, 0, 0);
				glCallList(dl_neck);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, 0, 9.5);
				glRotatef(-90, 0, 1, 0);
				if(!scratch || state != pause) {
					glCallList(dl_hat);
				}
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,0,0.3);
				glRotatef(180,1.0,0,0);
				glCallList(dl_buttocks);
			glPopMatrix();

			if(state == sitting || state == getup) {
				glTranslatef(0,0,-countK);
				glTranslatef(0,0,countI);
			}
			else if(state == sit) {
				glTranslatef(0, 0,-countK);
				glTranslatef(0,0,countI);
				angle_Cuisse[left]=70;
				angle_Cuisse[right]=70;
			}

			glColor3f(0, 0, 1.0);
			glPushMatrix();
				glTranslatef(1.25,0,0);
				glRotatef(angle_Cuisse[left],1.0,0,0);
				glCallList(dl_thigh);

				glPushMatrix();
					glTranslatef(3.5,0,0);
					glRotatef(angle_Mollet[left],0,0,1);
					glCallList(dl_calf);
					glTranslatef(3.2, 0.7, 0);
					glRotatef(10, 1, 0, 0);
					glCallList(dl_foot);
				glPopMatrix();
			glPopMatrix();

			if(state == sitting || state == sit || state == getup) {
				glTranslatef(0, 0 ,countK);
				glTranslatef(0,0,-countI);
			}

			glPushMatrix();
				glTranslatef(0,0,0.3);
				glRotatef(180,1.0,0,0);
				glRotatef(180,0,1,0);
				glCallList(dl_buttocks);
			glPopMatrix();

			if(state == sitting || state == sit || state == getup) {
				glTranslatef(0, 0 ,-countK);
				glTranslatef(0,0,countI);
			}

			glPushMatrix();
				glTranslatef(-1.25,0,0);
				glRotatef(angle_Cuisse[right],1.0,0,0);
				glCallList(dl_thigh);
				glPushMatrix();
					glTranslatef(3.5,0,0);
					glRotatef(angle_Mollet[right],0,0,1);
					glCallList(dl_calf);
					glTranslatef(3.2, 0.7, 0);
					glRotatef(10, 1, 0, 0);
					glCallList(dl_foot);
				glPopMatrix();
			glPopMatrix();

			if(state == sitting || state == sit || state == getup) {
				glTranslatef(0,0,countK);
			}
			if(state == sitting || state == sit || state == getup) {
				glTranslatef(0,0,-countI);
			}

			glPushMatrix();
				glTranslatef(3.8,0,6.5);
				glRotatef(180,1,0,0);
				glRotatef(180, 0, 1, 0);
				glCallList(dl_shoulder);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(3.5,0,6.9);
				glRotatef(angle_Bras[right],1.0,0,0);
				if(scratch && state == pause) { glRotatef(angle_scratch[0], 0, 1, 0);}
				glColor3f(1, 0, 0);
				glCallList(dl_arm);

				glPushMatrix();
					glTranslatef(3.7, -0.1, 0);
					glColor3f(1, 0.8, 0.6);
					glRotatef(angle_AvantBras[right],0,0,1);
					if(scratch && state == pause) { glRotatef(angle_scratch[1], 0, 1, 0); glRotatef(angle_scratch[2], 0, 0, 1);}
					glCallList(dl_forearm);
					glTranslatef(3, 0, 0);
					glCallList(dl_hand);
					if(scratch && state == pause) {
						glRotatef(-80, 0, 1, 0);
						glTranslatef(0, 0, -3);
						glCallList(dl_hat);
					}
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-3.8,0,6.5);
				glRotatef(180,1.0,0,0);
				glCallList(dl_shoulder);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-3.5,0,6.9);
				glRotatef(angle_Bras[left],1.0,0,0);
				glColor3f(1.0, 0, 0);
				glCallList(dl_arm);
				glPushMatrix();
					glTranslatef(3.7, -0.1, 0);
					glColor3f(1, 0.8, 0.6);
					glRotatef(angle_AvantBras[left],0,0,1);
					glCallList(dl_forearm);
					glTranslatef(3, 0, 0);
					glCallList(dl_hand);
				glPopMatrix();
			glPopMatrix();

			if(state == sitting) {
				glTranslatef(0,0,countI);
				if(i == 9) {
					previous_state = state;
					state = sit;
				}
			}
			else if(state == sit) {
				glTranslatef(0,0,countI);
				countI=0;
			}
			else if(state == getup) {
				glTranslatef(0,0,countI);
				if(i > 9) {
					previous_state = state;
					state = pause;
					i=0;
					positionX = chaiseX + widthSeat/2;
					positionZ = chaiseZ + widthSeat + 8;
				}
			}

			if(state == sit || state == sitting || state == getup) {
				glPopMatrix();
			}

			glutSwapBuffers();
}
