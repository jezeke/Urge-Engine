#ifndef SIMULATION
#define SIMULATION

typedef struct RGB
{
  float r;
  float g;
  float b;
} RGB;

typedef struct Trajectory
{
  double x;
  double y;
} Trajectory;

typedef struct Cell
{
  RGB colour;
  pthread_mutex_t lock;
  Trajectory traj;
} Cell;

typedef struct CellMatrix
{
  int hoz;
  int vert;
  int modified;
  Cell **matrix;
} CellMatrix;

#endif
