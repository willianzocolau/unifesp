#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>

#define SIZE 10000000
#define NUM_THREADS 16

int limit = SIZE / NUM_THREADS;

int *vector1, *vector2;
long result;
pthread_t *th;
sem_t semaphore;

typedef struct Attr {
    int start, end;
} Attr;

void random_array() {
  for (int i = 0; i < SIZE; i++) {
    vector1[i] = rand() % 100 + 1;
    vector2[i] = rand() % 100 + 1;
  }
}

void *new_thread(void * data) {
  Attr *dados = static_cast<Attr *>(data);
  long result_parcial = 0;

  for (int i = dados->start; i < dados->end; i++)
    result_parcial += vector1[i] * vector2[i];

  sem_wait(&semaphore);
  result += result_parcial;
  sem_post(&semaphore);
  return NULL;
}

int get_limit(int start, int thread) {
  int bonusAdd = 0;
  int finalValue = start + limit;
  if (limit % NUM_THREADS != 0)
    bonusAdd = 1;

  finalValue += bonusAdd;

  if (thread == NUM_THREADS - 1)
    finalValue = SIZE;

  return finalValue;
}

void scalar(){
  for (int i = 0; i < NUM_THREADS; i++) {
    int startValue = limit * i;
    Attr * dados = (Attr * ) malloc(sizeof(Attr));
    dados ->start = startValue;
    dados ->end = get_limit(startValue, i);
    if (pthread_create( & th[i], NULL, new_thread, dados))
      printf("Erro ao juntar NUM_THREADS %d\n", i);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_join(th[i], NULL))
      printf("Erro ao juntar NUM_THREADS %d\n", i);
  }
}

int main() {
  sem_init(&semaphore, 0, 1);
  vector1 = (int*) malloc(sizeof(int) * SIZE);
  vector2 = (int*) malloc(sizeof(int) * SIZE);
  th = (pthread_t * ) malloc(sizeof(pthread_t) * NUM_THREADS);
  random_array();

  struct timeval stop, start;
  gettimeofday( & start, NULL);
  scalar();
  gettimeofday( & stop, NULL);
  double secs = secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

  printf("Resultado: %lu\n", result);
  printf("Tempo: %f ms", secs);

  sem_destroy(&semaphore);
  return 0;
}

