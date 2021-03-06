#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "oc_kernel.h"

/* P.Andry 2014*/




void init_object_list (object ** nd){
	*nd = NULL;
}



object* create_object_from_data (int nb, char* n, int v){


	object* tmp;
	int size = (int) pow(RESET_VALUE, (float) 1/3);
	tmp = (object*)malloc (sizeof(object));
	tmp->ID = nb;
	strcpy(tmp->name,n);
	tmp->activity = v;
	tmp->timeout = RESET_VALUE;



	tmp->x = nb%size;
	tmp->y = (nb/size)%size;
	tmp->z = (nb/size)/size;

	tmp->next = NULL;
	return tmp;
}



void print_object(object *o){

	if (o == NULL) perror("object not allocated");
	else {

		printf("\t %d:%s:%d:%d \n",o->ID,o->name,o->activity,o->timeout);
	}


}



void print_list (object * first){
	int count;
	object * finger;

	finger = first;
	count = 0;

	while (finger != NULL){
		print_object(finger);
		finger = finger->next;
		count ++;
	}

	printf("%d objects found \n",count);

}


//add an object to the list
void add_object(object **first,object *new){

	new->next = *first;
	*first = new;
}



// search for an object in the list.
// if the object is present, reset the time stamp and update the activiy status
// return value :
//     - 0 : the object is not found
//     - 1 :  the object is found (same ID)
//     - 2 : an object with the same name (but not the same ID) is found : suspicious
//     - 3 : the object is found (same ID and same name)

int search_object (object*first, int valID, char *oname,int oact){

	object *finger;
	finger = first;
	int flagfound =0;
	int flagsuspicious =0;

	while (finger != NULL){
		if (finger->ID == valID) {flagfound = 1; finger->timeout=RESET_VALUE;finger->activity=oact;}
		if (strcmp(finger->name,oname) == 0) flagsuspicious = 2;
		finger = finger->next;
	}


	return flagfound+flagsuspicious;

}



// try to remove objetc with ID rID from the list
// return value :
//   0 : supression by ID ok
//   1 : no supression : empty list
//   2 : no supression : object not found

int remove_object(object **first, int rID){

	object *previous;
	object *finger;

	//  int res;



	if (*first == NULL) return 1;   //empty list
	else {                          //list is not empty
		previous = *first;
		finger = (*first)->next;

		if (previous->ID == rID){  //the first element is the one to remove
			*first = previous->next;
			free(previous);
			printf("removing the first element\n");
			return 0;
		}
		//the element to remove is in the folowing
		while ((finger != NULL )&&(finger->ID != rID)){
			printf(" *** %s \n",previous->name);
			previous = finger;
			finger = finger->next;
		}
		if (finger == NULL) {  // end of the list, element not found
			printf("not found\n");
			return 2;
		}
		else { //found

			previous->next = finger->next;
			free (finger);
			printf("removing element \n");
			return 0;
		}

	}
}

// this function is the only one to append only new object in the list.
// cheks the object in the list before adding.
// return value :
//     - 0 : object added
//     - 1 : object not added

int build_list(object ** aroot, int aID, char*aname,int aact) {

	object * tmp;
	int search;

	search = search_object(*aroot,aID,aname,aact);

	if ( search == 0) {  //not found wa can add the object

		tmp = create_object_from_data(aID,aname,aact);
		add_object(aroot,tmp);
		return 0;

	}

	if ( search == 2) {  //not found, we  can add the object but warning about an object qith same name present
		printf("warning, an object with the same name was found. Adding an object with different ID but same name\n");

		tmp = create_object_from_data(aID,aname,aact);
		add_object(aroot,tmp);
		return 0;
	}
	else  return 1;

}


// decrease the timeout of each object
void update_timeouts(object *o){

	object *finger;
	finger = o;

	while (finger != NULL){
		if (finger->timeout > 0)
		finger->timeout -= SPEED_DECREASE;

		finger = finger->next;
	}
}

// deprecated, to remove.
// json & ajax sucks
void save_json(object *o, char *json_name){
	FILE* fd;
	object *finger;
	int count =0;
	fd = fopen(json_name,"w+");
	finger = o;

	fprintf(fd,"%s\n","{\"nodes\":{");

	while (finger != NULL){
		if (count >0)  fprintf(fd,",\n");
		fprintf(fd,"\"%d\":{\"color\":\"red\", \"shape\":\"dot\", \"alpha\":%f}",finger->ID,(float)(finger->timeout)/RESET_VALUE);
		finger = finger->next;
		count++;

	}
	fprintf(fd,"\n");


	fprintf(fd,"%s\n","}\n}");

	fclose(fd);

}
