#include "Queue.h"



Queue *ConstructQueue(int limit) {
    Queue *queue = (Queue*) malloc(sizeof (Queue));
    if (queue == NULL) {
        return NULL;
    }
    if (limit <= 0) {
        printf("Invalid input.\n");
        exit(1);                  ////**********************EDW ISWS UPARXEI 8EMA**********************************************
    }
    queue->limit = limit;
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

void DestructQueue(Queue *queue) {
    NODE *pN;
    while (!isEmpty(queue)) {
        pN = Dequeue(queue);
        free(pN);
    }
    free(queue);
}

int Enqueue(Queue *pQueue, NODE *item) {
    /* Bad parameter */
    if ((pQueue == NULL) || (item == NULL)) {
        return 0;
    }
    // if(pQueue->limit != 0)
    if (pQueue->size >= pQueue->limit) {
        return 0;
    }
    /*the queue is empty*/

    item->prev = NULL;
    if (pQueue->size == 0) {
        pQueue->head = item;
        pQueue->tail = item;

    } else {
        /*adding item to the end of the queue*/
        pQueue->tail->prev = item;
        pQueue->tail = item;
    }
    pQueue->size++;
    return 1;
}

NODE * Dequeue(Queue *pQueue) {
    /*the queue is empty or bad param*/

    NODE *item;
    if (isEmpty(pQueue)==1){
        return NULL;
    }
    item = pQueue->head;
    pQueue->head = (pQueue->head)->prev;
    pQueue->size--;
    return item;
}

int isEmpty(Queue* pQueue) {
    if (pQueue == NULL) {
        return 0;
    }
    if (pQueue->size == 0) {
        return 1;
    } else {
        return 0;
    }
}
