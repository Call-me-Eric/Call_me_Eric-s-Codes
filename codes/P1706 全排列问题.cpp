#include <iostream>
#include <cstdio>

using namespace std;
int a[10], book[10],n;
void dfs(int x){
	if(x > n){
		for (int i = 1; i <= n; i++)
			printf("%5d", a[i]);
		printf("\n");
		return;
	}
	for (int i = 1; i <= n; i++){	//枚举每个数 
		if(!book[i]){
			a[x] = i;
			book[i] = 1;
			dfs( x + 1);	//递 
			book[i] = 0;
		}
	}
	//归 
}
int main(){
	scanf("%d", &n);
	dfs(1);
	return 0;
}

