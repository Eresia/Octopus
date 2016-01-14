#include "Graphic.h"

extern MoveInfo* VAR_MOVE_INFO;
extern ListObject* VAR_LIST_OBJECT;

void display(){

	MoveInfo* move = VAR_MOVE_INFO;

	/* Clear the srceen */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glScalef(0.016,0.016,0.016);
	//glTranslatef(0,-10,0);
	glRotatef(-move->angleX,1,0,0);
	glRotatef(-move->angleY,0,1,0);

	glColor3f(0.8,0.8,1.0);

	/*affichage du référentiel*/

	glColor4f(0.55,0.55,0.55,0.5);
	glutWireCube(SIZE_CUBE);
	printCubes(VAR_LIST_OBJECT->firstObject, 0);
	glutSwapBuffers();
}

void reshape(int x,int y) {
	if (x<y){
		glViewport(0,(y-x)/2,x,x);
	}
	else{
		glViewport((x-y)/2,0,y,y);
	}
} /* reshape */



/* getion des boutons de  la souris*/
void mouse(int bouton,int etat,int x,int y) {

	MoveInfo* move = VAR_MOVE_INFO;
	/* si on appuie sur la bouton de gauche */
	if (bouton==GLUT_LEFT_BUTTON && etat ==GLUT_DOWN) {
		move->press=1; // vrai
		move->xOld=x;   // sauvegarde de la position de la souris
		move->yOld=y;
	}

	/* si on relache la souris */
	if (bouton==GLUT_LEFT_BUTTON && etat ==GLUT_UP) {
		move->press=0; // faux
	}
} /* mouse */



/*gestion des mouvements de la souris */
void mousemotion(int x,int y) {

	MoveInfo* move = VAR_MOVE_INFO;
	if (move->press) { /* si le bouton gauche est presse */
		/* on mofifie les angles de rotation de l'objet en fonction de la position actuelle de la souris et de la derniere position sauvegard?e */
		move->angleX=move->angleX+(y-move->yOld);
		move->angleY=move->angleY+(x-move->xOld);
		glutPostRedisplay();
	}

	move->xOld=x; /* sauvegarde des valeurs courante des positions de la souris */
	move->yOld=y;
} /* mousemotion */

void printCubes(ItemObject item, int i){
	if(item != NULL){
		int x = item->object->id%NB_CELL_MAX;
		int y = (item->object->id/NB_CELL_MAX)%NB_CELL_MAX;
		int z = (item->object->id/NB_CELL_MAX)/NB_CELL_MAX;
		printf("Timeout : %d\n", item->object->timeout);
		glColor3f(0.6*(float) (item->object->timeout/item->object->activity),0.6*(float) (item->object->timeout/item->object->activity),(float) (item->object->timeout/item->object->activity) );
		#ifdef DEBUG
			draw_text(-1.,0.9-(float)i/18,"ID: %d value : %d",item->object->id,item->object->activity);
		#endif
		glPushMatrix();
		glTranslated(x*SIZE_CELL-27,y*SIZE_CELL-27,z*SIZE_CELL-27);

		glutSolidCube((float) (SIZE_CELL)-0.6);
		glPopMatrix();
		printCubes(item->next, i+1);
	}
}

/* affiche la chaine fmt a partir des coordonnées x,y*/
void draw_text(float x, float y, const char *fmt, ...)
{
	char* buf = malloc(1000*sizeof(char));                      //Holds Our String
	char *text = buf;
	va_list ap;                             // Pointer To List Of Arguments

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
	while (*text){
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text++);
	}

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
