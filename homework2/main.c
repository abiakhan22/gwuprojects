#include "pqueue_1.h"
#include "ring.h"

int main(void)
{
    unsigned int p1,p2,p3,p4;
    int v1,v2,v3,v4;
    int* res;
    p1=p3=1;
    p2=2;
    p4=0;
    v1=1,v2=2,v3=3,v4=4;

    struct pqueue_n* pqn=pqn_create();
    pqn_enqueue(pqn,&v1,p1);
    pqn_enqueue(pqn,&v2,p2);
    pqn_enqueue(pqn,&v3,p3);
    res=(int*)pqn_dequeue(pqn);
    printf("%d\n",*res);
    pqn_enqueue(pqn,&v4,p4);
    res=(int*)pqn_dequeue(pqn);
    printf("%d\n",*res);
    printf("free:%d\n",pqn_delete(pqn));
    res=(int*)pqn_dequeue(pqn);
    printf("%d\n",*res);
    res=(int*)pqn_dequeue(pqn);
    printf("%d\n",*res);
    printf("free:%d\n",pqn_delete(pqn));

    struct pqueue_1* pq=pq1_create();
    pq1_enqueue(pq,&v1,p1);
    pq1_enqueue(pq,&v2,p2);
    pq1_enqueue(pq,&v3,p3);
    res=(int*)pq1_dequeue(pq);
    printf("%d\n",*res);
    pq1_enqueue(pq,&v4,p4);
    res=(int*)pq1_dequeue(pq);
    printf("%d\n",*res);
    printf("free:%d\n",pq1_delete(pq));
    res=(int*)pq1_dequeue(pq);
    printf("%d\n",*res);
    res=(int*)pq1_dequeue(pq);
    printf("%d\n",*res);
    printf("free:%d\n",pq1_delete(pq));

    struct ring* rb=rb_create(4);
    rb_enqueue(rb,&v1);
    printf("empty:%d\n",rb_isempty(rb));
    rb_enqueue(rb,&v2);
    rb_enqueue(rb,&v3);
    rb_enqueue(rb,&v4);
    printf("full:%d\n",rb_isfull(rb));
    res=rb_dequeue(rb);
    printf("%d\n",*res);
    printf("full:%d\n",rb_isfull(rb));
    res=rb_dequeue(rb);
    printf("%d\n",*res);
    res=rb_dequeue(rb);
    printf("%d\n",*res);
    printf("free:%d\n",rb_delete(rb));
    res=rb_dequeue(rb);
    printf("%d\n",*res);
    printf("empty:%d\n",rb_isempty(rb));
    printf("free:%d\n",rb_delete(rb));
    return 0;
}

