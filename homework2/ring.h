#ifndef RING_H
#define RING_H

#include <stdio.h>
#include <stdlib.h>

struct ring
{
    void** data;
    int head;
    int tail;
    int num_items;
};
//rb_create allocates and returns a pointer to a ring buffer
static inline struct ring* rb_create(size_t num_items)
{
    struct ring* rb=(struct ring*)malloc((sizeof(struct ring)));
    if(rb!=NULL)
    {
        rb->data=(void**)malloc((sizeof(void*)*num_items));
        rb->head=rb->tail=0;
        rb->num_items=num_items;
    }
    return rb;
}
//rb_delete deallocates a ring buffer if there are not items stored in it.
static inline int rb_delete(struct ring *rb)
{
    if(rb->head==rb->tail)
    {
        free(rb->data);
        free(rb);
        return 0;
    }
    return -1;
}
//rb_isempty returns 0 if the ring buffer is non-empty and 1 if the ring buffer is empty.
static inline int rb_isempty(struct ring *rb)
{
    if(rb->head==rb->tail)
        return 1;
    return 0;
}
//rb_isfull returns 0 if the ring buffer is non-full and 1 if the ring buffer is full.
static inline int rb_isfull(struct ring *rb)
{
    if(rb->tail-rb->head==rb->num_items)
        return 1;
    return 0;
}
//rb_enqueue inserts a value into the ring buffer,and returns 0.If it is full, return −1.
static inline int rb_enqueue(struct ring *rb,void *value)
{
    if(rb->tail-rb->head!=rb->num_items)
    {
        rb->data[rb->tail%rb->num_items]=value;
        rb->tail++;
    }
    return -1;
}
//rb dequeue removes a value at the head of the ring buffer, and returns it.
static inline void* rb_dequeue(struct ring *rb)
{
    if(!rb_isempty(rb))
    {
        return rb->data[(rb->head++)%rb->num_items];
    }
    return NULL;
}

#endif // RING_H

