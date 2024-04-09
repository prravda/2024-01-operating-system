#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *funcForThread(void *arg) {
  sleep(1);
  printf("Thread created successfully\n");
  return NULL;
}

void main() {
  // create POSIX Thread(pthread)
  pthread_t thread_id;
  printf("Before Thread\n");
  pthread_create(&thread_id, NULL, funcForThread, NULL);
  pthread_join(thread_id, NULL);
  printf("After Thread\n");
  exit(0);
}