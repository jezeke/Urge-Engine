#ifndef INIT_THREADS
#define INIT_THREADS

#include "simulation.h"

#undef List_DLINKED
#undef List_DENDED
#include "list.h" //single-linked, single-ended list

typedef struct renderData
{
  int hoz;
  int vert;
  int fps;
  CellMatrix *grid;
  List *cellList;
  int returnCode;
} renderData;

/*typedef struct simData
{
  CellMatrix *grid;
  List *cellList;
  int returnCode;
} simulationData; */

#endif
