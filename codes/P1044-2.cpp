#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int a[101][10001];
int n;
int dfs(int top,int i){
	if(a[top][i] != 0)return a[top][i];
	if(i == n + 1)return 1;
	if(top > 0)a[top][i] += dfs(top - 1,i);
	a[top][i] += dfs(top + 1,i + 1);
	return a[top][i];
}
int main(){
	scanf("%d",&n);
	printf("%d",dfs(0,1));
	return 0;
}

