/* P.Andry 2014 */

 #include <stdlib.h>
 #include <stdio.h>
 #include "oc_graphics.h"



/* affiche la chaine fmt a partir des coordonnées x,y*/
void draw_text(float x, float y, const char *fmt, ...)
{
  char            buf[1024];                      //Holds Our String
  char            *text = buf;
  va_list         ap;                             // Pointer To List Of Arguments

  if (fmt == NULL)                                // If There's No Text
    return;                                 // Do Nothing

  va_start(ap, fmt);                              // Parses The String For Variables
  vsprintf(text, fmt, ap);                    // And Converts Symbols To Actual Numbers
  va_end(ap);                                     // Results Are Stored In Text

  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  glRasterPos2f(x, y);
  while (*text)
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text++);

  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}







void affichage() {
  //int i,ic,deb;
  int i;
  float x,y;

    object *finger;


    i = 0;
    finger = root;

  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glScalef(0.016,0.016,0.016);
  //glTranslatef(0,-10,0);
  glRotatef(-angley,1,0,0);
  glRotatef(-anglex,0,1,0);

  glColor3f(0.8,0.8,1.0);


  /*affichage du référentiel*/

  glColor4f(0.55,0.55,0.55,0.5);
  glutWireCube(size_cube);


  //    glBegin(GL_POINTS);
  //  glPointSize(2.0);

  while (finger != NULL){

    glColor3f(0.6*(float) (finger->timeout)/1024.,0.6*(float) (finger->timeout)/1024.,(float) (finger->timeout)/1024. );
    draw_text(-1.,0.9-(float)i/18,"ID: %d value : %d",finger->ID,finger->activity);
    glPushMatrix();
    //    glTranslated(finger->x,finger->y,finger->z);

    x=(finger->ID%10)*size_cell-27.;
    y=(finger->ID/10)*size_cell-27.;
    glTranslated(x,y,-27.);

    glutSolidCube((float) ((finger->activity)/1024*size_cell)-0.6);
    glPopMatrix();


    // glVertex3f(finger->x,finger->y,finger->z);
     // draw_text(finger->x,finger->y,"ID: %d name= %s",finger->ID,finger->name);
    //glVertex3f(0.,0.,0.);
    finger = finger->next;
    i++;
     }


      // glEnd();


      //glFlush();


  /* On echange les buffers */
  glutSwapBuffers();
}



void idle(){


  if(calc){


    cpt++;

    }

    glutPostRedisplay();
}



void clavier(unsigned char touche,int x,int y) {
  //int i;
  switch(touche) {
  case 'p':
    calc=!calc;
    //if(calc) calc=0; else calc=1;
    break;

  case 'q': /* la touche 'q' permet de quitter le programme */
    exit(0);
  } /* switch */

} /* clavier */




void reshape(int x,int y) {
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);
} /* reshape */



/* getion des boutons de  la souris*/
void mouse(int bouton,int etat,int x,int y) {
  /* si on appuie sur la bouton de gauche */
  if (bouton==GLUT_LEFT_BUTTON && etat ==GLUT_DOWN) {
    presse=1; // vrai
    xold=x;   // sauvegarde de la position de la souris
    yold=y;
  }

  /* si on relache la souris */
  if (bouton==GLUT_LEFT_BUTTON && etat ==GLUT_UP) {
    presse=0; // faux
  }
} /* mouse */



/*gestion des mouvements de la souris */
void mousemotion(int x,int y) {
  if (presse) { /* si le bouton gauche est presse */
    /* on mofifie les angles de rotation de l'objet en fonction de la position actuelle de la souris et de la derniere position sauvegard?e */
    anglex=anglex+(x-xold);
    angley=angley+(y-yold);
    glutPostRedisplay();
  }

  xold=x; /* sauvegarde des valeurs courante des positions de la souris */
  yold=y;
} /* mousemotion */
