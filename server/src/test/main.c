#include "../oc_kernel/Octopus.h"

int main(int argc, char** argv){
	ListObject* list = initListObject();
	updateData(list, 0, "data", 10000);
	updateData(list, 2, "data", 10000);
	updateData(list, 3, "data", 10000);
	updateData(list, 6, "data", 10000);
	launch_octopus(list);

	return 0;
}
