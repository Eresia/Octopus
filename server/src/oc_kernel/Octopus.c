#include "Octopus.h"

MoveInfo* VAR_MOVE_INFO;
ListObject* VAR_LIST_OBJECT;

void launch_octopus(ListObject* list) {

	pthread_t graph;
	bool isEnd = false;

	VAR_MOVE_INFO = malloc(sizeof(MoveInfo));
	VAR_MOVE_INFO->angleX = 0;
	VAR_MOVE_INFO->angleY = 0;
	VAR_MOVE_INFO->xOld = 0;
	VAR_MOVE_INFO->yOld = 0;
	VAR_MOVE_INFO->press = false;

	VAR_LIST_OBJECT = list;

	pthread_create(&graph, NULL, launch_graphic, &isEnd);

	while(!isEnd){
		//updateTimeouts(list);
		usleep(1000);
	}

	pthread_join(graph, NULL);
}
