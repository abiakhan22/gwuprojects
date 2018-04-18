#ifndef PQUEUE_N_H
#define PQUEUE_N_H

#include <stdio.h>
#include <stdlib.h>

#define PQN_HIGHEST_PRIORITY 0
#define PQN_LOWEST_PRIORITY 15

struct pqueue_n
{
   void *data;
   unsigned int priority;
   struct pqueue_n *next;
};
//pqn_create allocates and returns O(n) priority queue.
static inline struct pqueue_n *pqn_create(void)
{
    struct pqueue_n *pq=(struct pqueue_n*)malloc(sizeof(struct pqueue_n));
    if(pq!=NULL)
    {
        pq->data=NULL;
        pq->next=NULL;
    }
    //if unable to allocate the priority queue,returns NULL.
    return pq;
}
//pqn_delete deallocates an O(n) priority queue only if there are no items in it.
static inline int pqn_delete(struct pqueue_n *pq)
{
    //no items
    if(pq->next==NULL)
    {
        free(pq);
        return 0;
    }
    return -1;
}
//pqn_enqueue inserts a value into an O(n) priority queue.
static inline void pqn_enqueue(struct pqueue_n *pq,void *value,unsigned int priority)
{
    struct pqueue_n *temp1;
    struct pqueue_n *temp2;
    temp1=pq;
    temp2=pq->next;
    while(temp2!=NULL&&priority>=temp2->priority)
    {
        temp1=temp2;
        temp2=temp2->next;
    }
    temp1->next=pqn_create();
    temp1->next->data=value;
    temp1->next->priority=priority;
    temp1->next->next=temp2;
}
//pqn_dequeue removes the value at the head of an O(n) priority queue and returns the value
static inline void *pqn_dequeue(struct pqueue_n *pq)
{
    struct pqueue_n *temp;
    void *temp_data;
    if(pq->next!=NULL)
    {
        temp=pq->next;
        pq->next=temp->next;
        temp_data=temp->data;
        free(temp);
        return temp_data;
    }
    return NULL;
}
#endif // PQUEUE_N_H

