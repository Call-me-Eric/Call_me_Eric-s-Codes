#include <iostream>
#include <cstdio>
using namespace std;

struct node {
	int data;
	node *next;
}; 
node *head, *p, *r;
int n, m;
int main(){
	cin >> n >> m;
	head = new node;
	head->data = 1;	
	head->next = NULL; r = head;
	for(int i = 2; i <= n; i++){
		p = new node;
		p->data = i;
		p->next = NULL;
		r->next = p;
		r = p; 
	}
	r->next = head; r = head;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m - 2; j++)
			r = r->next;
		cout << r->next->data <<' ';
		r->next = r->next->next;
		r = r->next;

	}
	return 0;
}

