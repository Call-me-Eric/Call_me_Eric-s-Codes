#include<iostream>
#include<cstring>
#include<cstdio>
#define N 100005
using namespace std;
struct ticket{
	int price, time;
	bool used;
}tk[N];
int n;
int main(){
	int type, price, time;
	int res = 0;
	scanf("%d", &n);
	int head = 1, tail = 1;
	for(int i = 1; i <= n; i++){
		scanf("%d%d%d", &type, &price, &time);
		if(type == 0){
			res += price;
			tk[tail].price = price;
			tk[tail].time  = time;
			tk[tail].used  = false;
			tail++; 
		}
		else{
			bool find = false;
			while(head <tail && time - tk[head].time > 45)	head++;
			for(int j = head; j < tail; j++){
				if(tk[j].price >= price && !tk[j].used){
					tk[j].used = true;
					find = true;
					break; 
				}
			}
			if(!find)
				res += price;
		}
			
	} 
	printf("%d\n", res);	
	return 0;
}

