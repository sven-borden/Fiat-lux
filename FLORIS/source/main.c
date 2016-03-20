#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "modele.h"

int main(int argc, const char * argv[])
{
	modele_lecture(argv[2]);
    printf("*****************Après modèle lecture***************** \n");
    error_success();
    return 0;
}
