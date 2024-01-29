#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
struct ticket{
	int time;
	int price, book;
};
ticket tic[100005];
int head = 1;
int tail = 1;
int n;
int main(){

	scanf("%d",&n);
	int a, b, c;
	ticket q;
	a = b = c = 0;
	int sum = 0;
	bool ok = 0;
	
	for(int k = 1;k <= n;k++){
		a = b = c = 0;
		scanf("%d%d%d",&a,&b,&c);
		if(a == 0){//If by subway
			sum = sum + b;
			tic[tail].time = c + 45;
			tic[tail].price = b;
			tic[tail].book = 0;
			tail++; 
		}
		else {//If by bus
			while(head < tail && tic[head].time < c) head++;
			ok = 1;
			for(int i = head;i < tail;i++){
				if(tic[i].book == 0 && tic[i].price >= b){
					ok = 0;
					tic[i].book = 1;
					break;
				}
			}
			if(ok) sum += b;
		}
		
	}
	printf("%d\n",sum);
	return 0;
}
