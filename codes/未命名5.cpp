#include <iostream>
#include <cstdio>
#include <cstdlib> //free()
using namespace std; 
  
struct node{  
    int data;  
    struct node *next;  
};  
  
int main(){  
    int i, j, k, m, n;  
    struct node *h, *p, *q;  
    scanf("%d%d", &n, &m);  
    if(n == 0)
    	return 0;
    h = new node;  
    h->data = 1;     
    h->next = h;  
    p = h;  
    for(i=2;i<=n;i++){  
        q = new node;  
        q->data = i;  
        q->next = p->next;  
        p->next = q;  
        p = q;  
    }  
    p = h;  
    k = 1;  
    while(p->next != p){  
        if(k < m-1){  
            k++;  
            p = p->next;  
        }else if(k == m-1){  
            q = p->next;  
            p->next = p->next->next;  
            printf("%d ",q->data);  
            free(q);  
            k = 1;  
            p = p->next;  
        }  
    }  
    printf("%d\n", p->data);  
    return 0;  
}  

