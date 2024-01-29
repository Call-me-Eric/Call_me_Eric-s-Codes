#include <iostream>
#include <cstdio>
#define inf 99999999
using namespace std;

int h[10001], n;

void dfs(int m){
	if(h[m] != -1)return;
	h[m] = 1;
	for(int i = 1;i <= m / 2;i++){
		dfs(i);
		h[m] += h[i];
	}
	return;
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)h[i] = -1;
	dfs(n);
	printf("%d",h[n]);
	return 0;
}

