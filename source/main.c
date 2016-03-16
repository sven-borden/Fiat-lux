#include <stdio.h>
#include <stdlib.h>
#include "modele.h"


int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		if(modeleLecture(argv[1]) == 1)
			EXIT_FAILURE;
		else
			EXIT_SUCCESS;
	}
	
	return 0;
}
