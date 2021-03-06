#ifndef OC_GRAPHICS_H


#include <stdarg.h>
#include <math.h>
#include <GL/glut.h>    /*for Linux*/
//#include <GLUT/glut.h>    /*for macos*/
#include <time.h>
#include "../oc_kernel/oc_kernel.h"


extern object* root;

/* globales d'affichage */

int cpt;
char presse,calc;
int anglex,angley,xold,yold;

float size_cell;
float size_cube;

/* structure de coordonnée 2D pour affichage*/
typedef struct {
  double x,y;
} Point;







/* Prototypes */

void draw_text(float x, float y, const char *fmt, ...);
void affichage();
void clavier(unsigned char touche, int x, int y);
void reshape(int x,int y);
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void idle();


#endif
#define OC_GRAPHICS_H
