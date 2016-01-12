#ifndef USEFULL
#define USEFULL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Boolean utilisation*/
typedef enum bool bool;
enum bool{
	false = 0, true = 1
};

#endif


//Clean a descriptor after a "fgets"
void clean(const char *buffer, FILE *fp);

//Return if a string begin by another
bool startsWith(const char * string, const char * test);

//Take sizeMax char in string and remove char in toRemove
char* take_begin(char* string, int sizeMax, char* toRemove, int sizeToRemove);
