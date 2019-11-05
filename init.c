#include <stdlib.h>
#include <pthread.h>

#include "logging.h"
#include "simulation.h"
#include "render.h"
#include "init_threads.h"

#undef List_DLINKED
#undef List_DENDED
#include "list.h" //single-linked, single-ended list

void printUsage();

void initMatrix(CellMatrix *grid, unsigned int hoz, unsigned int vert);

int main(int argc, char *argv[])
{
  pthread_t render; //one is enough yeah?
  renderData *rData;
  pthread_t simulation; //TODO variable threads, timing, cell allocation, etc
  //simData *sData;

  unsigned int hozResolution, vertResolution, fps;
  CellMatrix *grid;
  List *cellList;

  if (argc != 4 && argc != 5)
  { //TODO improve argument handling
    printUsage();
    return 1;
  }

  hozResolution = atoi(argv[1]);
  vertResolution = atoi(argv[2]);
  fps = atoi(argv[3]);

  if(hozResolution <= 0 || vertResolution <= 0 || fps <= 0)
  {
    printUsage();
    return 1;
  }

  initMatrix(grid, hozResolution, vertResolution);
  //cellList = List_init();


  logging("Initializing renderer...");

  rData = malloc(sizeof(renderData));
  rData->hoz = hozResolution;
  rData->vert = vertResolution;
  rData->fps = fps;
  rData->returnCode = 0;

  pthread_create(&render, NULL, render_main, rData);


  logging("Beginning simulation...");
  //TODO sim spin-up

  //wrap up threads
  pthread_join(render, NULL);
  //pthread_join(simuation, NULL);

  //clean up
  free(rData);
  //freeMatrix(grid);
  //List_free(cellList, &free);

  if(rData->returnCode != 0 /*|| simData->returnCode != 0*/)
  {
    return -1; //executed with some error
  }

  return 0;
}

void printUsage()
{
  logging("Expecting form ./urge hoz vert fps\n");
  //TODO change
}

void initMatrix(CellMatrix *grid, unsigned int hoz, unsigned int vert)
{ //grid[x][y] ; grid[hoz][vert]
  grid = malloc(sizeof(CellMatrix));
  grid->hoz = hoz;
  grid->vert = vert;
  grid->modified = 0;

  grid->matrix = malloc(sizeof(Cell)*hoz);
  for(int i = 0; i < vert; i++)
  {
    grid->matrix[i] = NULL;
  }
}
