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

void initMatrix(CellMatrix *matrix, const unsigned int hoz, const unsigned int vert);

void freeMatrix(CellMatrix *matrix);

int main(int argc, char *argv[])
{
  pthread_t simulation, render; //TODO variable threads, timing, cell allocation, etc

  if (argc != 4)
  { //TODO improve argument handling
    printUsage();
    return 1;
  }

  const int hozResolution = atoi(argv[1]);
  const int vertResolution = atoi(argv[2]);
  const int fps = atoi(argv[3]);

  if(hozResolution <= 0 || vertResolution <= 0 || fps <= 0)
  {
    printUsage();
    return 1;
  }

  logging("Beginning simulation...");
  simData *sData = malloc(sizeof(simData));
  sData->returnCode = 0;

  sData->matrix = malloc(sizeof(CellMatrix));
  initMatrix(sData->matrix, hozResolution, vertResolution);

  //cellList = List_init();
  //pthread_create(&simulation, NULL, simulation_main, sData);


  logging("Initializing renderer...");
  renderData *rData = malloc(sizeof(renderData));
  rData->hoz = hozResolution;
  rData->vert = vertResolution;
  rData->fps = fps;
  rData->returnCode = 0;
  //pthread_create(&render, NULL, render_main, rData);

  //wrap up threads
  //pthread_join(render, NULL);
  //pthread_join(simuation, NULL);

  //clean up
  freeMatrix(sData->matrix);
  free(sData->matrix);
  //List_free(cellList, &free);

  if(rData->returnCode != 0 /*|| sData->returnCode != 0*/)
  {
    free(rData);
    //free(sData);
    return -1; //executed with some error
  }

  free(rData);
  free(sData);
  return 0;
}

void printUsage()
{
  logging("Expecting form ./urge hoz vert fps\n");
  //TODO change
}

void initMatrix(CellMatrix *matrix, const unsigned int hoz, const unsigned int vert)
{ //matrix[x][y] ; matrix[hoz][vert]
  matrix->modified = 0;
  matrix->hoz = hoz;
  matrix->vert = vert; //might as well do this here

  matrix->grid = malloc(sizeof(Cell**)*hoz);
  for(int i = 0; i < hoz; i++)
  {
    matrix->grid[i] = malloc(sizeof(Cell*)*vert);
    for(int j = 0; j < vert; j++)
    {
      matrix->grid[i][j] = NULL;
    }
  }
}

void freeMatrix(CellMatrix *matrix)
{
  for(int i = 0; i < matrix->hoz; i++)
  {
    for(int j = 0; j < matrix->vert; j++)
    {
      free(matrix->grid[i][j]);
    }
    free(matrix->grid[i]);
  }
  free(matrix->grid);
}
