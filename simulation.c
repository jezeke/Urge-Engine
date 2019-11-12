#include "simulation.h"
#include "init_threads.h"
#include <math.h>

void updateTemp(CellMatrix *data);

void updatePosition(CellMatrix *data);

void* simulation_main(void *data)
{
  simData *sData = (simData*)data;

  while(1) //FIXME sucky busy waiting with no proper exit condition
  {
    updatePosition(sData->grid); //this seems like a bad way of doing things
    updateTemp(sData->grid); //should combine temp & pos?
  }
}

void updateTemp(CellMatrix *data) //can we do this at the same time as position updating?
{

}

void updatePosition(CellMatrix *data) //combine with reagent reaction sim?
{

}
