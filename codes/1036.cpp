#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n, k, ans = 0;
int a[25],book[25];
int dfs(int step, int sum,int cnt){ //step选第几个，sum为和，cnt为选了几个 
	if(step == k) return; 
}
int prime(int x){
	if(x ==1) return 0;
	for(int i = 2; i <=sqrt(x); i++)
		if(x%i == 0 ) return 0;
	return 1;
}
int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i=1; i <= n; i++)
		scanf("%d", &a[i]); 
	dfs(1,);
	return 0;
}

