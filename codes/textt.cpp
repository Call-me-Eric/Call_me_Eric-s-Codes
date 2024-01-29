#include <iostream>
#include <cstdio>
using namespace std;

struct queue{
	int head, tail;
	int data[10001];
	int pop(){
		int t = data[head];
		head++;
		return t;
	}
	int printque(){
		for(int i = head + 1;i <= tail;i++){
			printf("%d ",data[i]);
		}
	}
	void push(int t){data[++tail] = t;}
	void init(){head = 0;tail = 0;}
};

int main(){
	ios::sync_with_stdio(false);
	queue a;
	a.init();
	a.push(1);
	a.push(2);
	a.push(3);
	a.printque();
	return 0;
}

