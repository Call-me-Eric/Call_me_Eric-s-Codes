#include<bits/stdc++.h>
using namespace std;
int T,A,B;
int size = 1;
bool book[200000];
struct node{
	int num ,step;
};

void getprime(){
	for(int i = 2;i <= sqrt(100001);i++){
		if(book[i] == 0){
			for(int j = i * i;j <= 100001;j += i){
				book[j] = 1;
			}
		}
	}
	book[1] = 1;
	return;
}
int bfs(){
	queue<node> que;
	node a;
	if(A == B)return 0;
	a.num = A;
	a.step = 0;
	que.push(a);
	while(!que.empty()){
		node temp = que.front();
		que.pop();
		int tmp = temp.num;
		int len = 0;
		while(tmp != 0){
			len++;
			tmp /= 10;
		}
		tmp = temp.num;
		for(int i = 1,per = 1;i <= len;i++,per *= 10){
			for(int j = 0;j <= 9;j++){
				int t = tmp - ((tmp / per) % 10) * per + j * per;
				if(!book[t]){
					a.num = t;
					a.step = temp.step + 1;
					que.push(a);
					if(t == B){
						return temp.step + 1;
					}
				}
			}
		}
	}
	return -1;
}
int main(){
	scanf("%d",&T);
	getprime();
	while(T--){
		scanf("%d%d",&A,&B);
		int tmp = bfs();
		if(tmp == -1){
			puts("No solution");
		}
		else printf("%d\n",tmp);
	}
	return 0;
}