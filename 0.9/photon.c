#include "photon.h"
#include "tools.h"
#include "constantes.h"

typedef struct Photon PHOTON

struct Photon
{
    POINT x;
    POINT y;
    double alpha;  
};

static PHOTON tab_r[MAX_RENDU1];

