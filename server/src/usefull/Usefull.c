#include "Usefull.h"

void clean(const char *buffer, FILE *fp)
{
    char *p = strchr(buffer,'\n');
    if (p != NULL)
    *p = 0;
    else
    {
        int c;
        while ((c = fgetc(fp)) != '\n' && c != EOF);
    }
}

bool startsWith(const char *string, const char *test) {
    size_t lenTest = strlen(test),
           lenString = strlen(string);
    return lenString < lenTest ? false : strncmp(test, string, lenTest) == 0;
}

char* take_begin(char* string, int sizeMax, char* toRemove, int sizeToRemove){
	int i, j;
	char* result = calloc(sizeMax, sizeof(char));
	for(i = 0; i < sizeMax; i++){
		for(j = 0; j < sizeToRemove; j++){
			if(string[i] == toRemove[j]){
				return result;
			}
		}
		result[i] = string[i];
	}
	return result;
}
