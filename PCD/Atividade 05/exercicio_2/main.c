#include<stdio.h>
#include<string.h>
#include<pthread.h>

#define MAX_THREADS 2
pthread_t tid[MAX_THREADS];
int counter;

typedef struct {
    int permissions;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} semaphore;

semaphore s;

void wait(semaphore *s);
void signal(semaphore *s);
void init(semaphore *s, int permissions);

void *trythis(void *arg) {
  wait(&s);

  unsigned long i = 0;
  counter += 1;
  printf("Thread %d bloqueou acesso.\n", counter);

  for (i = 0; i < (1000000000); i++);

  signal(&s);
  printf("Thread %d liberou acesso.\n", counter);

  return NULL;
}

int main(void) {
  int i = 0;
  int error;

  init(&s, 1);

  while (i < MAX_THREADS) {
    error = pthread_create(&(tid[i]), NULL, &trythis, NULL);
    if (error != 0)
      printf("\nThread não pode ser criada :[%s]", strerror(error));
    i++;
  }

  i = 0;
  while (i < MAX_THREADS) {
    pthread_join(tid[i], NULL);
    i++;
  }

  return 0;
}

void wait(semaphore *s) {
  pthread_mutex_lock(&(s->mutex));
  while (s->permissions == 0) {
    pthread_cond_wait(&(s->cond), &(s->mutex));
  }
  s->permissions--;
  pthread_mutex_unlock(&(s->mutex));
}

void signal(semaphore *s) {
  pthread_mutex_lock(&(s->mutex));
  s->permissions++;
  pthread_cond_broadcast(&(s->cond));
  pthread_mutex_unlock(&(s->mutex));
}

void init(semaphore *s, int permissions) {
  s->permissions = permissions;
}

