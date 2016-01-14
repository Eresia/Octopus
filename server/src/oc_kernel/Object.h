#ifndef OBJECT
#define OBJECT

#include <stdio.h>
#include <stdlib.h>

#include "../usefull/Usefull.h"

#define MAX_DATA_IN_OBJECTS 100
#define SPEED_TIMEOUT 1

/*An object representation*/
typedef struct Object Object;
struct Object{
	int id;
	void** data;
	int sizeData;
	int activity;
	int timeout;
};

/*An item of a chained list*/
typedef struct ItemObject_struct* ItemObject;
struct ItemObject_struct{
	Object* object;
	struct ItemObject_struct* next;
};

/*A chained list of objects*/
typedef struct ListObject ListObject;
struct ListObject{
	ItemObject firstObject;
	int size;
};

/*public functions on ListObject*/
ListObject* initListObject();
bool isListVoid(ListObject* list);

void addObject(ListObject* list, Object* obj);
void updateData(ListObject* list, int id, void* data, int activity);
void removeObject(ListObject* list, Object* obj);
void removeObjectById(ListObject* list, int id);
bool isObjectInList(ListObject* list, Object* obj);
bool isObjectInListById(ListObject* list, int id);
Object* getObjectById(ListObject* list, int id);
void updateTimeouts(ListObject* list);
void printListObject(ListObject* list);

/*private functions on Objects*/
Object* createObject(int id, void* data, int activity);
void printObject(Object* obj);
void updateObject(Object* obj, void* data, int activity);

/*private functions on ListObject*/
ItemObject createItem(Object* obj);

bool addObject_Item(ItemObject item, Object* obj);
bool updateData_Item(ItemObject item, int id, void* data, int activity);
bool removeObjectById_Item(ItemObject item, int id);
bool isObjectInListById_Item(ItemObject item, int id);
Object* getObjectById_Item(ItemObject item, int id);
void updateTimeouts_Item(ItemObject item);
void printListObject_Item(ItemObject item);

#endif
