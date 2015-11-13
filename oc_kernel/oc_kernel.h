#ifndef OC_KERNEL_H


#define RESET_VALUE 1024

typedef struct object {

  int ID;      // object ID
  char name[256]; 
  int activity; // activity level [0-1024] for analogous devices
  int timeout; // presence countdown. if timeout = 0 the object is considered as unactive and deconneted
               // each heartbeat reset the the timout to RESET_VALUE

  float x;  //graphical coordinates
  float y;
  float z;
 
  struct object *next;  //link baby, link

}object;



void print_object(object*);
object* create_object_from_data(int, char*, int);

void init_object_list (object **);
void add_object(object **,object *);
int search_object(object*,int,char*,int); // search if number nb and char* name are already present in the list
int remove_object (object **,int); //remove object with ID 
void print_list(object *);
int build_list(object **, int , char *, int );
void update_timeouts(object*); 


void save_json(object *,char *m);

#endif
#define OC_KERNEL_H
