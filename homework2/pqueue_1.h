#ifndef PQUEUE_1_H
#define PQUEUE_1_H

#include <stdio.h>
#include <stdlib.h>

#include "pqueue_n.h"

struct pqueue_1
{
   struct pqueue_n* pqueue;
};
//pq1_create allocates and returns O(1) priority queue.
static inline struct pqueue_1 *pq1_create(void)
{
    int i;
    struct pqueue_1 *pq=(struct pqueue_1*)malloc(sizeof(struct pqueue_1));
    if(pq!=NULL)
    {
        pq->pqueue=(struct pqueue_n*)malloc(sizeof(struct pqueue_n)*16);
        for(i=PQN_HIGHEST_PRIORITY;i<=PQN_LOWEST_PRIORITY;i++)
        {
            pq->pqueue[i].next=NULL;
        }
    }
    //if unable to allocate the priority queue,returns NULL.
    return pq;
}
static inline int pq1_delete(struct pqueue_1 *pq)
{
   int i;
   for(i=PQN_HIGHEST_PRIORITY;i<=PQN_LOWEST_PRIORITY;i++)
   {
       if(pq->pqueue[i].next!=NULL)
       {
            return -11;
       }
   }
   free(pq->pqueue);
   free(pq);
   return 0;
}
static inline void pq1_enqueue(struct pqueue_1 *pq,void *value,unsigned int priority)
{
    pqn_enqueue(&pq->pqueue[priority],value,priority);
}
static inline void *pq1_dequeue(struct pqueue_1 *pq)
{
    int i;
    for(i=PQN_HIGHEST_PRIORITY;i<=PQN_LOWEST_PRIORITY;i++)
    {
        if(pq->pqueue[i].next!=NULL)
        {
            return pqn_dequeue(&pq->pqueue[i]);
        }
    }
    return NULL;
}
#endif // PQUEUE_1_H

