#include"datastructure.h"


/* function: Queue queue_create()
 *
 * create a new queue and initialized it, memory allocated from the heap, so the associated memory should be freed manually 
 *
 * input: none
 * return: a queue struct
 * */
Queue queue_create()
{
    Queue qu;
    QueueNode *qn;

    qn = malloc(sizeof(QueueNode));

    qn->next = NULL;
    qn->data = NULL;

    qu.head = qn;
    qu.rear = qn;
    qu.current = qn;
    qu.length = 0;

    return qu;
}


/* function: void queue_add_node(Queue *qu, void *data, int length)
 *
 * create a new queue and initialized it. The initialization is 
 * implemented with a pointer to the data. But only the value of *data will be passed, the memory data points to will not be changed
 *
 * input:
 * return:
 */
void queue_add_node(Queue *qu, void *data, int length)
{
    QueueNode *qn = NULL; 
    void *p = NULL;

    qn = malloc(sizeof(QueueNode));
    p = malloc(length);
    memcpy(p, data, length);

    qn->next = NULL;
    qn->data = p;
    qn->length = length;

    qu->rear->next = qn;
    qu->rear = qn;
    qu->length++;
}


/* function: QueueNode queue_pop_node(Queue *qu)
 *
 * pop one queue node from the head of the queue, the queue node will be freed, but the memory the pointer QueueNode.data points to cannot be freed. The popped QueueNode.data should be freed manually
 * 
 * input: pointer to the queue
 * return: the queue node containing the data
 */
QueueNode queue_pop_node(Queue *qu)
{
    QueueNode qn;
    QueueNode *p = NULL;

    if(qu->head->next == NULL)
    {
        perror("Queue pop error");
        exit(0);
    }
    p = qu->head->next;
    qn = (*p);
    qu->head->next = qu->head->next->next;
    qu->length--;
    if(qu->head->next == NULL)
        qu->rear = qu->head;

    free(p);
    
    return qn;
}


/* function: bool queue_is_empty(Queue *qu)
 *
 * to check if a queue is empty. if empty, returns true 
 *
 * input: pointer to a Queue
 * return: true if the queue is empty, return false if the queue is not empty
 * */
bool queue_is_empty(Queue *qu)
{
    if(qu->head->next == NULL)
        return true;
    else
        return false;
}


/* function: void queue_destroy(Queue *qu)
 *
 * free the memory the queue takes up
 *
 * input: pointer to the queue
 * return: none
 */
void queue_destroy(Queue *qu)
{
    while(!queue_is_empty(qu))
        queue_pop_node(qu);

    free(qu->head);
}
