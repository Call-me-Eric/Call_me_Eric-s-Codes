#include<iostream>
#include<cstdio>
using namespace std;
struct queue{
	int price, time, used;
}tickets[200001];
int head = 1, tail = 1;
int n, sum;
int main(){
	int canuse = 0;
	int price, time, book;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d%d%d",&book, &price, &time);
		if(!book){
			tickets[tail].price = price;
			tickets[tail].time = time;
			tickets[tail].used = 0;
			sum += price;
			tail++;
		}
		else if(book){
			for(int i = head;i < tail;i++){
				canuse = 0;
				if(time - tickets[i].time <= 45){
					if(tickets[i].price > price && tickets[i].used == 0){
						canuse = 1;
						tickets[i].used = 1;
						break;
					}	
				}
				else head++;
				if(canuse) sum += price;
			}
		}
	}
	printf("%d",sum);
	return 0;
} 
