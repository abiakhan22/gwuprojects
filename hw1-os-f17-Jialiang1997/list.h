/*Jialiang Liang G38614191*/
#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

struct linked_list {
    void *data;
    struct linked_list *next;
};

static inline struct linked_list *
ll_create(void)
{
    struct linked_list *ll = malloc(sizeof(struct linked_list));
    //If unable to allocate the list, ll create_returns NULL.
    ll->next = NULL;//initiallized otherwise will seg fault 11!!!
    ll->data = NULL;
    return ll;
}

//ll_destroy deallocates a linked list, only if it is empty.
static inline void
ll_destroy(struct linked_list *ll)
{
    if(ll->next == NULL){
        free(ll);
        ll->next = ll; //<--
    }
    
}

//ll_add inserts a value at the head of the linked list.
static inline void
ll_add(struct linked_list *ll, void *value)
{
    if(ll != NULL){
        struct linked_list *temp = ll;
        while(temp->next != NULL){
            temp = temp->next;
        }
            //temp->next = (struct linked_list*)malloc(100);
            temp->next = (struct linked_list*)malloc(sizeof(struct linked_list));
            temp = temp->next;
            temp->next = NULL;
            temp->data = value;
    }

}

//ll_length returns the total number of values in the linked list.
static inline int
ll_length(struct linked_list *ll)
{
    struct linked_list *temp = ll;
    int ct = 0;
    while(temp->next!=NULL){
        temp = temp->next;
        ct++;
    }
	return ct;
}

/*ll remove first removes the value at the head of the linked list and returns the value. If the list is
empty, ll remove first returns NULL*/
static inline void *
ll_remove_first(struct linked_list *ll)
{
    if(ll != NULL && ll->next != NULL){
        struct linked_list *temp1 = ll;
        struct linked_list *temp2 = ll->next;
        while(temp2->next != NULL){
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        void *data1 = temp2->data; //Using a pointer to take out the value of temp2.
        free(temp2);
        temp1->next = NULL;
    
        return data1;
    }
    return NULL;
}

/* ll_contains searches the linked list from head to tail and returns the first position at which the value
is found. In a list with n values, the head is position 1 and the tail is position n; therefore, if the value is
in the list, ll contains returns a logical true, the offset into the linked list. If the value is not found in
the list, 0 is returned; therefore, if the value is not in the list, ll contains returns a logical false.*/
static inline int
ll_contains(struct linked_list *ll, void *value)
{
    struct linked_list *temp = ll;
    int ct = 0;
    int i = 0;
    while(temp->next != NULL){//run until pass the last node.
        temp = temp->next;
        ct++;
        if(temp->data == value){
            i = 1;
            break;//the data i collected = the value in the list
        }
    }
    if(i == 0){
        ct = 0;
    }
	return ct;
}

#endif
