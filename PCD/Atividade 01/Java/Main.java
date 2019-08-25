package com.company;

import java.util.Random;

public class Main {
  public static int SRAND_VALUE = 1985;
  public static int SIZE_GRID = 2048;
  public static int MAX_GERACOES = 2000;
  public static int MAX_THREADS = 16;

  public static void copyLeftRightColumns(int[][] grid){
    for (int i = 1; i <= SIZE_GRID; ++i) {
      grid[i][0] = grid[i][SIZE_GRID];
      grid[i][SIZE_GRID+1] = grid[i][1];
    }
  }

  public static void copyTopBottomLines(int[][] grid){
    for (int i = 1; i <= SIZE_GRID; ++i) {
      grid[0][i] = grid[SIZE_GRID][i];
      grid[SIZE_GRID+1][i] = grid[1][i];
    }
  }

  public static void copyCorners(int[][] grid){
    grid[0][0] = grid[SIZE_GRID][SIZE_GRID];
    grid[0][SIZE_GRID + 1] = grid[SIZE_GRID][1];
    grid[SIZE_GRID + 1][0] = grid[1][SIZE_GRID];
    grid[SIZE_GRID + 1][SIZE_GRID + 1] = grid[1][1];
  }

  public static void copyBorder(int[][] grid){
    copyLeftRightColumns(grid);
    copyTopBottomLines(grid);
    copyCorners(grid);
  }

  public static int countPopulation(int[][] grid){
    int i, j, count = 0;
    for (i = 1; i <= SIZE_GRID; i++){
      for (j = 1; j <= SIZE_GRID; j++){
        count += grid[i][j];
      }
    }
    return count;
  }

  public static void newPopulation(int[][] grid){
    Random gerador = new Random(SRAND_VALUE);
    int i, j;
    for (i = 1; i <= SIZE_GRID; i++){
      for (j = 1; j <= SIZE_GRID; j++){
        grid[i][j] = gerador.nextInt(2147483647) % 2;
      }
    }
  }

  public static void printPopulation(int[][] grid){
    System.out.println("_________________________________");
    for (int i = 0; i < SIZE_GRID + 2; i++) {
      System.out.println();
      for (int j = 0; j < SIZE_GRID + 2; j++) {
        System.out.print(grid[i][j] + "\t");
      }
    }
    System.out.println();
  }

  public static int[][] copyPopulation(int[][] grid){
    int[][] m = new int[SIZE_GRID + 2][SIZE_GRID + 2];
    for (int i = 0; i < SIZE_GRID + 2; i++){
      for (int j = 0; j < SIZE_GRID + 2; j++){
        m[i][j] = grid[i][j];
      }
    }
    return m;
  }

  public static void main(String[] args) throws InterruptedException {
    int[][] grid = new int[SIZE_GRID + 2][SIZE_GRID + 2];
    newPopulation(grid);

    long startTime = System.currentTimeMillis();

    MyThread threads[] = new MyThread[MAX_THREADS];
    for (int i = 0; i < MAX_GERACOES; i++) {
      int incremento = SIZE_GRID / MAX_THREADS;
      int limite_inicial = 1;
      int limite_final = incremento;
      copyBorder(grid);
      int[][] new_grid = copyPopulation(grid);

      for (int th = 0; th < MAX_THREADS; th++) {
        threads[th] = new MyThread(grid, new_grid, limite_inicial, limite_final, SIZE_GRID);
        threads[th].run();

        limite_inicial += incremento;
        limite_final += incremento;
      }

      for(int j = 0; j < MAX_THREADS; j++) {
        threads[j].join();
      }

      grid = new_grid;
    }

    long calcTime = System.currentTimeMillis() - startTime;

    System.out.println("Threads: " + MAX_THREADS);
    System.out.println("Células vivas: " + countPopulation(grid));
    System.out.println("Tempo decorrido: " + calcTime + " milisegundos");
  }
}
