#include <cstdio>
#include <iostream>
using namespace std;
int n, k;
struct stu{int xuehao;double sorce;}h[1001];
void swapp(int x, int y){stu t = h[x];h[x] = h[y];h[y] = t;return;}

void siftdown(int i){
	int flag = 1, t;
	while(i * 2 <= k && flag){
		if(h[i].sorce > h[i * 2].sorce)t = i * 2;
		if(i * 2 + 1 <= k){
			if(h[t].sorce > h[i * 2 + 1].sorce)
				t = i * 2 + 1;
		}
		if(t != i){
			swapp(i, t);
			i = t;
		}
		else
			flag = 0;
	}
}
void pop(){stu t = h[1];h[1] = h[n];siftdown(1);return;}
int main() {
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;i++){
		scanf("%d%lf",&h[i].xuehao,&h[i].sorce);
	}
	for(int i = k / 2;i >= 1;i--){
		siftdown(i);
	}
	pop();
	for(int i = k + 1;i <= n;i++){
		if(h[i].sorce > h[1].sorce){
			h[1] = h[i];
			siftdown(i);
		}
	} 
	printf("%d %g",h[1].xuehao,h[1].sorce);
	return 0;
}
//stu ;
