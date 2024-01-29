#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int a[10001];
int n,k,sum,total;
inline bool prime(int x){
	for(int i = 2;i <= sqrt(x);i++)
		if(x % i == 0)
			return false;
	return true;
}
inline void dfs(int step,int sum,int cnt){
	if(step == n + 1 || cnt == k){ 
		if(cnt == k && prime(sum))total++;
		return;
	}
	dfs(step + 1, sum + a[step], cnt + 1);
	dfs(step + 1, sum, cnt);
	return;
}
int main(){
	scanf("%d %d",&n,&k);
	for(int i = 1;i <= n;i++)
		scanf("%d",&a[i]);
	dfs(1,0,0);
	printf("%d",total);
	return 0;
}
