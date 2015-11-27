#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../oc_graphics/oc_graphics.h"
#include "oc_kernel.h"
#include "oc_timing.h"
#include "../oc_network/oc_network.h"

#include <pthread.h>



pthread_t server;
pthread_t db;


/*object list*/
object *root;



void * refresh (void * em) {

  /*time */
  struct timeval start,checkpoint;
  long long diff;


  /*init*/
  init_object_list (&root);

  /*initializing the time reference*/
  gettimeofday(&start, 0);


  /*build_list (&root,1,"babar",1024);
  build_list (&root,2,"babar",1024);
  build_list (&root,3,"babar",1000);

  build_list (&root,1,"babar",1024);
  build_list (&root,1,"babar",1024);
  build_list (&root,13,"sxsbabar",1024);
  build_list (&root,2,"babare",1024);*/

  print_list (root);
  printf("------------------\n");

  while (1){

    gettimeofday(&checkpoint, 0);
    diff=(checkpoint.tv_sec-start.tv_sec) * 1000000L + (checkpoint.tv_usec-start.tv_usec); // calculate time elapsed

    if (diff < TASK_PERIOD ) ; /* we are toot early : do nothing*/
    else {
      gettimeofday(&start, 0); /* re-init the time reference for next calculation*/
#ifdef __GTIMETRACE
      printf("temps écoulé=%lld usec\n",diff);
#endif
      if (diff > TASK_PERIOD + TASK_DEADLINE) fprintf (stderr,"***echeance manquée \n"); /* we are too late*/
      else {  /*we are on time : do real-time stuff*/
#ifdef __GTIMETRACE
        print_list(root);
#endif
	//MUTEX LOCK sur root ici
        update_timeouts(root);
        save_json(root,"./arbor-v0.92/octopus/test2.json");
	//MUTEX UNLOCK ic, ou bien a l'intérieur des fonctions
      }


    }


  }

}



// server  : lissens UDP messages, parses and build the oblject list
// refresh : update the timeout of each message (decrease the timeout vlaue at each TIME_PERIOD step)
// glutmainloop : opengl dirty Interface

int main (int argc,char**argv){


  size_cube = 60.;
  size_cell = 6.;


  pthread_create (&server,0,oc_server,0);
  pthread_create (&db,0,refresh,0);



  /* initilisation de glut et creation de la fenetre */

  glutInit(&argc,argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(530,530);
  glutCreateWindow("Octopus");

  /* initialisation OpenGL */

  glClearColor(0,0,0,0);
  glColor3f(1,1,1);
  glPointSize(1);
  glEnable(GL_DEPTH_TEST);

  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);


  /* non graphical global goes here */



  /* main loop */
   glutMainLoop();



return 0;






}
