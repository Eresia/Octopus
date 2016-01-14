#ifndef GRAPHIC
#define GRAPHIC

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

#include <GL/glut.h>    /*for Linux*/
/*#include <GLUT/glut.h>*/   /*for macos*/

#include "../oc_kernel/Object.h"

#define SIZE_CUBE 60
#define SIZE_CELL 6
//#define NB_CELL_MAX (SIZE_CUBE/SIZE_CELL) * (SIZE_CUBE/SIZE_CELL) * (SIZE_CUBE/SIZE_CELL)
#define NB_CELL_MAX 1000

typedef struct MoveInfo MoveInfo;
struct MoveInfo{
	int angleX;
	int angleY;
	int xOld, yOld;
	bool press;
};

void display();
void draw_text(float x, float y, const char *fmt, ...);
void reshape(int x,int y);
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void printCubes(ItemObject item, int i);

#endif
