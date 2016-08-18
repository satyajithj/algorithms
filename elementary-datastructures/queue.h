#include <stdbool.h>

#ifndef QUEUE_H
#define QUEUE_H

#define Q_SIZE 100

typedef struct {
  int queue[Q_SIZE];
  int front_index;
  int back_index;
} queue;

void init_queue(queue *);
void enqueue(queue *, int);
int dequeue(queue *);
bool is_empty(queue *);

#endif
