#include "Window.h"

void* launch_graphic(void* isEnd_void){

	bool* isEnd = (bool*) isEnd_void;

	/*WindowInfo* info = (WindowInfo*) info_void;*/
	/*glutInit(info->argc, info->argv);*/

	int* argc = malloc(sizeof(int));
	char** argv;
	*argc = 1;
	argv = malloc(*argc * sizeof(char*));

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(530,530);
	glutCreateWindow("Octopus");

	/* initialisation OpenGL */

	glClearColor(0,0,0,0);
	glColor3f(1,1,1);
	glPointSize(1);
	glEnable(GL_DEPTH_TEST);

	/* Rappel fonctions */
	glutDisplayFunc(display);
	/*glutKeyboardFunc(clavier);*/
	glutReshapeFunc(reshape);
	/*glutIdleFunc(idle);*/
	glutMouseFunc(mouse);
	glutMotionFunc(mousemotion);

	/* main loop */
	glutMainLoop();

	*isEnd = true;
	pthread_exit(NULL);
}
