#ifndef QUEUE
#define QUEUE

typedef struct Queue {
        int *data;
        int point;
        int size;
} Queue;

Queue *queueData(const int size);
void enqueue(Queue *, int data);
int dequeue(Queue *);
void freeQueue(Queue *);

#endif
