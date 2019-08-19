#include <stdio.h>
#include <stdlib.h>

#define SRAND_VALUE 1985
#define SIZE_GRID 3

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
//TODO conta o próprio elemento?
int getNeighbors(int** grid, int i, int j){
  int n_neighbors = 0;
  n_neighbors = n_neighbors + getNeighborsLeft(grid, i, j) + getNeighborsBottom(grid, i, j);
  n_neighbors = n_neighbors + getNeighborsRight(grid, i, j) + getNeighborsTop(grid, i, j);
  printf("\n (%d, %d) -> %d", i , j, n_neighbors);
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

void printPopulation(int **grid){
  for (int i = 0; i < SIZE_GRID + 2; ++i) {
    printf("\n");
    for (int j = 0; j < SIZE_GRID + 2; ++j) {
      printf("%d\t", grid[i][j]);
    }
  }
}

int** newPopulation(int** grid){
  srand(SRAND_VALUE);
  int i, j;
  for (i = 1; i <= SIZE_GRID; i++){
    for (j = 1; j <= SIZE_GRID; j++){
      grid[i][j] = rand() % 2;
    }
  }
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

int main() {
  int** grid = initialize();
  newPopulation(grid);
  copyBorder(grid);
  printPopulation(grid);
}
