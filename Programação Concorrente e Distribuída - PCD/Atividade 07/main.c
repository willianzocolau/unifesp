#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "mpi.h"

#define SRAND_VALUE 1985
#define SIZE_GRID 2048
#define MAX_GERACOES 2000
#define MAX_THREADS 4
#define OUT_POINTS 4

struct Args {
    int** grid;
    int** new_grid;
    int limite_inicial;
    int limite_final;
};

int countPopulation(int** grid){
  int i, j, count = 0;
  for (i = 1; i <= SIZE_GRID; i++){
    for (j = 1; j <= SIZE_GRID; j++){
      count += grid[i][j];
    }
  }
  return count;
}

void printPopulation(int **grid){
  printf("\n_________________________________");
  for (int i = 0; i < SIZE_GRID + 2; i++) {
    printf("\n");
    for (int j = 0; j < SIZE_GRID + 2; j++) {
      printf("%d\t", grid[i][j]);
    }
  }
}


int main(){

  MPI_Status Stat;

  int size, rank, tag, rc, N, generations, outPoints, s;

  struct timeval inicio, final2;
  int tmili;

  gettimeofday(&inicio, NULL);

  float *vec, max, min, *maxTot, *minTot;
  int i, pri, qtde, tamLocal, ierr, numProc, esteProc, iproc;
  MPI_Status status;

  MPI_Init(NULL,NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &numProc);
  MPI_Comm_rank(MPI_COMM_WORLD, &esteProc);

  if(esteProc == 0){
    N = SIZE_GRID;
    generations = MAX_GERACOES; 
    outPoints = OUT_POINTS; 
    s=N/numProc;

    int GRID[N][N]; 
    srand(SRAND_VALUE);
    for (int i = 0; i < N; i++){
     for (int j = 0; j < N; j++){
        GRID[i][j] = rand() % 2;
      }
    }
    int info[4];
    info[0]=N; info[1]=s; info[2]=generations; info[3]=outPoints;
    for (int dest=0; dest<numProc; dest++) MPI_Send(&info, 4, MPI_INT, dest, 1, MPI_COMM_WORLD); 
    int FATIA[N/numProc][N]; 
    for (int z=0; z<numProc; z++)
    {
      for (int k=0; k<s; k++) 
        for (int l=0; l<N; l++) 
          FATIA[k][l]=GRID[k+(z*s)][l]; 
      MPI_Send(&FATIA, N*s, MPI_INT, z, 1, MPI_COMM_WORLD); 
    }
  }

  
  int LOCAL[4];   
  MPI_Recv(&LOCAL, 4, MPI_INT, 0, 1, MPI_COMM_WORLD, &Stat);  

  int GRIDLOCAL[LOCAL[1]][LOCAL[0]]; 
  MPI_Recv(&GRIDLOCAL, LOCAL[0]*LOCAL[1], MPI_INT, 0, 1, MPI_COMM_WORLD, &Stat); 

  N = LOCAL[0];     
  s = LOCAL[1];    
  generations=LOCAL[2]; 
  outPoints=LOCAL[3];   

  int TODOWN[N];  int TOUP[N]; int DOWN[N]; int UP[N];

  for (int i=1; i<=generations; i++) 
  { 

    if (esteProc!=numProc-1) 
    {
      for (int j=0; j<N; j++) TODOWN[j]=GRIDLOCAL[s-1][j];
      MPI_Send(&TODOWN, N, MPI_INT, esteProc+1, 1, MPI_COMM_WORLD);

    } else {
      for (int k=0; k<N; k++) DOWN[k]=0; 
    } 

    if (esteProc!=0)
    {
      MPI_Recv(&UP, N, MPI_INT, esteProc-1, 1, MPI_COMM_WORLD, &Stat);  

    } else { for (int k=0; k<N; k++) UP[k]=0; }  
  
    if (esteProc!=0) 
    {
      for (int j=0; j<N; j++) TOUP[j]=GRIDLOCAL[0][j];
      MPI_Send(&TOUP, N, MPI_INT, esteProc-1, 1, MPI_COMM_WORLD);
    }
  
    if (esteProc!=numProc-1) 
    {
      MPI_Recv(&DOWN, N, MPI_INT, esteProc+1, 1, MPI_COMM_WORLD, &Stat);
    }
    int sum=0; 
    int NOVOGRID[s][N];
    for (int x=0; x<s; x++)
    { 
      for (int y=0; y<N; y++) 
      {
        if (x==0 && y==0){ 
          sum = GRIDLOCAL[x+1][y]+GRIDLOCAL[x+1][y+1]+GRIDLOCAL[0][y+1]+UP[0]+UP[1];
        }
        else if (x==0 && y==N-1){ 
          sum = GRIDLOCAL[x][y-1]+GRIDLOCAL[x+1][y-1]+GRIDLOCAL[x+1][y]+UP[N-1]+UP[N-2];
        }
        else if (x==s-1 && y==0){ 
          sum = GRIDLOCAL[x][y+1]+GRIDLOCAL[x-1][y+1]+GRIDLOCAL[x-1][y]+DOWN[0]+DOWN[1];
        }
        else if (x==s-1 && y==N-1){ 
          sum = GRIDLOCAL[x-1][y]+GRIDLOCAL[x-1][y-1]+GRIDLOCAL[x][y-1]+DOWN[N-1]+DOWN[N-2];
        }
        else
        {
          if (y==0) {
            sum=GRIDLOCAL[x-1][y]+GRIDLOCAL[x-1][y+1]+GRIDLOCAL[x][y+1]+GRIDLOCAL[x+1][y+1]+GRIDLOCAL[x+1][y];
          }
          else if (y==N-1) {
            sum=GRIDLOCAL[x-1][y]+GRIDLOCAL[x-1][y-1]+GRIDLOCAL[x][y-1]+GRIDLOCAL[x+1][y-1]+GRIDLOCAL[x+1][y];
          }
          else if (x==0) {
            sum=GRIDLOCAL[x][y-1]+GRIDLOCAL[x+1][y-1]+GRIDLOCAL[x+1][y]+GRIDLOCAL[x+1][y+1]+GRIDLOCAL[x][y+1]+UP[y-1]+UP[y]+UP[y+1];
          }
          else if (x==s-1) {
            sum=GRIDLOCAL[x-1][y-1]+GRIDLOCAL[x-1][y]+GRIDLOCAL[x-1][y+1]+GRIDLOCAL[x][y+1]+GRIDLOCAL[x][y-1]+DOWN[y-1]+DOWN[y]+DOWN[y+1];
          }
          else {
            sum=GRIDLOCAL[x-1][y-1]+GRIDLOCAL[x-1][y]+GRIDLOCAL[x-1][y+1]+GRIDLOCAL[x][y+1]+GRIDLOCAL[x+1][y+1]+GRIDLOCAL[x+1][y]+GRIDLOCAL[x+1][y-1]+GRIDLOCAL[x][y-1];
          }
        }
        if (GRIDLOCAL[x][y]==1 && (sum==2 || sum==3)) NOVOGRID[x][y]=1;
        else if (GRIDLOCAL[x][y]==1 && sum>3) NOVOGRID[x][y]=0;
        else if (GRIDLOCAL[x][y]==1 && sum<1) NOVOGRID[x][y]=0;
        else if (GRIDLOCAL[x][y]==0 && sum==3) NOVOGRID[x][y]=1;
        else NOVOGRID[x][y]=0;
      
      }
    }


    for (int x=0; x<s; x++)
      for (int y=0; y<N; y++)
        GRIDLOCAL[x][y]=NOVOGRID[x][y];

    if (i%outPoints==0) 
    {
      if (esteProc==0) 
      {
        int GRIDPRINTA[s][N];
        for (int i=1; i<size; i++)
        {
          MPI_Recv(&GRIDPRINTA, N*s, MPI_INT, i, 1, MPI_COMM_WORLD, &Stat);
          for (int x=0; x<s; x++)
          {
            for (int y=0; y<N; y++) printf("%d", GRIDPRINTA[x][y]);
            printf("\n");
          }
        }
      }
      else MPI_Send(&GRIDLOCAL, N*s, MPI_INT, 0,1, MPI_COMM_WORLD);
    }   
  } 
  gettimeofday(&final2, NULL);
  tmili = (int) (1000 * (final2.tv_sec - inicio.tv_sec) + (final2.tv_usec - inicio.tv_usec) / 1000);

  printf("Tempo decorrido: %d milisegundos\n", tmili); 
  MPI_Finalize();
}