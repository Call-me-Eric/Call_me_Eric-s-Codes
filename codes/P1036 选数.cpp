#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n, k,ans = 0,sum = 0;
int a[21],b[21];
int prime(int x){
	if(x == 0 || x == 1) return 0;
	for(int i = 2; i<=sqrt(x);i++)
		if(x%i == 0) return 0;
 	return 1;
	
}

void dfs(int x,int y){
	for(int i = y; i<= n;i ++)
	if(!b[i]){
		b[i] = 1;
		sum += a[i];
		if(x == k){
			if(prime(sum)) ans++;
		}
		else dfs(x+1,i+1);
		b[i] = 0;
		sum -= a[i];
	}
	
}
int main(){
	scanf("%d%d",&n, &k);
	for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
	dfs(1,1);
	printf("%d\n",ans);
	return 0;
}

