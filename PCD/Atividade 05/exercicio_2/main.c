#include<stdio.h>
#include<string.h>
#include<pthread.h>

#define MAX_THREADS 2
pthread_t tid[MAX_THREADS];
int counter;

typedef struct {
    int val;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} semaphore;

semaphore s;

void up(semaphore *s) {
  pthread_mutex_lock(&(s->mutex));
  while (s->val == 0) {
    pthread_cond_wait(&(s->cond), &(s->mutex));
  }
  s->val--;
  pthread_mutex_unlock(&(s->mutex));
}

void down(semaphore *s) {
  pthread_mutex_lock(&(s->mutex));
  s->val++;
  pthread_cond_broadcast(&(s->cond));
  pthread_mutex_unlock(&(s->mutex));
}

void init(semaphore *s, int permissions) {
  s->val = permissions;
}

void *trythis(void *arg) {
  up(&s);

  unsigned long i = 0;
  counter += 1;
  printf("\n Thread %d bloqueou acesso.\n", counter);

  for (i = 0; i < (0xFFFFFFFF); i++);

  printf("\n Thread %d liberou acesso.\n", counter);

  down(&s);

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
