/*Jialiang Liang G38614191*/
//#include "list.h"
#include <list.h>

int main(void)
{
    int a = 34;
    int b = 6;
    int c = 4000;
    int d = 3;
    char w1 = 'A';
    char w2 = 'Z';
    char w3 = 'S';
    char w4 = 'E';

    printf("=========================Testing=========================\n");
    
    struct linked_list* p = ll_create();
    printf("Successfully created a empty list!\n");
    
    //test destroy
    ll_destroy(p);
    printf("Successfully destroyed an empty list!\n");
    
    //add element in to the list
    p = ll_create();//create again
    printf("Successfully created a empty list and add 8 elements into the list!\n");
    ll_add(p, &a);
    ll_add(p, &w1);
    ll_add(p, &b);
    ll_add(p, &w2);
    ll_add(p, &c);
    ll_add(p, &w3);
    ll_add(p, &d);
    ll_add(p, &w4);
    printf("Now we have list contains 8 elements: {34, A, 6, Z, 4000, S, 3, E}\n");
    int i = ll_length(p);
    printf("After add 8 elements into the list the list length is: %d\n", i);//print the length of the list
    
    //test remove
    ll_remove_first(p);
    int q = ll_length(p);
    printf("After remove 1 elements(E) from the 8-element list the new list length is: %d\n", q);//print the length of the list after remove the first one
    
    //test destroy a list with elements
    ll_destroy(p);
    int o = ll_length(p);
    printf("Trying to destory the list with 7-element, and testing the list length, which is: %d\n", o);//print the length of the list after trying to destory the 7-element
    
    //test contain
    int ct = ll_contains(p, &c);
    printf("The position of 4000 is: %d\n", ct);
    int ct1 = ll_contains(p, &w4);
    printf("The position of E is: %d, becauese it has been removed in the previous steps!\n", ct1);
    
    printf("=========================================================\n");

}

