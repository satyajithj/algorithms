#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

// initialize queue
void init_queue(queue *q) {
  for (size_t i = 0; i < Q_SIZE; i++)
    q->queue[i] = 0;
  q->front_index = -1;
  q->back_index = -1;
}

// add an element to the queue
void enqueue(queue *q, int x) {

  if ((q->front_index == 0 && q->back_index == Q_SIZE-1)
        || (q->front_index == q->back_index+1))
      printf("%s\n", "queue is full");

  else if (q->back_index == Q_SIZE-1) {
    q->back_index = 0;
    q->queue[q->back_index] = x;
  }

  else if (q->front_index == -1) {
    q->front_index = 0;
    q->back_index = 0;
    q->queue[q->back_index] = x;
  }
  else
    q->queue[++q->back_index] = x;
}

// remove the front element
int dequeue(queue *q) {

  if (q->front_index == -1)   // if queue is empty
    return -1;

  int r = q->queue[q->front_index];   // extract from element

  if (q->front_index == q->back_index)  // reset indices if last element was extracted
    q->front_index = -1;

  else if (q->front_index == Q_SIZE-1)  // a circular queue
    q->front_index = 0;

  else
    q->front_index++;

  return r;
}

// check if queue is empty
bool is_empty(queue *q) {
  if (q->front_index == -1)
    return true;
  else
    return false;
}
