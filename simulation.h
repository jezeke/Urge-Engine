#ifndef SIMULATION
#define SIMULATION

#include <pthread.h>

typedef struct RGB
{
  float r;
  float g;
  float b;
} RGB;
//reminder: subset struct casting shit for rendering.
//don't you dare make a thread that copies cells from simulation matrix to render matrix

typedef struct Trajectory
{
  double x;
  double y;
} Trajectory;

typedef struct Material
{
  double mass;
  double heat;
  int fixed; //bool
  //need some way of defining reaction properties...maybe structs isnt the way
} Material;

typedef struct Cell
{
  RGB colour;
  pthread_mutex_t lock;
  Trajectory traj;
  Material mat;
} Cell;

typedef struct CellMatrix
{
  unsigned int hoz;
  unsigned int vert;
  int modified; //bool
  Cell ***grid; //stored non-contiguously currently. need to redesign how empty cells are stored if needed contiguous for rendering
} CellMatrix;

void* simulation_main(void *data);

#endif
