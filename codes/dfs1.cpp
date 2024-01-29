#include <cstdio>
#include <iostream>
using namespace std;
int a[101];
int n;
int book[101];
void dfs(int step){
	int i;
	if(step == n + 1){
		for(i = 1;i <= n;i++){
			printf("%5d",a[i]);
		}
		printf("\n");
		return;
	}
	for(i = 1;i <= n;i++){
		if(!book[i]){
			a[step] = i;
			book[i] = 1;
			dfs(step + 1);
			book[i] = 0;
		}
	}
}
int main(){
	scanf("%d",&n);
	dfs(1);
	return 0;
}

