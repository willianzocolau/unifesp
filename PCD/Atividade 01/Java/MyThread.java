package com.company;

class MyThread {
  public static int SIZE_GRID;
  private static int[][] grid;
  private static int[][] new_grid;
  private int limite_inicial;
  private int limite_final;

  public MyThread(int[][] grid, int[][] new_grid, int limite_inicial, int limite_final, int SIZE_GRID) {
    this.grid = grid;
    this.new_grid = new_grid;
    this.limite_inicial = limite_inicial;
    this.limite_final = limite_final;
    this.SIZE_GRID = SIZE_GRID;
  }

  public static int getNeighborsLeft(int[][] grid, int i, int j){
    j = j - 1;
    int neighbords_left = grid[i - 1][j] + grid[i][j] + grid[i + 1][j];
    return neighbords_left;
  }

  public static int getNeighborsBottom(int[][] grid, int i, int j){
    i = i + 1;
    int neighbords_bottom = grid[i][j] + grid[i][j + 1];
    return neighbords_bottom;
  }

  public static int getNeighborsRight(int[][] grid, int i, int j){
    j = j + 1;
    int neighbords_right = grid[i][j] + grid[i - 1][j];
    return neighbords_right;
  }

  public static int getNeighborsTop(int[][] grid, int i, int j){
    i = i - 1;
    int neighbords_top = grid[i][j];
    return neighbords_top;
  }

  public static int getNeighbors(int[][] grid, int i, int j){
    int n_neighbors = 0;
    n_neighbors = n_neighbors + getNeighborsLeft(grid, i, j) + getNeighborsBottom(grid, i, j);
    n_neighbors = n_neighbors + getNeighborsRight(grid, i, j) + getNeighborsTop(grid, i, j);
    return n_neighbors;
  }

  public static void DeadLife(int[][] grid, int[][] new_grid, int i, int j){
    int neighbors = getNeighbors(grid, i, j);
    int life = grid[i][j];
    //System.out.println(String.format("(%d,%d) -> %d", i, j, neighbors));
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

  public void nextGeneration(){
    for (int i = limite_inicial; i <= limite_final; i++){
      for (int j = 1; j <= SIZE_GRID; j++){
        DeadLife(grid, new_grid, i, j);
      }
    }
  }

  void printPopulation(int[][] grid){
    System.out.println("_________________________________");
    for (int i = 0; i < SIZE_GRID + 2; i++) {
      System.out.println();
      for (int j = 0; j < SIZE_GRID + 2; j++) {
        System.out.print(grid[i][j] + "\t");
      }
    }
    System.out.println();
  }

  public void run(){
    nextGeneration();
  }
}
