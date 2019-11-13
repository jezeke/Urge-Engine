#include "simulation.h"
#include "init_threads.h"
#include <math.h>

void updateTemp(CellMatrix *matrix);

void updatePosition(CellMatrix *matrix);

void* simulation_main(void *data)
{
  simData *sData = (simData*)data;

  while(1) //FIXME sucky busy waiting with no proper exit condition
  {
    updatePosition(sData->matrix); //this seems like a bad way of doing things
    updateTemp(sData->matrix); //should combine temp & pos?
  }
}

void updateTemp(CellMatrix *matrix) //can we do this at the same time as position updating?
{

}

void updatePosition(CellMatrix *matrix) //combine with reagent reaction sim?
{

}
