#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int a = 0;
int b = 0;
int c = 0;
pthread_t t1,t2; // duas threads
sem_t mutex;

void *thread1(void *par){
  while(1){
    if(a == 0){
      printf("A ");
      a = 1;
    }
    sem_wait(&mutex);  // entra na regiao critica
    if((a == 1 || a == 2) && b == 0){
      printf("RACE ");
      b = 1;
      a++;
    }
    sem_post(&mutex);  // sai da regiao critica
  }
}

void *thread2(void *par){
  while(1){
    sem_wait(&mutex);  // entra na regiao critica
    if((a == 1 || a == 2) && c == 0){
      printf("CAR ");
      c = 1;
      a++;
    }
    sem_post(&mutex);  // sai da regiao critica
    if(a == 3){
      printf("IS FUN TO WATCH \n");
      a = 0;
      b = 0;
      c = 0;
    }
  }
}

int main(void){
  sem_init(&mutex, 0, 2);
  pthread_create(&t1,NULL,&thread1,NULL);
  pthread_create(&t2,NULL,&thread2,NULL);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  return 0;
}
