#ifndef INIT_THREADS
#define INIT_THREADS

#include "simulation.h"

#undef List_DLINKED
#undef List_DENDED
#include "list.h" //single-linked, single-ended list

typedef struct renderData
{
  unsigned int hoz;
  unsigned int vert;
  unsigned int fps;
  CellMatrix *matrix;
  List *cellList; //needed?
  int returnCode;
} renderData;

typedef struct simData
{
  CellMatrix *matrix;
  List *cellList;
  int returnCode;
} simData;

#endif
