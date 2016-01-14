#ifndef WINDOW
#define WINDOW

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include <GL/glut.h>    /*for Linux*/
/*#include <GLUT/glut.h>*/   /*for macos*/

#include "Graphic.h"
#include "../oc_kernel/Object.h"

/*typedef struct WindowInfo WindowInfo;
struct WindowInfo{
	int *argc;
	char** argv;
};*/

void* launch_graphic(void* isEnd_void);

#endif
