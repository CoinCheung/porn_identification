#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

/* ==============================================
 *  headers to be included
 * ============================================== */
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdio.h>


/* ==============================================
 * micros and data type definitions 
 * ============================================== */

/* types definitions */
// structure of queue node
typedef struct queue_node QueueNode;
struct queue_node
{
    struct queue_node* next;
    void *data; // point to the data the queue node contains
    int length; // the length of the data
};

// structure of queue
typedef struct
{
    QueueNode *head; // queue head
    QueueNode *rear; // queue rear
    QueueNode *current; // point to the current queue node in the interation
    int length;

}Queue;


/* ==============================================
 *  function definitions
 * ============================================== */
Queue queue_create(); // create a new queue
void queue_add_node(Queue *qu, void *data, int length); // add a node to the queue
QueueNode queue_pop_node(Queue *qu); // pop a node from the queue
bool queue_is_empty(Queue *qu); // check if a queue is empty
void queue_destroy(Queue *qu); // free all the memory the queue takes up

#endif
