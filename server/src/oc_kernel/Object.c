#include "Object.h"

/*=============================================================================public functions on ListObject*/
ListObject* initListObject(){
	ListObject* list = malloc(sizeof(ListObject));
	list->size = 0;
	list->firstObject = NULL;
	return list;
}


void addObject(ListObject* list, Object* obj){
	if(list->firstObject == NULL){
		list->firstObject = createItem(obj);
		list->size++;
		#ifdef DEBUG
			printf("Object added\n");
		#endif
	}
	else{
		if(addObject_Item(list->firstObject, obj)){
			list->size++;
			#ifdef DEBUG
				printf("Object added\n");
			#endif
		}
		#ifdef DEBUG
		else{
			printf("Object not added\n");
		}
		#endif
	}
}

void updateData(ListObject* list, int id, void* data, int activity){
	if(list->firstObject == NULL){
		list->firstObject = createItem(createObject(id, data, activity));
		list->size++;
		#ifdef DEBUG
			printf("List update\n");
		#endif
	}
	else{
		if(updateData_Item(list->firstObject, id, data, activity)){
			list->size++;
		}
	}
}

void removeObject(ListObject* list, Object* obj){
	removeObjectById(list, obj->id);
}

void removeObjectById(ListObject* list, int id){
	if(list->firstObject != NULL){
		if(list->firstObject->object->id == id){
			ItemObject next = list->firstObject->next;
			free(list->firstObject);
			list->firstObject = next;
			list->size--;
			#ifdef DEBUG
				printf("Object removed\n");
			#endif
		}
		else{
			if(removeObjectById_Item(list->firstObject, id)){
				list->size--;
				#ifdef DEBUG
					printf("Object removed\n");
				#endif
			}
			#ifdef DEBUG
			else{
				printf("Object not removed\n");
			}
			#endif
		}
	}
	#ifdef DEBUG
	else{
		printf("Object not removed\n");
	}
	#endif
}

bool isObjectInList(ListObject* list, Object* obj){
	return isObjectInList(list, obj);
}

bool isObjectInListById(ListObject* list, int id){
	return isObjectInListById_Item(list->firstObject, id);
}

Object* getObjectById(ListObject* list, int id){
	return getObjectById_Item(list->firstObject, id);
}

void updateTimeouts(ListObject* list){
	updateTimeouts_Item(list->firstObject);
}

void printListObject(ListObject* list){
	printf("%d objects : \n", list->size);
	printListObject_Item(list->firstObject);
}

/*=============================================================================private functions on Objects*/
Object* createObject(int id, void* data, int activity){
	Object* obj = malloc(sizeof(Object));
	obj->id = id;
	obj->data = malloc(MAX_DATA_IN_OBJECTS*sizeof(Object));
	obj->data[0] = data;
	obj->activity = activity;
	obj->timeout = TIMEOUT_MAX;
	obj->sizeData = 1;
	return obj;
}

void printObject(Object* obj){
	int i;
	printf("Obj - id : %d, activity : %d, timeout : %d\n", obj->id, obj->activity, obj->timeout);
	for(i = 0; i < obj->sizeData; i++){
		printf("--- %s\n", (char*) obj->data[i]);
	}
}

void updateObject(Object* obj, void* data, int activity){
	obj->data[obj->sizeData] = data;
	obj->activity = activity;
	obj->timeout = TIMEOUT_MAX;
	obj->sizeData++;
}

/*=============================================================================private functions on ListObject*/
ItemObject createItem(Object* obj){
	ItemObject item = malloc(sizeof(struct ItemObject_struct));
	item->object = obj;
	item->next = NULL;
	return item;
}

bool addObject_Item(ItemObject item, Object* obj){
	if(item == NULL){
		return false;
	}

	if(item->next == NULL){
		item->next = createItem(obj);
		return true;
	}
	else{
		return addObject_Item(item->next, obj);
	}
}

bool updateData_Item(ItemObject item, int id, void* data, int activity){
	if(item == NULL){
		return false;
	}

	if(item->object->id == id){
		updateObject(item->object, data, activity);
		return false;
	}
	else if(item->next == NULL){
		item->next  = createItem(createObject(id, data, activity));
		#ifdef DEBUG
			printf("Object update\n");
		#endif
		return true;
	}
	else{
		return updateData_Item(item->next, id, data, activity);
	}
}

bool removeObjectById_Item(ItemObject item, int id){
	if((item == NULL) || (item->next == NULL)){
		return false;
	}

	if(item->next->object->id == id){
		ItemObject next = item->next->next;
		free(item->next);
		item->next = next;
		return true;
	}
	else{
		return removeObjectById_Item(item->next, id);
	}
}

bool isObjectInListById_Item(ItemObject item, int id){
	if(item == NULL){
		return false;
	}

	if(item->object->id == id){
		return true;
	}
	else{
		return isObjectInListById_Item(item->next, id);
	}
}

Object* getObjectById_Item(ItemObject item, int id){
	if(item == NULL){
		return NULL;
	}

	if(item->object->id == id){
		return item->object;
	}
	else{
		return getObjectById_Item(item->next, id);
	}
}

void updateTimeouts_Item(ItemObject item){
	if(item != NULL){
		item->object->timeout -= SPEED_TIMEOUT;
		updateTimeouts_Item(item->next);
	}
}

void printListObject_Item(ItemObject item){
	if(item != NULL){
		printObject(item->object);
		printListObject_Item(item->next);
	}
}
