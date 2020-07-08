#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SRAND_VALUE 1985
#define SIZE_GRID 2048
#define MAX_GERACOES 2000
#define MAX_THREADS 16

int getNeighborsLeft(int** grid, int i, int j){
  j = j - 1;
  int neighbords_left = grid[i - 1][j] + grid[i][j] + grid[i + 1][j];
  return neighbords_left;
}

int getNeighborsBottom(int** grid, int i, int j){
  i = i + 1;
  int neighbords_bottom = grid[i][j] + grid[i][j + 1];
  return neighbords_bottom;
}

int getNeighborsRight(int** grid, int i, int j){
  j = j + 1;
  int neighbords_right = grid[i][j] + grid[i - 1][j];
  return neighbords_right;
}

int getNeighborsTop(int** grid, int i, int j){
  i = i - 1;
  int neighbords_top = grid[i][j];
  return neighbords_top;
}

int getNeighbors(int** grid, int i, int j){
  int n_neighbors = 0;
  n_neighbors = n_neighbors + getNeighborsLeft(grid, i, j) + getNeighborsBottom(grid, i, j);
  n_neighbors = n_neighbors + getNeighborsRight(grid, i, j) + getNeighborsTop(grid, i, j);
  return n_neighbors;
}

void copyLeftRightColumns(int** grid){
  for (int i = 1; i <= SIZE_GRID; ++i) {
    grid[i][0] = grid[i][SIZE_GRID];
    grid[i][SIZE_GRID+1] = grid[i][1];
  }
}

void copyTopBottomLines(int** grid){
  for (int i = 1; i <= SIZE_GRID; ++i) {
    grid[0][i] = grid[SIZE_GRID][i];
    grid[SIZE_GRID+1][i] = grid[1][i];
  }
}

void copyCorners(int** grid){
  grid[0][0] = grid[SIZE_GRID][SIZE_GRID];
  grid[0][SIZE_GRID + 1] = grid[SIZE_GRID][1];
  grid[SIZE_GRID + 1][0] = grid[1][SIZE_GRID];
  grid[SIZE_GRID + 1][SIZE_GRID + 1] = grid[1][1];
}

void copyBorder(int** grid){
  copyLeftRightColumns(grid);
  copyTopBottomLines(grid);
  copyCorners(grid);
}

void newPopulation(int** grid){
  srand(SRAND_VALUE);
  int i, j;
  for (i = 1; i <= SIZE_GRID; i++){
    for (j = 1; j <= SIZE_GRID; j++){
      grid[i][j] = rand() % 2;
    }
  }
}

int countPopulation(int** grid){
  int i, j, count = 0;
  for (i = 1; i <= SIZE_GRID; i++){
    for (j = 1; j <= SIZE_GRID; j++){
      count += grid[i][j];
    }
  }
  return count;
}

int** copyPopulation(int** grid){
  int i, j;
  int **m = (int**)malloc((SIZE_GRID + 2) * sizeof(int*));
  for (i = 0; i < SIZE_GRID + 2; i++){
    m[i] = (int*) malloc((SIZE_GRID + 2) * sizeof(int));
    for (j = 0; j < SIZE_GRID + 2; j++){
      m[i][j] = grid[i][j];
    }
  }
  return m;
}

int** initialize(){
  int i, j;
  int **m = (int**)malloc((SIZE_GRID + 2) * sizeof(int*));
  for (i = 0; i < SIZE_GRID + 2; i++){
    m[i] = (int*) malloc((SIZE_GRID + 2) * sizeof(int));
    for (j = 0; j < SIZE_GRID + 2; j++){
      m[i][j] = 0;
    }
  }
  return m;
}

void liberar(int** grid){
  int i;
  for (i = 0; i < SIZE_GRID + 2; i++){
    free(grid[i]);
  }
  free(grid);
}

void DeadLife(int** grid, int** new_grid, int i, int j){
  int neighbors = getNeighbors(grid, i, j);
  int life = grid[i][j];
  if(life == 1){
    if(neighbors < 2) {
      new_grid[i][j] = 0;
    } else if (neighbors == 2 || neighbors == 3){
      new_grid[i][j] = 1;
    } else if(neighbors >= 4){
      new_grid[i][j] = 0;
    }
  } else if(life == 0 && neighbors == 3){
    new_grid[i][j] = 1;
  }
}

int** nextGeneration(int** grid){
  int i, j;
  int **new_grid = copyPopulation(grid);

  #pragma omp parallel default(none) private(i, j) shared(grid, new_grid) num_threads(MAX_THREADS)
  {
    #pragma omp for
    for (i = 1; i <= SIZE_GRID; i++) {
      for (j = 1; j <= SIZE_GRID; j++) {
        DeadLife(grid, new_grid, i, j);
      }
    }
  }
  return new_grid;
}

int main() {
  int** grid = initialize();
  newPopulation(grid);

  double start, end;

  start = omp_get_wtime();

  for (int i = 0; i < MAX_GERACOES; i++) {
    copyBorder(grid);
    int** new_grid = nextGeneration(grid);
    liberar(grid);
    grid = new_grid;
  }

  end = omp_get_wtime();

  printf("Threads: %d\n", MAX_THREADS);
  printf("Células vivas: %d\n", countPopulation(grid));
  printf("Tempo decorrido: %.0f milissegundos\n", ((end-start)*1000000)/1000);
}